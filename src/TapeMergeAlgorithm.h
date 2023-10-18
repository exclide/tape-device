//
// Created by asd on 18-Oct-23.
//

#ifndef TAPEROOT_TAPEMERGEALGORITHM_H
#define TAPEROOT_TAPEMERGEALGORITHM_H

#include "Tape.h"
#include <memory>
#include <vector>

class TapeMergeAlgorithm {
public:
    virtual void MergeTapesToOut(std::vector<std::shared_ptr<Tape>>& tapes, const std::shared_ptr<Tape>& outTape) = 0;
};

#endif //TAPEROOT_TAPEMERGEALGORITHM_H
