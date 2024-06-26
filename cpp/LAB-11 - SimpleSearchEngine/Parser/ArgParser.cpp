#include "ArgParser.h"
#include "Argument.cpp"
#include <sstream>
namespace ArgumentParser {
    ArgParser::ArgParser(std::string program_name) : parser_name(program_name) {};
    bool ArgumentParser::ArgParser::Parse(std::string &str) {
        std::vector<std::string> arguments;
        std::istringstream ss(str);

        std::string word;
        while (ss >> word) {
            arguments.push_back(word);
        }

        return Parse(arguments);
    }

    bool ArgumentParser::ArgParser::Parse(std::vector<std::string> arguments) {
        for (int i = 0; i < arguments.size(); i++) {
            std::string_view arg = arguments[i];
            size_t equal_pos = arg.find_first_of('=');
            std::string name;
            std::string value{};
            bool is_short_name = false;

            if (arg[0] == '-' && arg.size() > 1 && arg[1] == '-') {
                if (equal_pos != -1) {
                    name = static_cast<std::string>(arg.substr(2, equal_pos - 2));
                    value = static_cast<std::string>(arg.substr(equal_pos + 1));
                }
                else {
                    name = static_cast<std::string>(arg.substr(2));

                }

            }
            else if (arg[0] == '-') {
                is_short_name = true;
                if (equal_pos != -1) {
                    value = static_cast<std::string>(arg.substr(equal_pos + 1));
                }

            }
            else {
                AddToPositionalArgument(static_cast<std::string>(arg));
                continue;
            }

            if (equal_pos == -1 && (!is_short_name || IsBoolArgument(arg[1]))) {
                if (is_short_name) {
                    for (int i = 1; i < arg.size(); i++) {
                        for (auto& it : bool_arguments) {
                            if (it.GetShortName() == arg[i]) {
                                it.AddValue(true);
                            }
                        }
                    }
                }
                else {
                    for (auto& it : bool_arguments) {
                        if (name == it.GetName()) {
                            it.AddValue(true);
                        }
                    }
                }
            }
            else if ((is_short_name && IsStringArgument(arg[1])) || (!is_short_name && IsStringArgument(name))) {
                if (is_short_name) {
                    for (int i = 1; i < equal_pos; i++) {
                        for (auto& it : string_arguments) {
                            if (it.GetShortName() == arg[i]) {
                                it.AddValue(value);
                            }
                        }
                    }
                }
                else {
                    for (auto& it : string_arguments) {
                        if (name == it.GetName()) {
                            it.AddValue(value);
                        }
                    }
                }
            }
            else if (!is_short_name || IsIntArgument(name)) {
                if (is_short_name) {
                    for (int i = 1; i < equal_pos; i++) {
                        for (auto& it : int_arguments) {
                            if (it.GetShortName() == arg[i]) {
                                it.AddValue(std::stoi(value));
                            }
                        }
                    }
                }
                else {
                    for (auto& it : int_arguments) {
                        if (name == it.GetName()) {
                            it.AddValue(std::stoi(value));
                        }
                    }
                }
            }
            else {
                AddToPositionalArgument(static_cast<std::string>(arg));
            }
        }
        for (auto& it : string_arguments) {
            if (!it.IsDefaultArgument() && it.IsMultiValue() && it.GetMinCountArguments() > it.GetValuesSize()) {
                return false;
            }

        }
        for (auto& it : int_arguments) {
            if (!it.IsDefaultArgument() && it.IsMultiValue() && it.GetMinCountArguments() > it.GetValuesSize()) {
                return false;
            }

        }
        for (auto& it : bool_arguments) {
            if (!it.IsDefaultArgument() && it.IsMultiValue() && it.GetMinCountArguments() > it.GetValuesSize()) {
                return false;
            }

        }
        return true;
    }

