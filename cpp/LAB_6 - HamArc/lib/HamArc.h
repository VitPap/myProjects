#pragma once

#include <iostream>
#include <bitset>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <cmath>
#include <ctime>
#include <timezoneapi.h>
#include <chrono>
#include <unistd.h>
#include <vector>

class HamArc {
public:
    static void Create(const std::string& archive_name, int data_bits = 8);
    static void Append(const std::string& archive_name, const std::string& file_name);
    static void Extract(const std::string& archive_name, const std::string& file_name);
    static std::vector<std::string> List(const std::string& archive_name, bool show = false);
    static void Delete(const std::string& archive_name, const std::string& file_name);
    static void Concatenate(const std::string& main_archive, const std::string& add_archive);

private:
    class Coder {
    public:
        static void ToCodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, std::ostream& full_name_archive, int data_bits, int parity_bits);
        static void DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, long long& size, int& count, int j);
        static void DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, std::vector<unsigned short>& date, int& count, int j);
        static void DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, std::string& string, int j);
        static void DecodeSeq(std::vector<bool>& buff, std::vector<bool>& bits, int& pos_bits, bool& is_end, std::ostream& new_file, int& count, long long size, int j);
        static std::vector<bool> Decode(std::vector<bool> toCoded_symbols, int data_bits, int parity_bits);
        static std::vector<bool> ToCode(std::vector<bool> symbols, int data_bits, int parity_bits);
    };

    static std::string GetNameFile(const std::string& file_name);
    static std::string GetExtensionName(const std::string& file_name);
};