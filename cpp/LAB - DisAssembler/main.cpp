#include <ParserOfElf.h>
#include <InstructionFab.h>
using namespace std;
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

ParserOfElf* parseFile(ifstream& input, const char* path) {
    input.open(path, ios_base::binary);
    if (!input.is_open()) {
        throw ios_base::failure("Can`t open input file");
    }

    const auto parser = new ParserOfElf(input);
    parser->parse();
    return parser;
};

void openOutFile(ofstream& output, const char* path) {
    output.open(path, ios_base::binary);
    if (!output.is_open()) {
        throw ios_base::failure("Can`t open output file");
    }
}

int main(const int argc, char const* argv[]) {
    if (argc < 3) {
        cout << "2 arguments expected, " + to_string(argc - 1) + " found\n";
        return 0;
    }

    try {
        ifstream input;
        ParserOfElf* parser = parseFile(input, argv[1]);
        try {
            ofstream output;
            openOutFile(output, argv[2]);
            parser->printDotText(output);
            output << "\n";
            parser->printSymtab(output);
        } catch (const ios_base::failure& e) {
            cout << e.what() << endl;
        }
        delete parser;
    } catch (ios_base::failure& e) {
        cout << e.what() << endl;
    } catch (runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}