#include "HamArc.h"

void CheckOpenArchive(std::ofstream& archive) {
    if (!archive.is_open()) {
        std::cerr << "Error in creating archive";
        exit(EXIT_FAILURE);
    }
}

void CheckOpenArchive(std::fstream& archive) {
    if (!archive.is_open()) {
        std::cerr << "Error in openning archive";
        exit(EXIT_FAILURE);
    }
}

void CheckOpenArchive(std::ifstream& archive) {
    if (!archive.is_open()) {
        std::cerr << "Error in openning archive";
        exit(EXIT_FAILURE);
    }
}
void BinConverter(std::vector<bool>& vr, int pos, long long num) {
    while (num > 0) {
        vr[pos] = num % 2;
        pos--;
        num /= 2;
    }
}

std::vector<bool> ToVector(const char* buffer, int bits_size) {
    std::vector<bool> bits(bits_size);

    for (int i = 0; i < bits_size; i++) {
        if (buffer[i] == '1') {
            bits[i] = 1;
        }
    }

    return bits;
}

void InitVector(std::vector<bool>& bits, int cnt, char seq, int index) {
    for (int i = cnt; i >= 0; i--) {
        bits[index++] = (seq >> i) & 1;
    }
}

std::vector<bool> HamArc::Coder::ToCode(std::vector<bool> seq, int data_bits, int parity_bits) {
    std::vector<bool> tocoded_seq(data_bits + parity_bits, 0);

    int data_ind = 0;
    for (int i = 1; i <= data_bits + parity_bits; i++) {
        if (i & (i - 1)) {
            tocoded_seq[i - 1] = seq[data_ind++];
        }
    }

    for (int i = 0; i < parity_bits; i++) {
        int parity = 0;

        for (int j = (1 << i) - 1; j < data_bits + parity_bits; j++) {
            if ((1 + j) & (1 << i)) {
                parity ^= tocoded_seq[j];
            }
        }

        tocoded_seq[(1 << i) - 1] = parity;
    }

    return tocoded_seq;
}

std::vector<bool> HamArc::Coder::Decode(std::vector<bool> tocoded_seq, int data_bits, int parity_bits) {
    std::vector<bool> tocoded_seq_temp = tocoded_seq;

    for (int i = 0; i < parity_bits; i++) {
        tocoded_seq_temp[(1 << i) - 1] = 0;
    }

    int wrong_pos = 0;
    for (int i = 0; i < parity_bits; i++) {
        int parity = 0;

        for (int j = (1 << i) - 1; j < data_bits + parity_bits; j++) {
            if ((1 + j) & (1 << i)) {
                if (tocoded_seq[j] == tocoded_seq_temp[j]) {
                    parity ^= tocoded_seq_temp[j];
                }
            }
        }

        if (parity != tocoded_seq[(1 << i) - 1]) {
            wrong_pos += (1 << i);
        }
    }
    if (wrong_pos != 0) {
        tocoded_seq[wrong_pos - 1] = !tocoded_seq[wrong_pos - 1];
    }

    std::vector<bool> seq;
    for (int i = 0; i < data_bits + parity_bits; i++) {
        if (i & (i + 1)) {
            seq.push_back(tocoded_seq[i]);
        }
    }

    return seq;
}

std::vector<unsigned short> GetCreationTime(const std::string& file_name) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring f = converter.from_bytes(file_name);
    const wchar_t* file_name_width = f.c_str();

    WIN32_FILE_ATTRIBUTE_DATA file_values;

    if (!GetFileAttributesExW(file_name_width, GetFileExInfoStandard, &file_values)) {
        std::cerr << "Error in getting values of file" << GetLastError() << std::endl;
        exit(EXIT_FAILURE);
    } else {
        FILETIME file_creation_time = file_values.ftCreationTime;
        SYSTEMTIME system_creation_time_local, system_creation_time_UTC;

        FileTimeToSystemTime(&file_creation_time, &system_creation_time_UTC);
        SystemTimeToTzSpecificLocalTime(nullptr, &system_creation_time_UTC, &system_creation_time_local);
        unsigned short second = system_creation_time_local.wSecond;
        unsigned short minute = system_creation_time_local.wMinute;
        unsigned short hour = system_creation_time_local.wHour;
        unsigned short day = system_creation_time_local.wDay;
        unsigned short month = system_creation_time_local.wMonth;
        unsigned short year = system_creation_time_local.wYear;

        std::vector<unsigned short> data_time = { second, minute, hour, day, month, year};
        return data_time;
    }
}

