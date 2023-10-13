//
// Created by asd on 13-Oct-23.
//

#ifndef TAPEROOT_TAPESORTER_H
#define TAPEROOT_TAPESORTER_H

#include "Tape.h"
#include <iostream>
#include <utility>
#include <vector>
#include <filesystem>
#include <future>

class TapeSorter {
public:
    TapeSorter(std::shared_ptr<Tape> in, std::shared_ptr<Tape> out, size_t maxMemElements)
            : inputTape(std::move(in)), outputTape(std::move(out)), maxMemElements(maxMemElements) {
    }

    void SortTapeToOut() {
        Split();
        MergeUp();
    }

    virtual ~TapeSorter() {
    }

private:
    void Split() {
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

    std::shared_ptr<Tape> MergeTwoTapes(const std::shared_ptr<Tape>& leftTape, const std::shared_ptr<Tape>& rightTape) {
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

    void MergeUp() {
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

    void WriteToOutput() {
        while (!tapes.front()->Eot()) {
            outputTape->Write(tapes.front()->Read());
            outputTape->MoveRight();
            tapes.front()->MoveRight();
        }

        outputTape->ResetPointer();
    }

protected:
    virtual void WriteBuffer(std::vector<int>&) = 0;
    virtual std::shared_ptr<Tape> GetTmpTape() const = 0;


    std::shared_ptr<Tape> inputTape;
    std::shared_ptr<Tape> outputTape;
    std::vector<std::shared_ptr<Tape>> tapes;
    size_t maxMemElements;
};

#endif //TAPEROOT_TAPESORTER_H
