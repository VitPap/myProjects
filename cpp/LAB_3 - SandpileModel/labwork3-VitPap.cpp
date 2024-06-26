#include "labwork3-VitPap.h"

int main(int argc, char** argv) {

    bool good = MakeArguments(argv, argc);
    if (good) {
        std::ifstream input(Arguments::input);
        input.open(Arguments::input);
        
        if (!input.is_open()) {
            std::cerr << "File not found";
            exit(EXIT_FAILURE);
        }

        Matrix main_matrix;
        SandPile(input, main_matrix);
    } else {
        std::cerr << "Error in making arguments";
        exit(EXIT_FAILURE);
    }

    system("pause");

    return 0;
}
