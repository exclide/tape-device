//
// Created by asd on 13-Oct-23.
//

#include "TapeSorter.h"

TapeSorter::TapeSorter(std::shared_ptr<Tape> in, std::shared_ptr<Tape> out, size_t maxMemElements)
        : inputTape(std::move(in)), outputTape(std::move(out)), maxMemElements(maxMemElements) {
}

void TapeSorter::SortTapeToOut() {
    Split();
    MergeUp();
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
            WriteBuffer(buffer);
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        WriteBuffer(buffer);
    }

}

std::shared_ptr<Tape>
TapeSorter::MergeTwoTapes(const std::shared_ptr<Tape> &leftTape, const std::shared_ptr<Tape> &rightTape) {
    std::shared_ptr<Tape> mergedTape = GetTmpTape();

    while (!leftTape->Eot() && !rightTape->Eot()) {
        int leftElem = leftTape->Read();
        int rightElem = rightTape->Read();

        if (leftElem < rightElem) {
            mergedTape->Write(leftElem);
            leftTape->MoveRight();
        } else {
            mergedTape->Write(rightElem);
            rightTape->MoveRight();
        }

        mergedTape->MoveRight();
    }

    while (!leftTape->Eot()) {
        mergedTape->Write(leftTape->Read());
        leftTape->MoveRight();
        mergedTape->MoveRight();
    }

    while (!rightTape->Eot()) {
        mergedTape->Write(rightTape->Read());
        rightTape->MoveRight();
        mergedTape->MoveRight();
    }

    mergedTape->ResetPointer();

    return mergedTape;
}

void TapeSorter::MergeUp() {
    while (tapes.size() > 1) {
        size_t writePos = 0;

        std::vector<std::future<std::shared_ptr<Tape>>> tapeMergeFutures;


        for (int i = 0; i < tapes.size() - 1; i += 2) {
            tapeMergeFutures.emplace_back(
                    std::async(std::launch::async, &TapeSorter::MergeTwoTapes, this, tapes[i], tapes[i+1]));
        }

        for (auto& f : tapeMergeFutures) {
            tapes[writePos++] = f.get();
        }

        if (tapes.size() % 2) {
            tapes[writePos++] = tapes.back();
        }

        while (tapes.size() != writePos) {
            tapes.pop_back();
        }
    }

    WriteToOutput();
}

void TapeSorter::WriteToOutput() {
    while (!tapes.front()->Eot()) {
        outputTape->Write(tapes.front()->Read());
        outputTape->MoveRight();
        tapes.front()->MoveRight();
    }

    outputTape->ResetPointer();
}