void SetCreationTime(std::vector<unsigned short>& creation_time, const std::string& file_name) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring f = converter.from_bytes(file_name);
    const wchar_t* file_name_width = f.c_str();

    FILETIME new_create_time;
    SYSTEMTIME data;
    data.wSecond = creation_time[0];
    data.wMinute = creation_time[1];
    data.wHour =   creation_time[2];
    data.wDay =    creation_time[3];
    data.wMonth =  creation_time[4];
    data.wYear =   creation_time[5];

    SystemTimeToFileTime(&data, &new_create_time);

    HANDLE file_handle = CreateFileW(file_name_width, FILE_WRITE_ATTRIBUTES, 0,
                                     nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (file_handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error in openning file " << GetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    CloseHandle(file_handle);
}
long long GetSize(const std::string& file_name) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring f = converter.from_bytes(file_name);

    const wchar_t* file_name_width = f.c_str();
    WIN32_FILE_ATTRIBUTE_DATA file_values;

    if (!GetFileAttributesExW(file_name_width, GetFileExInfoStandard, &file_values)) {
        std::cerr << "Error in getting values of file " << GetLastError() << std::endl;
        exit(EXIT_FAILURE);
    } else {
        return file_values.nFileSizeLow;
    }
}

std::vector<unsigned short> GetChangeTime(const std::string& file_name) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring f = converter.from_bytes(file_name);

    const wchar_t* file_name_width = f.c_str();
    WIN32_FILE_ATTRIBUTE_DATA file_values;

    if (!GetFileAttributesExW(file_name_width, GetFileExInfoStandard, &file_values)) {
        std::cerr << "Error in getting values of file " << GetLastError() << std::endl;
        exit(EXIT_FAILURE);
    } else {
        FILETIME file_last_time_write = file_values.ftLastWriteTime;
        SYSTEMTIME system_last_time_write;

        FileTimeToSystemTime(&file_last_time_write, &system_last_time_write);
        unsigned short second = system_last_time_write.wSecond;
        unsigned short minute = system_last_time_write.wMinute;
        unsigned short hour = system_last_time_write.wHour;
        unsigned short day = system_last_time_write.wDay;
        unsigned short month = system_last_time_write.wMonth;
        unsigned short year = system_last_time_write.wYear;

        std::vector<unsigned short> data_time = { second, minute, hour, day, month, year };
        return data_time;
    }
}

void SetChangeTime(std::vector<unsigned short>& change_time, const std::string& file_name) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring f = converter.from_bytes(file_name);
    const wchar_t* file_name_width = f.c_str();

    FILETIME new_create_time;
    SYSTEMTIME data;

    data.wSecond = change_time[0];
    data.wMinute = change_time[1];
    data.wHour =   change_time[2];
    data.wDay =    change_time[3];
    data.wMonth =  change_time[4];
    data.wYear =   change_time[5];

    SystemTimeToFileTime(&data, &new_create_time);
    HANDLE file_handle = CreateFileW(file_name_width, FILE_WRITE_ATTRIBUTES, 0,
                                     nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (file_handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Error in openning file " << GetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    CloseHandle(file_handle);
}

std::vector<std::string> HamArc::List(const std::string& archive_name, bool show) {
    std::ifstream archive(archive_name, std::ios::binary);
    CheckOpenArchive(archive);
    archive.seekg(0, std::ios::end);
    std::streampos file_end = archive.tellg();
    archive.seekg(0);
    std::vector<std::string> files;
    int data_bits = 0;

    for (int i = 0; i < 4; i++) {
        char temp[12];
        archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);

        data_bits <<= 8;
        int bit = 0;

        for (int m = 0; m < 8; m++) {
            bit |= (buff[m] << (7 - m));
        }

        data_bits += bit;
    }

    int parity_bits = static_cast<int>(floor(log2(data_bits))) + 1;
    std::vector<bool> bits(8);
    int pos_bits = 0;

    while (archive.tellg() != file_end) {
        std::string name;
        int j = 0;
        int pos = 0;
        bool is_end = 0;
        for (int i = 0; i < ceil(1600.0 / data_bits); i++) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);

            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            j = 0;
            Coder::DecodeSeq(buff, bits, pos_bits, is_end, name, j);
            delete[] temp;

            if (is_end) {
                break;
            }
            pos++;
        }

        pos = -(pos + 1);
        archive.seekg(pos * (data_bits + parity_bits), std::ios::cur);
        pos = 0;
        std::string exten;
        bool is_end_exten = 0;
        archive.seekg((1600 / data_bits) * (data_bits + parity_bits), std::ios::cur);

        for (int i = 0; i < ceil(160.0 / data_bits); i++) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);

            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            if (i == 0) {
                j = 1600 % data_bits;
            } else {
                j = 0;
            }

            Coder::DecodeSeq(buff, bits, pos_bits, is_end_exten, exten, j);
            delete[] temp;

            if (is_end_exten) {
                break;
            }
            pos++;
        }
        pos = -(pos + 1);
        pos_bits = 0;
        archive.seekg(pos * (data_bits + parity_bits), std::ios::cur);

        files.push_back(name + '.' + exten);

        if (show) {
            std::cout << name + '.' + exten << std::endl;
        }

        archive.seekg(352 / data_bits * (data_bits + parity_bits), std::ios::cur);
        int i = 0;
        bool is_ended = 0;
        int cnt = 0;

        long long size = 0;

        while (i < ceil((32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits))) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);

            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            if (i == 0) {
                j = (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits;
            } else {
                j = 0;
            }

            Coder::DecodeSeq(buff, bits, pos_bits, is_ended, size, cnt, j);
            i++;
            delete[] temp;

            if (is_ended) {
                break;
            }
        }
        archive.seekg((size + 1) * (data_bits + parity_bits), std::ios::cur);
    }

    return files;
}

