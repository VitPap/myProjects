#pragma once

#include "vector"
#include "Argument.cpp"
#include <string>
#include <string_view>
#include <iostream>
namespace ArgumentParser {
    enum class value_types { value_int, value_string, value_bool };

    class ArgParser {
    public:
        explicit ArgParser(std::string program_name);
        bool Parse(int argc, char** argv);
        bool Parse(std::vector<std::string> arguments);

        ArgParser& AddStringArgument(const char short_name, const char* name, const char* description = "Some description");
        ArgParser& AddStringArgument(const char* name, const char* description = "Some description");

        ArgParser& AddIntArgument(const char short_name, const char* name, const char* description = "Some description");
        ArgParser& AddIntArgument(const char* name, const char* description = "Some description");

        ArgParser& AddFlag(const char short_name, const char* name, const char* description = "Some description");
        ArgParser& AddFlag(const char* name, const char* description = "Some description");

        ArgParser& AddHelp(const char short_name, const char* name, const char* description = "Display this help and exit");
        ArgParser& AddHelp(const char* name, const char* description = "Display this help and exit");

        ArgParser& Default(const bool value);
        ArgParser& Default(const int value);
        ArgParser& Default(const char* value);

        void StoreValues(std::vector<int>& vector);
        void StoreValues(std::vector<bool>& vector);
        void StoreValues(std::vector<std::string>& vector);
        void StoreValue(std::string& value);
        void StoreValue(int& value);
        void StoreValue(bool& value);

        ArgParser& Positional();
        ArgParser& MultiValue(const int n = 0);

        std::string GetStringValue(const char* name, const int n = 0);
        std::string GetStringValue(const char name, const int n = 0);
        std::string GetParserName();
        int GetIntValue(const char* name, const int n = 0);
        int GetIntValue(const char name, const int n = 0);
        bool GetFlag(const char* name, const int n = 0);
        bool GetFlag(const char name, const int n = 0);
        std::string HelpDescription();
        bool Help();

    private:
        std::string parser_name;
        std::vector<Argument<int>> int_arguments;
        std::vector<Argument<bool>> bool_arguments;
        std::vector<Argument<std::string>> string_arguments;

        value_types last_argument{};

        bool IsStringArgument(std::string name);
        bool IsStringArgument(char symbol);
        bool IsIntArgument(std::string name);
        bool IsIntArgument(char symbol);
        bool IsBoolArgument(std::string name);
        bool IsBoolArgument(char symbol);
        void AddToPositionalArgument(const std::string value);

        value_types positional_argument{};
        size_t positional_argument_pos{};
    };

} // namespace ArgumentParser