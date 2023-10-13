#include <iostream>
#include "Parsing.h"
#include "FileTape.h"
#include "MemoryTape.h"


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

    Tape* tape = new FileTape(cfg);
    for (int i = 0; i < 10; i++) {
        tape->Write(i);
        tape->MoveRight();
    }

    return EXIT_SUCCESS;
}
