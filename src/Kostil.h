//
// Created by asd on 19-Oct-23.
//

#ifndef TAPEROOT_KOSTIL_H
#define TAPEROOT_KOSTIL_H

#include "Tape.h"
#include "MemoryTape.h"
#include "FileTape.h"

const std::string tempDir = "tmp";

std::shared_ptr<Tape> GetTmpTape(const std::shared_ptr<Tape>& tape) {
    static int count = 0;

    if (dynamic_cast<FileTape*>(tape.get())) {
        std::string tapePath = tempDir + "/" + "WorkingTapeN" + std::to_string(count++);
        return std::make_shared<FileTape>(tapePath, tape->GetConfig());
    } else if (dynamic_cast<MemoryTape*>(tape.get())) {
        return std::make_shared<MemoryTape>(std::vector<int>{}, tape->GetConfig());
    } else {
        throw std::runtime_error("not implemented");
    }
}

#endif //TAPEROOT_KOSTIL_H