std::string HamArc::GetNameFile(const std::string& file_name) {
    size_t pos = file_name.find_last_of('\\');

    if (pos != std::string::npos) {
        pos++;
    } else {
        pos = 0;
    }

    std::string name{};
    for (size_t i = pos; i < file_name.size() && file_name[i] != '.'; i++) {
        name.push_back(file_name[i]);
    }

    return name;
}

std::string HamArc::GetExtensionName(const std::string& file_name) {
    size_t pos = file_name.find_last_of('.');
    std::string exten{};

    if (pos != std::string::npos) {
        for (int i = pos + 1; i < file_name.size(); i++) {
            exten.push_back(file_name[i]);
        }
    }

    return exten;
}

void HamArc::Coder::ToCodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, std::ostream& archive, int data_bits, int parity_bits) {
    int j = 0;

    while (j < buff.size()) {
        bits[pos_bits++] = buff[j++];

        if (pos_bits == data_bits) {
            std::vector<bool> to_coded_bits = Coder::ToCode(bits, data_bits, parity_bits);

            for (bool bit : to_coded_bits) {
                archive << bit;
            }
            pos_bits = 0;
        }
    }
}

void HamArc::Coder::DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_ended, std::string& str, int j) {
    while (j < buff.size()) {
        bits[pos_bits++] = buff[j++];

        if (pos_bits == 8) {
            char seq = 0;

            for (int p = 0; p < 8; p++) {
                seq |= (bits[p] << (7 - p));
            }

            pos_bits = 0;

            if (seq == '\v') {
                is_ended = 1;
                break;
            }

            str += seq;
        }
    }
}

void HamArc::Coder::DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, std::ostream& new_file, int& cnt, long long size, int j) {

    while (j < buff.size()) {
        bits[pos_bits++] = buff[j++];

        if (pos_bits == 8) {
            char seq = 0;
            for (int p = 0; p < 8; p++) {
                seq |= (bits[p] << (7 - p));
            }
            pos_bits = 0;

            new_file << seq;
            cnt++;
        }
        if (cnt == size) {
            is_end = 1;
            break;
        }
    }
}

void HamArc::Coder::DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, long long& size, int& cnt, int j) {

    while (j < buff.size()) {
        bits[pos_bits++] = buff[j++];

        if (pos_bits == 8) {
            size <<= 8;
            int bit = 0;

            for (int p = 0; p < 8; p++) {
                bit |= (bits[p] << (7 - p));
            }

            pos_bits = 0;
            size += bit;
            cnt++;
        }

        if (cnt == 4) {
            is_end = 1;
            break;
        }
    }
}

void HamArc::Create(const std::string& archive_name, int data_bits) {
    std::ofstream archive(archive_name, std::ios::binary);
    CheckOpenArchive(archive);

    std::vector<bool> buff(32);
    std::vector<bool> bits(8);

    int pos_bits = 0;
    BinConverter(buff, 31, data_bits);

    Coder::ToCodeSeq(buff, bits, pos_bits, archive, 8, 4);
    archive.close();
}

