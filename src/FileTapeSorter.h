//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPESORTER_H
#define TAPE_TAPESORTER_H

#include "Tape.h"
#include "TapeSorter.h"
#include "FileTape.h"
#include <iostream>
#include <vector>
#include <filesystem>

class FileTapeSorter : public TapeSorter {
public:
    FileTapeSorter(const std::shared_ptr<FileTape>& in, const std::shared_ptr<FileTape>& out, size_t maxMemElements);

    ~FileTapeSorter() override;

private:
    void WriteBuffer(std::vector<int>& buffer) override;
    std::shared_ptr<Tape> GetTmpTape() const override;

    const std::string tempDir = "tmp";
};

#endif //TAPE_TAPESORTER_H
