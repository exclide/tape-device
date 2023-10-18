//
// Created by asd on 13-Oct-23.
//

#include "TapeSorter.h"

TapeSorter::TapeSorter(
        const std::shared_ptr<Tape>& in,
        const std::shared_ptr<Tape>& out,
        const std::shared_ptr<TapeMergeAlgorithm>& mergeAlgorithm,
        size_t maxMemElements)
        : inputTape(std::move(in)), outputTape(std::move(out)), mergeAlgorithm(mergeAlgorithm), maxMemElements(maxMemElements) {
}

void TapeSorter::SortTapeToOut() {
    Split();
    mergeAlgorithm->MergeTapesToOut(tapes, outputTape);
    outputTape->ResetPointer();
}

TapeSorter::~TapeSorter() {
}

void TapeSorter::Split() {
    int extraTapes = inputTape->ElementCount() / maxMemElements;
    if (inputTape->ElementCount() % maxMemElements) {
        extraTapes++;
    }

    std::vector<int> buffer;

    while (!inputTape->Eot()) {
        buffer.push_back(inputTape->Read());
        inputTape->MoveRight();

        if (buffer.size() == maxMemElements) {
            std::sort(buffer.begin(), buffer.end(), std::greater<>()); //sort descending to avoid tape pointer reset
            WriteBuffer(buffer);
            buffer.clear();
        }
    }


    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end(), std::greater<>());
        WriteBuffer(buffer);
    }

}