void HamArc::Coder::DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, std::vector<unsigned short>& date, int& cnt, int j) {

    while (j < buff.size()) {
        bits[pos_bits++] = buff[j++];

        if (pos_bits == 8) {
            date[cnt / 2] <<= 8;
            int bit = 0;

            for (int p = 0; p < 8; p++) {
                bit |= (bits[p] << (7 - p));
            }

            pos_bits = 0;
            cnt++;
            date[cnt / 2] += bit;

        }

        if (cnt == 12) {
            is_end = 1;
            break;
        }
    }
}

void FillToMaxSize(std::string& str, int size) {
    while (str.size() < size) {
        str.push_back('\v');
    }
}

void HamArc::Extract(const std::string& archive_name, const std::string& file_name) {
    std::ifstream archive(archive_name, std::ios::binary);
    CheckOpenArchive(archive);

    int data_bits = 0;

    for (int i = 0; i < 4; ++i) {
        char temp[12];
        archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);

        data_bits <<= 8;
        int bit = 0;
        for (int p = 0; p < 8; p++) {
            bit |= (buff[p] << (7 - p));
        }

        data_bits += bit;
    }
    int parity_bits = static_cast<int>(floor(log2(data_bits))) + 1;
    std::string exten = GetExtensionName(file_name);
    std::string name = GetNameFile(file_name);

    std::vector<unsigned short> creation_time;
    std::vector<unsigned short> change_time;
    creation_time.resize(6);
    change_time.resize(6);

    long long size = 0;
    std::vector<bool> bits(8);

    int pos_bits = 0;

    while (archive) {
        std::string posible_name;
        int j = 0;
        int pos = 0;
        bool is_end = 0;

        for (int i = 0; i < ceil(1600.0 / data_bits); i++) {

            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);

            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);
            j = 0;

            Coder::DecodeSeq(buff, bits, pos_bits, is_end, posible_name, j);
            delete[] temp;

            if (is_end) {
                break;
            }

            pos++;
        }
        pos = -(pos + 1);
        archive.seekg(pos * (data_bits + parity_bits), std::ios::cur);
        pos = 0;

        bool is_end_exten = 0;
        std::string posible_exten;
        archive.seekg(1600 / data_bits * (data_bits + parity_bits), std::ios::cur);
        pos = 0;

        for (int i = 0; i < ceil(160.0 / data_bits); i++) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);

            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            if (i == 0) {
                j = 1600 % data_bits;
            } else {
                j = 0;
            }

            Coder::DecodeSeq(buff, bits, pos_bits, is_end_exten, posible_exten, j);
            delete[] temp;

            if (is_end_exten) {
                break;
            }

            pos++;
        }

        pos_bits = 0;

        if (posible_exten == exten && posible_name == name) {
            archive.seekg((160 + 1600 % data_bits) / data_bits * (data_bits + parity_bits) -
                          (data_bits + parity_bits) * (pos + 1), std::ios::cur);
            int cnt = 0;
            bool is_end = 0;
            int i = 0;

            while (i < ceil((96 + (160 + 1600 % data_bits) % data_bits) / static_cast<double>(data_bits)) && !is_end) {
                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);

                std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

                if (i == 0) {
                    j = (160 + 1600 % data_bits) % data_bits;
                } else {
                    j = 0;
                }

                Coder::DecodeSeq(buff, bits, pos_bits, is_end, creation_time, cnt, j);

                i++;

                delete[] temp;
            }
            archive.seekg((floor((96 + (160 + 1600 % data_bits) % data_bits) / static_cast<double>(data_bits)) - i) *
                          (data_bits + parity_bits), std::ios::cur);

            cnt = 0;
            is_end = 0;
            i = 0;

            while (i < ceil((96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits)) && !is_end) {
                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);

                std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

                if (i == 0) {
                    j = (96 + (160 + 1600 % data_bits) % data_bits) % data_bits;
                } else {
                    j = 0;
                }

                Coder::DecodeSeq(buff, bits, pos_bits, is_end, change_time, cnt, j);

                i++;
                delete[] temp;
            }
            archive.seekg(floor(((96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits)) - i) * (data_bits + parity_bits), std::ios::cur);

            cnt = 0;
            is_end = 0;
            i = 0;
            size = 0;

            while (i < ceil((32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits)) && !is_end) {
                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);
                std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

                if (i == 0) {
                    j = (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits;
                } else {
                    j = 0;
                }

                Coder::DecodeSeq(buff, bits, pos_bits, is_end, size, cnt, j);

                i++;
                delete[] temp;
            }
            archive.seekg(floor(((32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) /
                                 static_cast<double>(data_bits)) - i) * (data_bits + parity_bits), std::ios::cur);

            std::ofstream new_file(file_name, std::ios::binary);
            CheckOpenArchive(new_file);


            cnt = 0;
            is_end = 0;
            i = 0;

            while (i < ceil((size * 8 + (32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits))) {

                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);
                std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

                if (i == 0) {
                    j = (32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) % data_bits;
                } else {
                    j = 0;
                }

                Coder::DecodeSeq(buff, bits, pos_bits, is_end, new_file, cnt, size, j);

                i++;
                delete[] temp;
            }

            SetCreationTime(creation_time, file_name);
            SetChangeTime(creation_time, file_name);

            new_file.close();
            break;
        } else {
            pos = -(pos + 1);
            archive.seekg(pos * (data_bits + parity_bits), std::ios::cur);
            archive.seekg(352 / data_bits * (data_bits + parity_bits), std::ios::cur);


            int cnt = 0;
            int i = 0;
            bool is_end = 0;
            size = 0;

            while (i < ceil((32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits)) && !is_end) {
                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);
                std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

                if (i == 0) {
                    j = (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits;
                } else {
                    j = 0;
                }

                Coder::DecodeSeq(buff, bits, pos_bits, is_end, size, cnt, j);

                i++;
                delete[] temp;
            }

            archive.seekg((size + 1) * (data_bits + parity_bits), std::ios::cur);
            pos_bits = 0;
        }
    }

    archive.close();
}

