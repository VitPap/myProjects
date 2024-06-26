#include <iostream>
#include "Lib/HamArc.h"
#include "Parser/ArgParser.h"

void AddingArguments(ArgumentParser::ArgParser &parser, std::vector<std::string> &files_value) {
    parser.AddFlag('x', "extract").Default(false);
    parser.AddFlag('l', "list").Default(false);
    parser.AddFlag('d', "delete").Default(false);
    parser.AddFlag('c', "create").Default(false);
    parser.AddStringArgument('f', "file");
    parser.AddFlag('A', "concatenate").Default(false);
    parser.AddStringArgument("files").Positional().MultiValue().StoreValues(files_value);
    parser.AddFlag('a', "append").Default(false);
    parser.AddIntArgument('b', "bits").Default(8);
}

void MakeHamArcCommands(ArgumentParser::ArgParser& parser, std::vector<std::string>& files_value) {

    if (parser.GetFlag('c')) {
        HamArc::Create(parser.GetStringValue("file"), parser.GetIntValue("bits"));
    }

    if (parser.GetFlag('a')) {
        for (std::string& i : files_value) {
            HamArc::Append(parser.GetStringValue("file"), i);
        }
    }

    if (parser.GetFlag('A')) {
        for (std::string& i : files_value) {
            HamArc::Concatenate(parser.GetStringValue("file"), i);
        }
    }

    if (parser.GetFlag('x')) {
        if (files_value.size() == 0) {
            for (std::string& i : HamArc::List(parser.GetStringValue("file"))) {
                HamArc::Extract(parser.GetStringValue("file"), i);
            }
        } else {
            for (std::string& i : files_value) {
                HamArc::Extract(parser.GetStringValue("file"), i);
            }
        }
    }

    if (parser.GetFlag('d')) {
        for (std::string& i : files_value) {
            HamArc::Delete(parser.GetStringValue("file"), i);
        }
    }

    if (parser.GetFlag('l')) {
        HamArc::List(parser.GetStringValue("file"), true);
    }
}

int main(int argc, char** argv) {
    ArgumentParser::ArgParser parser("parser");
    std::vector<std::string> files_value;

    AddingArguments(parser, files_value);

    if (!parser.Parse(argc, argv)) {
        std::cerr << "Error in parsing";
        exit(EXIT_FAILURE);
    }

    MakeHamArcCommands(parser, files_value);

    std::cout << "Everything fine!" << std::endl;

    return 0;
}