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
    TapeSorter(std::shared_ptr<Tape> in, std::shared_ptr<Tape> out, size_t maxMemElements);

    void SortTapeToOut();

    virtual ~TapeSorter();

private:
    void Split();

    std::shared_ptr<Tape> MergeTwoTapes(const std::shared_ptr<Tape>& leftTape, const std::shared_ptr<Tape>& rightTape);

    void MergeUp();

    void WriteToOutput();

protected:
    virtual void WriteBuffer(std::vector<int>&) = 0;
    virtual std::shared_ptr<Tape> GetTmpTape() const = 0;


    std::shared_ptr<Tape> inputTape;
    std::shared_ptr<Tape> outputTape;
    std::vector<std::shared_ptr<Tape>> tapes;
    size_t maxMemElements;
};

#endif //TAPEROOT_TAPESORTER_H
