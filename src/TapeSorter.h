//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPESORTER_H
#define TAPE_TAPESORTER_H

#include "Tape.h"
#include <iostream>
#include <vector>

template<class T>
class TapeSorter {
public:
    TapeSorter(Tape* in, size_t maxMemElements) : inputTape(in), maxMemElements(maxMemElements) {

    }

    void Sort() {

    }

private:
    Tape* inputTape;
    size_t maxMemElements;
    std::vector<Tape*> tapes;
    Tape* outputTape;
};

#endif //TAPE_TAPESORTER_H
