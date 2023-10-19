//
// Created by asd on 18-Oct-23.
//

#ifndef TAPEROOT_TWOUPMERGEALGORITHM_H
#define TAPEROOT_TWOUPMERGEALGORITHM_H

#include "TapeMergeAlgorithm.h"
#include "TapeSorter.h"
#include <future>
#include "Kostil.h"

template<class Comp>
std::shared_ptr<Tape> MergeTwoTapes(const std::shared_ptr<Tape>& left, const std::shared_ptr<Tape>& right, Comp cmp) {
    std::shared_ptr<Tape> mergedTape = GetTmpTape(left);

    while (left->GetCursor() != -1 && right->GetCursor() != -1) {
        int leftElem = left->Read();
        int rightElem = right->Read();

        if (cmp(leftElem, rightElem)) {
            mergedTape->Write(leftElem);
            left->MoveLeft();
        } else {
            mergedTape->Write(rightElem);
            right->MoveLeft();
        }

        mergedTape->MoveRight();
    }

    while (left->GetCursor() != -1) {
        mergedTape->Write(left->Read());
        left->MoveLeft();
        mergedTape->MoveRight();
    }

    while (right->GetCursor() != -1) {
        mergedTape->Write(right->Read());
        right->MoveLeft();
        mergedTape->MoveRight();
    }

    mergedTape->MoveLeft();

    return mergedTape;
}

std::shared_ptr<Tape> GetReverseTape(const std::shared_ptr<Tape>& tape) {
    std::shared_ptr<Tape> tmpTape = GetTmpTape(tape);

    while (tape->GetCursor() != -1) {
        tmpTape->Write(tape->Read());
        tmpTape->MoveRight();
        tape->MoveLeft();
    }

    tmpTape->MoveLeft();

    return tmpTape;
}

void WriteToOut(const std::shared_ptr<Tape>& tape, const std::shared_ptr<Tape>& outTape) {
    while (tape->GetCursor() != -1) {
        outTape->Write(tape->Read());
        outTape->MoveRight();
        tape->MoveLeft();
    }
}


class TwoUpMergeAlgorithm : public TapeMergeAlgorithm {
public:
    TwoUpMergeAlgorithm() {
    }

    void MergeTapesToOut(std::vector<std::shared_ptr<Tape>>& tapes, const std::shared_ptr<Tape>& outTape) override {
        size_t iters = 0;

        while (tapes.size() > 1) {
            size_t writePos = 0;
            iters++;


            std::vector<std::future<std::shared_ptr<Tape>>> tapeMergeFutures;

            for (int i = 0; i < tapes.size() - 1; i += 2) {
                if (iters % 2) {
                    tapeMergeFutures.emplace_back(
                            std::async(
                                    std::launch::async, [&tapes, i] {
                                        return MergeTwoTapes(tapes[i], tapes[i + 1], std::less<>());
                                    }));
                } else {
                    tapeMergeFutures.emplace_back(
                            std::async(
                                    std::launch::async, [&tapes, i] {
                                        return MergeTwoTapes(tapes[i], tapes[i + 1], std::greater<>());
                                    }));
                }
            }

            for (auto& f : tapeMergeFutures) {
                tapes[writePos++] = f.get();
            }

            if (tapes.size() % 2) {
                tapes[writePos++] = GetReverseTape(tapes.back());
            }

            while (tapes.size() != writePos) {
                tapes.pop_back();
            }

        }

        if (iters % 2) {
            WriteToOut(GetReverseTape(tapes.back()), outTape);
        } else {
            WriteToOut(tapes.back(), outTape);
        }
    }

    std::vector<std::shared_ptr<Tape>> inTapes;
    std::vector<std::shared_ptr<Tape>> outTapes;
};

#endif //TAPEROOT_TWOUPMERGEALGORITHM_H
