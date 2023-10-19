//
// Created by asd on 12-Oct-23.
//

#include <gtest/gtest.h>
#include "../src/MemoryTape.h"
#include "../src/MemoryTapeSorter.h"
#include "../src/FindMinMergeAlgorithm.h"
#include "../src/TwoUpMergeAlgorithm.h"

void TestBase(
        std::vector<int>& inputData,
        std::vector<int>& outputData,
        const std::shared_ptr<TapeMergeAlgorithm>& mergeAlgorithm,
        int maxMemElements) {

    TapeConfig cfg;
    cfg.maxMemoryElements = maxMemElements;
    auto inputTape = std::make_shared<MemoryTape>(inputData, cfg);
    auto outTape = std::make_shared<MemoryTape>(std::vector<int>{}, cfg);


    auto tapeSorter = std::make_shared<MemoryTapeSorter>(
            inputTape,
            outTape,
            mergeAlgorithm,
            cfg.maxMemoryElements);

    tapeSorter->SortTapeToOut();

    while (!outTape->Eot()) {
        outputData.push_back(outTape->Read());
        outTape->MoveRight();
    }

}

TEST(TestTapeSorter, TestSortingCorrectFindMinMerge) {
    std::vector<int> inputData = {5, 1, 4, 9, 3, 2, 8, 0, 6, 7, 5, 3, 2};
    std::vector<int> sortedInput(inputData);
    std::sort(sortedInput.begin(), sortedInput.end());

    for (int i = 2; i <= inputData.size(); i++) {
        std::vector<int> outputData;

        TestBase(inputData, outputData, std::make_shared<FindMinMergeAlgorithm>(), i);

        ASSERT_EQ(sortedInput, outputData);
    }
}

TEST(TestTapeSorter, TestSortingCorrectTwoUpMerge) {
    std::vector<int> inputData = {5, 1, 4, 9, 3, 2, 8, 0, 6, 7, 5, 3, 2};
    std::vector<int> sortedInput(inputData);
    std::sort(sortedInput.begin(), sortedInput.end());

    for (int i = 2; i <= inputData.size(); i++) {
        std::vector<int> outputData;

        TestBase(inputData, outputData, std::make_shared<TwoUpMergeAlgorithm>(), i);

        ASSERT_EQ(sortedInput, outputData);
    }
}