void HamArc::Append(const std::string& archive_name, const std::string& file_name) {
    std::fstream archive(archive_name, std::ios::in | std::ios::app | std::ios::binary);
    CheckOpenArchive(archive);
    archive.seekg(0);

    int data_bits = 0;
    for (int i = 0; i < 4; i++) {
        char temp[12];
        archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);

        data_bits <<= 8;
        int bit = 0;

        for (int p = 0; p < 8; p++) {
            bit |= (buff[p] << (7 - p));
        }

        data_bits += bit;
    }

    int parity_bits = static_cast<int>(floor(log2(data_bits))) + 1;

    archive.seekg(0, std::ios::end);
    std::ifstream file(file_name, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "File can't be opened";
        exit(EXIT_FAILURE);
    }

    std::string name = GetNameFile(file_name);
    std::string exten = GetExtensionName(file_name);

    FillToMaxSize(name, 200);
    FillToMaxSize(exten, 20);

    std::vector<bool> bits(data_bits);
    int pos_bits = 0;
    long long size = GetSize(file_name);
    std::vector<unsigned short> creation_time = GetCreationTime(file_name);
    std::vector<unsigned short> change_time = GetChangeTime(file_name);



    for (char i : name) {
        std::vector<bool> buff(8);
        InitVector(buff, 7, i, 0);
        Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);
    }

    for (char i : exten) {
        std::vector<bool> buff(8);
        InitVector(buff, 7, i, 0);
        Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);
    }

    for (unsigned short i : creation_time) {
        std::vector<bool> buff(16);
        BinConverter(buff, 15, i);
        Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);
    }

    for (unsigned short i : change_time) {
        std::vector<bool> buff(16);
        BinConverter(buff, 15, i);
        Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);
    }

    std::vector<bool> buff(32);
    BinConverter(buff, 31, size);
    Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);


    while (file) {
        std::vector<bool> buff(8);
        char seq;
        file.get(seq);

        InitVector(buff, 7, seq, 0);
        Coder::ToCodeSeq(buff, bits, pos_bits, archive, data_bits, parity_bits);
    }

    if (pos_bits != 0) {
        while (pos_bits != data_bits) {
            bits[pos_bits++] = 0;
        }

        std::vector<bool> to_coded_bits = Coder::ToCode(bits, data_bits, parity_bits);
        for (bool i : to_coded_bits) {
            archive << i;
        }
    }

    file.close();
    archive.close();
}

