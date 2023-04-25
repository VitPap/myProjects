#include "ParserOfElf.h"
using namespace std;
ParserOfElf::ParserOfElf(ifstream& f) : file(f) {}

void ParserOfElf::parse() {
    // ELF HEADER
    elfHeader.fill(file);

    // PROGREMM HEADERS
    programHeaders = new ProgrammHeader[elfHeader.phnum];
    for (int i = 0; i < elfHeader.phnum; i++) {
        programHeaders[i].fill(file);
    }

    // SECTION HEADERS
    bufferOffset = elfHeader.phoff + elfHeader.phnum * elfHeader.phentsize;
    const int bufferSize = elfHeader.shoff - bufferOffset;

    const auto buff = new char[bufferSize];
    for (int i = 0; i < bufferSize; i++) {
        file.read(&buff[i], sizeof(char));
    }

    sectionHeaders = new SectionHeader[elfHeader.shnum];
    for (int i = 0; i < elfHeader.shnum; i++) {
        sectionHeaders[i].fill(file);
        if (sectionHeaders[i].type == STR_TAB) {
            if (i == elfHeader.shstrndx) {
                shStrTabAddress = sectionHeaders[i].offset;
                shStrTabSize = sectionHeaders[i].size;
            } else {
                strTabAddress = sectionHeaders[i].offset;
                strTabSize = sectionHeaders[i].size;
            }
        } else if (sectionHeaders[i].type == SYM_TAB) {
            symTabAddress = sectionHeaders[i].offset;
            symTabEntrySize = sectionHeaders[i].entsize;
            symTabEntriesCount = sectionHeaders[i].size / symTabEntrySize;  // by default ent size is 0x10
        }
    }

    fillStrTab(buff);
    fillShStrTab(buff);

    // SYMBOL TABLE
    symTableEntries = new SymTabEntry[symTabEntriesCount];
    stringstream bufferStream;
    bufferStream.write(buff + symTabAddress - bufferOffset, bufferSize - (symTabAddress - bufferOffset));
    bufferStream.seekg(0);
    for (int i = 0; i < symTabEntriesCount; i++) {
        symTableEntries[i].fill(bufferStream);
        if (symTableEntries[i].info % 0b00010000 == STT::FUNC) {
            labels[symTableEntries[i].value] = getStringFromStrTab(symTableEntries[i].name);
        }
    }

    // INSTRUCTIONS
    for (int i = 1; i < elfHeader.shnum; i++) {
        if (getStringFromShStrTab(sectionHeaders[i].name) == ".text") {
            textAddress = sectionHeaders[i].offset;
            textVirtualAddress = sectionHeaders[i].addr;
            textSize = sectionHeaders[i].size;
            SectionHeader::validateTextSize(textSize);
            break;
        }
    }

    int labelsCounter = 0;
    for (uint32_t curAddress = 0; curAddress < textSize; curAddress += 4) {
        Instruction* newInstr = InstructionFab::createInstruction(*reinterpret_cast<uint32_t*>(&buff[curAddress]));
        newInstr->setAddress(textVirtualAddress + curAddress);
        if (newInstr->needLabel()) {
            uint32_t address = newInstr->getImmAddr();
            if (labels.count(address) <= 0) {
                labels[address] = "L" + to_string(labelsCounter++);
            }
        }
        instructions.push_back(newInstr);
    }

    for (auto& inst : instructions) {
        if (inst->needLabel()) {
            uint32_t address = inst->getImmAddr();
            inst->setLabel(labels[address]);
        }
    }

    delete[] buff;
}

void ParserOfElf::printDotText(ostream& out) {
    out << ".text\n";
    int curAddress = textVirtualAddress;
    for (int i = 0; i < instructions.size(); i++, curAddress += 4) {
        if (labels.count(curAddress) > 0) {
            constexpr int buffSize = 128;
            char buff[buffSize];
            snprintf(buff, buffSize, "%08x   <%s>:\n", curAddress, labels[curAddress].c_str());
            out << buff;
        }
        instructions.at(i)->toString(out);
    }
}

void ParserOfElf::printSymtab(ostream& out) const {
    out << ".symtab\n"
        << "Symbol Value              Size Type 	 Bind 	 Vis   	  Index Name\n";
    for (int i = 0; i < symTabEntriesCount; i++) {
        SymTabEntry curEntry = symTableEntries[i];

        string name;
        if (curEntry.info % 0b00010000 == STT::SECTION) {
            name = getStringFromShStrTab(sectionHeaders[curEntry.shndx].name);
        } else {
            name = getStringFromStrTab(curEntry.name);
        }

        constexpr int buffSize = 128;
        char buff[buffSize];
        snprintf(buff, buffSize, "[%4i] 0x%-15X %5i %-8s %-8s %-8s %6s %s", i, curEntry.value, curEntry.size,
                 toStringSTT(static_cast<STT>(curEntry.info % 0b10000)).c_str(),
                 toStringSTB(static_cast<STB>(curEntry.info >> 4)).c_str(),
                 toStringSTV(static_cast<STV>(curEntry.other)).c_str(),
                 toStringSHN(static_cast<SHN>(curEntry.shndx)).c_str(),
                 name.c_str());
        out << buff << "\n";
    }
}

void ParserOfElf::fillStrTab(const char* buff) {
    strTab = new char[strTabSize];
    for (int j = 0; j < strTabSize; j++) {
        strTab[j] = buff[strTabAddress + j - bufferOffset];
    }
}

void ParserOfElf::fillShStrTab(const char* buff) {
    shStrTab = new char[shStrTabSize];
    for (int j = 0; j < shStrTabSize; j++) {
        shStrTab[j] = buff[shStrTabAddress + j - bufferOffset];
    }
}

string ParserOfElf::getStringFromStrTab(const uint32_t offset) const {
    if (offset > strTabSize) {
        throw runtime_error("strTab index '" + to_string(offset) + "' is out of bound for size '" + to_string(strTabSize) + "'");
    }

    stringstream ss;
    int charsRead = 0;
    while (strTab[offset + charsRead] != '\0') {
        ss << strTab[offset + charsRead];
        ++charsRead;
    }

    return ss.str();
}

string ParserOfElf::getStringFromShStrTab(const uint32_t offset) const {
    if (offset > shStrTabSize) {
        throw runtime_error("shStrTab index '" + to_string(offset) + "' is out of bound for size '" + to_string(shStrTabSize) + "'");
    }

    stringstream ss;
    int charsRead = 0;
    while (shStrTab[offset + charsRead] != '\0') {
        ss << shStrTab[offset + charsRead];
        ++charsRead;
    }

    return ss.str();
}

ParserOfElf::~ParserOfElf() {
    for (const auto& instruction : instructions) {
        delete instruction;
    }
    delete[] programHeaders;
    delete[] sectionHeaders;
    delete[] symTableEntries;
    delete[] strTab;
    delete[] shStrTab;
}