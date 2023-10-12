#include <iostream>
#include "Parsing.h"


int main(int argc, char* argv[]) {
    TapeConfig cfg;

    try {
        cfg = ParseCmdLineArguments(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Correct usage: \n"
                     "tape -in=input.txt -out=output.txt -cfg=config.txt";

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
