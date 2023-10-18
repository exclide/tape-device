//
// Created by asd on 12-Oct-23.
//

#include <gtest/gtest.h>
#include "../src/MemoryTape.h"
#include "../src/MemoryTapeSorter.h"
#include "../src/FindMinMergeAlgorithm.h"

TEST(TestTapeSorter, TestSortingCorrect) {
    std::vector<int> inputData = {5, 1, 4, 9, 3, 2, 8, 0, 6, 7, 5, 3, 2};
    std::vector<int> sortedInput(inputData);
    std::sort(sortedInput.begin(), sortedInput.end());

    for (int i = 2; i <= inputData.size(); i++) {
        std::vector<int> outputData;

        TapeConfig cfg;
        cfg.maxMemoryElements = i;
        auto inputTape = std::make_shared<MemoryTape>(inputData, cfg);
        auto outTape = std::make_shared<MemoryTape>(std::vector<int>{}, cfg);


        auto tapeSorter = std::make_shared<MemoryTapeSorter>(
                inputTape,
                outTape,
                std::make_shared<FindMinMergeAlgorithm>(),
                cfg.maxMemoryElements);

        tapeSorter->SortTapeToOut();

        while (!outTape->Eot()) {
            outputData.push_back(outTape->Read());
            outTape->MoveRight();
        }

        ASSERT_EQ(sortedInput, outputData);
    }
}