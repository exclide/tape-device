//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_FILETAPE_H
#define TAPE_FILETAPE_H

#include <string>
#include "Tape.h"
#include "TapeException.h"
#include "TapeConfig.h"

class FileTape : public Tape {
public:
    FileTape(const TapeConfig& cfg) : cfg(cfg) {

    }

    int read() override {

    }

    void write(int elem) override {

    }

    void moveLeft() override {
        if (headPointer == 0) return;

        headPointer--;
    }

    void moveRight() override {
        if (headPointer == tapeSize) return;

        headPointer++;
    }

private:
    size_t headPointer = 0;
    size_t tapeSize = 0;
    TapeConfig cfg;
};

#endif //TAPE_FILETAPE_H