void HamArc::Concatenate(const std::string& main_archive_name, const std::string& add_archive_name) {
    std::fstream main_archive(main_archive_name, std::ios::in | std::ios::app | std::ios::binary);
    std::ifstream add_archive(add_archive_name, std::ios::binary);

    CheckOpenArchive(main_archive);
    CheckOpenArchive(add_archive);

    main_archive.seekg(0);
    int data_bits_first = 0;


    for (int i = 0; i < 4; i++) {
        char temp[12];
        main_archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);
        data_bits_first <<= 8;

        int bit = 0;
        for (int p = 0; p < 8; p++) {
            bit |= (buff[p] << (7 - p));
        }
        data_bits_first += bit;
    }

    int data_bits_second = 0;

    for (int i = 0; i < 4; i++) {

        char temp[12];

        add_archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);
        data_bits_second <<= 8;

        int bit = 0;
        for (int p = 0; p < 8; p++) {
            bit |= (buff[p] << (7 - p));
        }

        data_bits_second += bit;
    }

    if (data_bits_first != data_bits_second) {
        std::cerr << "Error in concatinating archives with different codes";
        exit(EXIT_FAILURE);
    }

    main_archive.seekg(0, std::ios::end);
    char temp[512 * 8 + 1];

    while (add_archive) {
        temp[512 * 8] = 0;
        add_archive.read(temp, 512 * 8);
        main_archive.write(temp, add_archive.gcount());
    }
    add_archive.close();
    main_archive.close();
}

void HamArc::Delete(const std::string& archive_name, const std::string& file_name) {
    std::fstream archive(archive_name);
    CheckOpenArchive(archive);

    archive.seekg(0, std::ios::end);
    std::streampos file_end = archive.tellg();
    archive.seekg(0);

    int data_bits = 0;
    char temp[12];

    for (int i = 0; i < 4; i++) {

        archive.read(temp, 12);
        std::vector<bool> buff = Coder::Decode(ToVector(temp, 12), 8, 4);
        data_bits <<= 8;

        int bit = 0;
        for (int p = 0; p < 8; p++) {
            bit |= (buff[p] << (7 - p));
        }

        data_bits += bit;
    }

    long long size = 0;
    int pos_bits = 0;

    int parity_bits = static_cast<int>(floor(log2(data_bits))) + 1;
    std::string name = GetNameFile(file_name);
    std::string posible_name;
    std::vector<bool> bits(8);


    while (archive) {
        int pos = 0;
        int j = 0;
        bool is_end = 0;
        std::streampos start_pos = archive.tellg();
        for (int i = 0; i < ceil(1600.0 / data_bits); i++) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);
            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            j = 0;

            Coder::DecodeSeq(buff, bits, pos_bits, is_end, posible_name, j);

            delete[] temp;

            if (is_end) {
                break;
            }

            pos++;
        }

        pos = -(pos + 1);

        archive.seekg(pos * (data_bits + parity_bits), std::ios::cur);
        archive.seekg(1952 / data_bits * (data_bits + parity_bits), std::ios::cur);

        int cnt = 0;
        bool is_ended = 0;
        size = 0;
        int i = 0;

        while (i < ceil((32 + (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits) / static_cast<double>(data_bits)) && !is_ended) {
            char* temp = new char[data_bits + parity_bits];
            archive.read(temp, data_bits + parity_bits);
            std::vector<bool> buff = Coder::Decode(ToVector(temp, data_bits + parity_bits), data_bits, parity_bits);

            if (i == 0) {
                j = (96 + (96 + (160 + 1600 % data_bits) % data_bits) % data_bits) % data_bits;
            } else {
                j = 0;
            }

            Coder::DecodeSeq(buff, bits, pos_bits, is_ended, size, cnt, j);

            i++;
            delete[] temp;
        }
        if (name != posible_name) {
            archive.seekg((size + 1) * (data_bits + parity_bits), std::ios::cur);
            posible_name.clear();
        } else {
            archive.seekg((size + 1) * (data_bits + parity_bits), std::ios::cur);

            while (archive.tellg() != file_end) {
                char* temp = new char[data_bits + parity_bits];
                archive.read(temp, data_bits + parity_bits);
                std::streampos was_read = archive.tellg();
                archive.seekp(start_pos);
                archive.write(temp, archive.gcount());
                start_pos = archive.tellp();
                archive.seekg(was_read);
                delete[] temp;
            }
            std::filesystem::resize_file(archive_name, start_pos);
            break;
        }

    }
    archive.close();
}