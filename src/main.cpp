#include <iostream>
#include "Parsing.h"
#include "FileTape.h"
#include "MemoryTape.h"
#include "FileTapeSorter.h"
#include "TapeSorter.h"
#include "MemoryTapeSorter.h"


int main(int argc, char* argv[]) {
    TapeConfig tapeConfig;
    std::string inputTapePath, outputTapePath;

    try {
        tapeConfig = ParseCmdLineArguments(argc, argv, inputTapePath, outputTapePath);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Correct usage: \n"
                     "tape -in=input.txt -out=output.txt -cfg=config.txt";

        return EXIT_FAILURE;
    }

    std::vector<int> testInput = {2, 6, 1, 0, 7, 3, 9, 5, 4, 8};

    auto inputTape = std::make_shared<FileTape>(inputTapePath, tapeConfig);

    for (int i : testInput) {
        inputTape->Write(i);
        inputTape->MoveRight();
    }

    inputTape->ResetPointer();


    auto outputTape = std::make_shared<FileTape>(outputTapePath, tapeConfig);

    auto sorter = std::make_shared<FileTapeSorter>(inputTape, outputTape, tapeConfig.maxMemoryElements);
    sorter->SortTapeToOut();

    while (!outputTape->Eot()) {
        std::cout << outputTape->Read();
        outputTape->MoveRight();
    }

    return EXIT_SUCCESS;
}