    ArgParser& ArgumentParser::ArgParser::AddStringArgument(const char short_name, const char* name, const char* description) {
        string_arguments.push_back(Argument<std::string>(short_name, name, description));
        last_argument = value_types::value_string;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddStringArgument(const char* name, const char* description) {
        string_arguments.push_back(Argument<std::string>(name, description));
        last_argument = value_types::value_string;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddIntArgument(const char short_name, const char* name, const char* description) {
        int_arguments.push_back(Argument<int>(short_name, name, description));
        last_argument = value_types::value_int;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddIntArgument(const char* name, const char* description) {
        int_arguments.push_back(Argument<int>(name, description));
        last_argument = value_types::value_int;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddFlag(const char short_name, const char* name, const char* description) {
        bool_arguments.push_back(Argument<bool>(short_name, name, description));
        last_argument = value_types::value_bool;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddFlag(const char* name, const char* description) {
        bool_arguments.push_back(Argument<bool>(name, description));
        last_argument = value_types::value_bool;
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddHelp(const char short_name, const char* name, const char* description) {
        AddFlag(short_name, name, description);

        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::AddHelp(const char* name, const char* description) {
        AddFlag(name, description);

        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::Default(const bool value) {
        bool_arguments.back().SetDefaultValue(value);
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::Default(const char* value) {
        string_arguments.back().SetDefaultValue(value);
        return *this;
    }

    void ArgumentParser::ArgParser::StoreValues(std::vector<int>& vector) {
        int_arguments.back().SetOutsideValue(vector);
    }

    void ArgumentParser::ArgParser::StoreValues(std::vector<bool>& vector) {
        bool_arguments.back().SetOutsideValue(vector);
    }

    void ArgumentParser::ArgParser::StoreValues(std::vector<std::string>& vector) {
        string_arguments.back().SetOutsideValue(vector);
    }

    void ArgumentParser::ArgParser::StoreValue(int& value) {
        int_arguments.back().SetOutsideValue(value);
    }

    void ArgumentParser::ArgParser::StoreValue(bool& value) {
        bool_arguments.back().SetOutsideValue(value);
    }

    void ArgumentParser::ArgParser::StoreValue(std::string& value) {
        string_arguments.back().SetOutsideValue(value);
    }

    ArgParser& ArgumentParser::ArgParser::Default(const int value) {
        int_arguments.back().SetDefaultValue(value);
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::Positional() {
        if (last_argument == value_types::value_int) {
            int_arguments.back().SetPositional();
            positional_argument = value_types::value_int;
            positional_argument_pos = int_arguments.size() - 1;
        }
        else if (last_argument == value_types::value_string) {
            string_arguments.back().SetPositional();
            positional_argument = value_types::value_string;
            positional_argument_pos = string_arguments.size() - 1;
        }
        else {
            bool_arguments.back().SetPositional();
            positional_argument = value_types::value_bool;
            positional_argument_pos = bool_arguments.size() - 1;
        }
        return *this;
    }

    ArgParser& ArgumentParser::ArgParser::MultiValue(const int n) {
        if (last_argument == value_types::value_int) {
            int_arguments.back().SetMinCountArguments(n);
        }
        else if (last_argument == value_types::value_string) {
            string_arguments.back().SetMinCountArguments(n);
        }
        else {
            bool_arguments.back().SetMinCountArguments(n);
        }
        return *this;
    }

    std::string ArgumentParser::ArgParser::GetStringValue(const char* name, const int n) {
        for (auto& it : string_arguments) {
            if (it.GetName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return std::string();
    }
    std::string ArgumentParser::ArgParser::GetStringValue(const char name, const int n) {
        for (auto& it : string_arguments) {
            if (it.GetShortName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return std::string();
    }
    std::string ArgumentParser::ArgParser::GetParserName() {
        return parser_name;
    }
    int ArgParser::GetIntValue(const char* name, const int n) {
        for (auto& it : int_arguments) {
            if (it.GetName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return int();
    }

    int ArgParser::GetIntValue(const char name, const int n) {
        for (auto& it : int_arguments) {
            if (it.GetShortName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return int();
    }
    bool ArgumentParser::ArgParser::GetFlag(const char name, const int n) {
        for (auto& it : bool_arguments) {
            if (it.GetShortName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return bool();
    }
    bool ArgumentParser::ArgParser::GetFlag(const char* name, const int n) {
        for (auto& it : bool_arguments) {
            if (it.GetName() == name) {
                return (it.IsDefaultArgument() ? it.GetDefaultValue() : it.GetValue()[n]);
            }
        }
        return bool();
    }

    std::string ArgumentParser::ArgParser::HelpDescription() {
        std::string help_result = parser_name + "\n\n";

        for (auto& it : bool_arguments) {
            help_result.push_back('-');
            help_result.push_back(it.GetShortName());
            help_result.append(", --" + it.GetName() + ", " + it.GetDescription());

            if (it.IsDefaultArgument()) {
                help_result.append(" [default = " + std::to_string(it.GetDefaultValue()));
                help_result.push_back(']');
            }
            if (it.IsPositional()) {
                help_result.append(" [Positional argument]");
            }

            if (it.IsMultiValue()) {
                help_result.append(" [repeated, min args = " + std::to_string(it.GetMinCountArguments()));
                help_result.push_back(']');
            }
            help_result.push_back('\n');
        }

        for (auto& it : string_arguments) {
            help_result.push_back('-');
            help_result.push_back(it.GetShortName());
            help_result.append(", --" + it.GetName() + "=<string>, " + it.GetDescription());

            if (it.IsDefaultArgument()) {
                help_result.append(" [default = " + it.GetDefaultValue());
                help_result.push_back(']');
            }

            if (it.IsPositional()) {
                help_result.append(" [Positional argument]");
            }

            if (it.IsMultiValue()) {
                help_result.append(" [repeated, min args = " + std::to_string(it.GetMinCountArguments()));
                help_result.push_back(']');
            }

            help_result.push_back('\n');
        }

        for (auto& it : int_arguments) {
            help_result.push_back('-');
            help_result.push_back(it.GetShortName());
            help_result.append(", --" + it.GetName() + "=<int>, " + it.GetDescription());

            if (it.IsDefaultArgument()) {
                help_result.append(" [default = " + std::to_string(it.GetDefaultValue()));
                help_result.push_back(']');
            }

            if (it.IsPositional()) {
                help_result.append(" [Positional argument]");
            }
            if (it.IsMultiValue()) {
                help_result.append(" [repeated, min args = " + std::to_string(it.GetMinCountArguments()));
                help_result.push_back(']');
            }

            help_result.push_back('\n');
        }

        return help_result;
    }
    bool ArgumentParser::ArgParser::Help() {
        for (auto& it : bool_arguments) {
            if (it.GetName() == "help") {
                return true;
            }
        }
        return false;
    }
    bool ArgumentParser::ArgParser::IsStringArgument(std::string name) {
        for (auto& it : string_arguments) {
            if (it.GetName() == name) {
                return true;
            }
        }

        return false;
    }

    bool ArgumentParser::ArgParser::IsIntArgument(std::string name) {
        for (auto& it : int_arguments) {
            if (it.GetName() == name) {
                return true;
            }
        }

        return false;
    }

    bool ArgumentParser::ArgParser::IsBoolArgument(std::string name) {
        for (auto& it : bool_arguments) {
            if (it.GetName() == name) {
                return true;
            }
        }

        return false;
    }

    bool ArgumentParser::ArgParser::IsStringArgument(char symbol) {
        for (auto& it : string_arguments) {
            if (it.GetShortName() == symbol) {
                return true;
            }
        }

        return false;
    }

    bool ArgumentParser::ArgParser::IsIntArgument(char symbol) {
        for (auto& it : int_arguments) {
            if (it.GetShortName() == symbol) {
                return true;
            }
        }

        return false;
    }

    bool ArgumentParser::ArgParser::IsBoolArgument(char symbol) {
        for (auto& it : bool_arguments) {
            if (it.GetShortName() == symbol) {
                return true;
            }
        }

        return false;
    }

    void ArgumentParser::ArgParser::AddToPositionalArgument(const std::string value)
    {
        switch (positional_argument) {
            case value_types::value_int:
                int_arguments[positional_argument_pos].AddValue(std::stoi(value));
                break;
            case value_types::value_string:
                string_arguments[positional_argument_pos].AddValue(value);
                break;
            case value_types::value_bool:
                bool_arguments[positional_argument_pos].AddValue(true);
                break;
        }
    }


}