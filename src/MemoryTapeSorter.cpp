//
// Created by asd on 13-Oct-23.
//

#include "MemoryTapeSorter.h"

MemoryTapeSorter::MemoryTapeSorter(const std::shared_ptr<MemoryTape> &in, const std::shared_ptr<MemoryTape> &out,
                                   size_t maxMemElements)
        : TapeSorter(in, out, maxMemElements) {
}

void MemoryTapeSorter::WriteBuffer(std::vector<int> &buffer) {
    std::sort(buffer.begin(), buffer.end());
    auto tmp = std::make_shared<MemoryTape>(buffer, inputTape->GetConfig());
    tapes.push_back(tmp);
}

std::shared_ptr<Tape> MemoryTapeSorter::GetTmpTape() const {
    return std::make_shared<MemoryTape>(std::vector<int>{}, inputTape->GetConfig());
}
