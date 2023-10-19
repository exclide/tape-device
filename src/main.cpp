#include <iostream>
#include "Parsing.h"
#include "FileTape.h"
#include "MemoryTape.h"
#include "FileTapeSorter.h"
#include "TapeSorter.h"
#include "MemoryTapeSorter.h"
#include "DirectWayMergeAlgorithm.h"
#include "TwoUpMergeAlgorithm.h"


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

    const int testSz = 100;
    std::vector<int> testInput(testSz);


    for (int i = 0; i < testSz; i++) {
        testInput[i] = rand() % 20;
    }

    auto inputTape = std::make_shared<FileTape>(inputTapePath, tapeConfig);

    for (int i : testInput) {
        inputTape->Write(i);
        inputTape->MoveRight();
    }

    inputTape->ResetPointer();


    auto outputTape = std::make_shared<FileTape>(outputTapePath, tapeConfig);

    auto sorter = std::make_shared<FileTapeSorter>(
            inputTape,
            outputTape,
            std::make_shared<TwoUpMergeAlgorithm>(),
            tapeConfig.maxMemoryElements);

    sorter->SortTapeToOut();

    while (!outputTape->Eot()) {
        std::cout << outputTape->Read() << " ";
        outputTape->MoveRight();
    }

    return EXIT_SUCCESS;
}
