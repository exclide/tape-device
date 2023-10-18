//
// Created by asd on 13-Oct-23.
//

#ifndef TAPEROOT_TAPESORTER_H
#define TAPEROOT_TAPESORTER_H

#include "Tape.h"
#include "TapeMergeAlgorithm.h"
#include <iostream>
#include <utility>
#include <vector>
#include <filesystem>
#include <future>

class TapeSorter {
public:
    TapeSorter(
            const std::shared_ptr<Tape>& in,
            const std::shared_ptr<Tape>& out,
            const std::shared_ptr<TapeMergeAlgorithm>& mergeAlgorithm,
            size_t maxMemElements);

    virtual ~TapeSorter();

    void SortTapeToOut();
    virtual std::shared_ptr<Tape> GetTmpTape() const = 0;

private:
    void Split();

protected:
    virtual void WriteBuffer(std::vector<int>&) = 0;


    std::shared_ptr<Tape> inputTape;
    std::shared_ptr<Tape> outputTape;
    std::vector<std::shared_ptr<Tape>> tapes;
    std::shared_ptr<TapeMergeAlgorithm> mergeAlgorithm;
    size_t maxMemElements;
};

#endif //TAPEROOT_TAPESORTER_H
