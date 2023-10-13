//
// Created by asd on 13-Oct-23.
//

#ifndef TAPEROOT_MEMORYTAPESORTER_H
#define TAPEROOT_MEMORYTAPESORTER_H

#include "MemoryTape.h"
#include "TapeSorter.h"
#include <iostream>
#include <vector>
#include <algorithm>

class MemoryTapeSorter : public TapeSorter {
public:
    MemoryTapeSorter(const std::shared_ptr<MemoryTape>& in, const std::shared_ptr<MemoryTape>& out, size_t maxMemElements)
    : TapeSorter(in, out, maxMemElements) {
    }

private:
    void WriteBuffer(std::vector<int>& buffer) override {
        std::sort(buffer.begin(), buffer.end());
        auto tmp = std::make_shared<MemoryTape>(buffer, inputTape->GetConfig());
        tapes.push_back(tmp);
    }

    std::shared_ptr<Tape> GetTmpTape() const override {
        return std::make_shared<MemoryTape>(std::vector<int>{}, inputTape->GetConfig());
    }

};

#endif //TAPEROOT_MEMORYTAPESORTER_H
