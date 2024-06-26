#include <iostream>
#include <fstream>
#include <string> 
#include <string_view>

enum err {
    OK = 0,
    FAILURE = 1,
};

struct Arguments {
    err err_status = OK;
    size_t lines = 0;
    const char* filename = nullptr;
    bool is_tail = false;
    char delimiter = '\n';
};

char ParseDelimiter(const std::string& delimiter) {
    char char_delimiter = delimiter[0];

    if (delimiter == "'\\n'" || delimiter == "\\n") {
        char_delimiter = '\n';
    } else if (delimiter == "'\\v'" || delimiter == "\\v") {
        char_delimiter = '\v';
    } else if (delimiter == "'\\t'" || delimiter == "\\t") {
        char_delimiter = '\t';
    } else if (delimiter == "'\\r'" || delimiter == "\\r") {
        char_delimiter = '\r';
    } else if (delimiter == "'\\f'" || delimiter == "\\f") {
        char_delimiter = '\f';
    } else if (delimiter == "'\\b'" || delimiter == "\\b") {
        char_delimiter = '\b';
    } else if (delimiter == "'\\a'" || delimiter == "\\a") {
        char_delimiter = '\a';
    } else if (delimiter == "'\\'"  || delimiter == "\\")  {
        char_delimiter = '\\';
    } else if (delimiter == "'\\?'" || delimiter == "\\?") {
        char_delimiter = '\?';
    } else if (delimiter == "'\"'" || delimiter == "\"")   {
        char_delimiter = '\"';
    } else if (delimiter == "'\\''" || delimiter == "\\'") {
        char_delimiter = '\'';
    }

    return char_delimiter;
}

Arguments ParseArguments(int argc, char** argv) {
    Arguments arguments;
    if (argc < 2) {
        std::cerr << "Missed necessary argument: filename";

        arguments.err_status = FAILURE;
        return arguments;
    }
    arguments.filename = argv[argc - 1];

    for (int i = 1; i < argc - 1; i++) {
        std::string_view arg = argv[i];
        if (arg.find("--delimiter=") == 0) {
            arguments.delimiter = ParseDelimiter(arg.substr(12));

        } else if (arg == "-d") {
            arguments.delimiter = ParseDelimiter(argv[i + 1]);
            i += 1;

        } else if (arg == "-t" || arg == "--tail") {
            arguments.is_tail = true;
        } else if (arg.find("--lines=") == 0) {
            int begin_pos = arg.find("=") + 1;
               
            if (begin_pos == arg.size()) {
                std::cerr << "Wrong presentation of lines"; 

                arguments.err_status = FAILURE;
                return arguments;
            }

            arguments.lines = std::stoi(arg.substr(begin_pos));

        } else if (arg == "-l") {
            arguments.lines = std::atoi(argv[i + 1]);
            if (i + 1 == argc - 1 || !std::isdigit(*argv[i + 1]) || arguments.lines  < 1) {
                std::cerr << "Wrong presentation of lines";

                arguments.err_status = FAILURE;
                return arguments;
            }
            
            i += 1;
        } else {
            std::cerr << "Entered wrong argument: " << arg;
            arguments.err_status = FAILURE;
            return arguments;
        }
    }

    if (arguments.is_tail && arguments.lines == 0) {
        arguments.err_status = FAILURE;
        std::cerr << "Entered tail argument, but missed lines argument";
    }

    return arguments;
}

int PrintFile(const Arguments &arguments) {
    std::ifstream file(arguments.filename);
    if (!file.is_open()) {
        std::cerr << "File doesn`t exist or wrong filename, entered FILENAME: " << arguments.filename;

        return EXIT_FAILURE;
    }

    if (!arguments.is_tail) {
        int printed_lines = 0;
        char ch;

        while (file.get(ch) && (printed_lines < arguments.lines || arguments.lines == 0)) {
            if (ch == arguments.delimiter) {
                printed_lines++;
            }
            std::cout << ch;
        }
    
    } else {
        int total_lines = 1;
        char ch;

        while (file.get(ch)) {
            if (ch == arguments.delimiter) {
                total_lines++;
            }
        }
        file.clear();
        file.seekg(0);

        int skiped_lines = 0;
        while (file.get(ch)) {
            if (skiped_lines + arguments.lines >= total_lines) {
                std::cout << ch;
            }
            if (ch == arguments.delimiter) {
                skiped_lines++;
            }
        }
    }
    
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    const Arguments arguments = ParseArguments(argc, argv);

    if (arguments.err_status == FAILURE) {
        return EXIT_FAILURE;
    }

    return PrintFile(arguments);
}