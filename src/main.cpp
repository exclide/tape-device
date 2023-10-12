#include <iostream>
#include "Parsing.h"


int main(int argc, char* argv[]) {
    auto cfg = ParseCmdLineArguments(argc, argv);

    std::cout << cfg.outputFile << std::endl;
    std::cout << cfg.inputFile << std::endl;
    std::cout << cfg.readDelay << std::endl;
    std::cout << cfg.writeDelay << std::endl;
    std::cout << cfg.moveTapeDelay << std::endl;

    return EXIT_SUCCESS;
}
