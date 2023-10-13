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

    void MergeUp() {
        while (tapes.size() > 1) {
            size_t writePos = 0;

            for (int i = 0; i < tapes.size(); i += 2) {
                if (i+1 == tapes.size()) {
                    tapes[writePos++] = tapes[i];
                    break;
                }

                auto leftTape = tapes[i];
                auto rightTape = tapes[i+1];

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
                    rightTape->MoveRight();
                    mergedTape->MoveRight();
                }

                mergedTape->ResetPointer();
                tapes[writePos++] = mergedTape;
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
