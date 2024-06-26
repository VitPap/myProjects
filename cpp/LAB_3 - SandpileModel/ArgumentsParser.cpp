#include "ArgumentsParser.hpp"

void Clear(char* &name, char* &value) {
    delete[] name;
    delete[] value;
}

bool ParseArguments(char*& name, char*& value, int &value_size) {
    if (strcmp(name, "--output") == 0 || strcmp(name, "-o") == 0) {
        if (Flags::is_output_used) {
            Clear(name, value);
            std::cerr << "Wrong input. To much arguments: -o or --output";
            return false;
        }

        delete[] Arguments::output;
        Arguments::output = new char[value_size + 1];
        Arguments::output[value_size] = '\0';

        for (int i = 0; i < value_size; ++i) {
            Arguments::output[i] = value[i];
        }

        Flags::is_output_used = true;
    }
    else if (strcmp(name, "--input") == 0 || strcmp(name, "-i") == 0) {
        if (Flags::is_input_used) {
            Clear(name, value);
            std::cerr << "Wrong input. To much arguments: -i or --input";
            return false;
        }

        delete[] Arguments::input;
        Arguments::input = new char[value_size + 1];
        Arguments::input[value_size] = '\0';

        for (int i = 0; i < value_size; ++i) {
            Arguments::input[i] = value[i];
        }

        Flags::is_input_used = true;
    }
    else if (strcmp(name, "--freq") == 0 || strcmp(name, "-f") == 0) {
        if (Flags::is_freq_used) {
            Clear(name, value);
            std::cerr << "Wrong input. To much arguments: -f or --freq";
            return false;
        }

        Flags::is_freq_used = true;
        std::from_chars(value, value + value_size, Arguments::freq);
    }
    else if (strcmp(name, "--max-iter") == 0 || strcmp(name, "-m") == 0) {
        if (Flags::is_max_iter_used) {
            Clear(name, value);
            std::cerr << "Wrong input. To much arguments: -m or --max-iter";
            return false;
        }

        Flags::is_max_iter_used = true;
        std::from_chars(value, value + value_size, Arguments::max_iter);
    }

    return true;
}

bool MakeArguments(char** arguments, int size) {
    bool is_name;
    int name_size;
    int value_size;

    for (int i = 0; i < size; ++i) {
        is_name = true;
        name_size = value_size = 0;

        for (int j = 0; j < std::strlen(arguments[i]); ++j) {
            if (arguments[i][j] == '=') {
                is_name = false;
            
            } else if (!is_name) {
                value_size++;

            } else {
                name_size++;
            
            }
        }

        is_name = true;
        char* value = new char[value_size + 1];
        char* name = new char[name_size + 1];
        

        for (int j = 0; j < std::strlen(arguments[i]); ++j) {
            if (arguments[i][j] == '=') {
                is_name = false;

            } else if (!is_name) {
                value[j - name_size - 1] = arguments[i][j];

            } else {
                name[j] = arguments[i][j];

            }
        }

        name[name_size] = value[value_size] = '\0';
        ParseArguments(name, value, value_size);
        Clear(name, value);
    }
    return true;
}