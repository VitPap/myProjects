#include <iostream>
#include "../Lib/IndexBuilder.cpp"
#include "../Lib/IndexSearch.cpp"
#include "../Parser/ArgParser.h"
#include <string>

using namespace std;

void AddingArguments(ArgumentParser::ArgParser &parser) {
    parser.AddStringArgument('p', "dir_path").Default("C:\\Vitaly\\myProjects\\cpp");
    parser.AddFlag('b', "build").Default(false);
    parser.AddStringArgument('s', "save_dir").Default("C:\\Vitaly\\");
}

int main() {
    ArgumentParser::ArgParser parser("parser");
    AddingArguments(parser);
	std::string user_in;
    std::getline(std::cin, user_in);

    parser.Parse(user_in);

	if (parser.GetFlag('b')) {
		IndexBuilder idx;
        idx.build_index(parser.GetStringValue("dir_path"), parser.GetStringValue("save_dir"));
        std::cout << "Building index is success" << std::endl;
	} else {
        std::cout << "Enter a query" << std::endl;
        std::getline(cin, user_in);
        IndexSearch idx_search;
        auto result = idx_search.SearchDoc(user_in, parser.GetStringValue("save_dir"));
        std::cout << result.str() << std::endl;
    }

	return 0;
}
