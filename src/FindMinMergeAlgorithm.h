//
// Created by asd on 18-Oct-23.
//

#ifndef TAPEROOT_FINDMINMERGEALGORITHM_H
#define TAPEROOT_FINDMINMERGEALGORITHM_H

#include "TapeMergeAlgorithm.h"

class FindMinMergeAlgorithm : public TapeMergeAlgorithm {
public:
    void MergeTapesToOut(std::vector<std::shared_ptr<Tape>>& tapes, const std::shared_ptr<Tape>& outTape) override {
        while (!tapes.empty()) {
            int minTapeIndex = 0;
            int minElem = tapes[minTapeIndex]->Read();

            for (int i = 0; i < tapes.size(); i++) {
                if (int elem = tapes[i]->Read(); elem < minElem) {
                    minTapeIndex = i;
                    minElem = elem;
                }
            }

            outTape->Write(minElem);
            outTape->MoveRight();

            tapes[minTapeIndex]->MoveLeft();
            if (tapes[minTapeIndex]->GetCursor() == -1) { //all elems viewed, remove tape
                std::swap(tapes[minTapeIndex], tapes.back());
                tapes.pop_back();
            }
        }
    }
};

#endif //TAPEROOT_FINDMINMERGEALGORITHM_H
