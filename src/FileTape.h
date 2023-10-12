//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_FILETAPE_H
#define TAPE_FILETAPE_H

#include "Tape.h"

class FileTape : public Tape {
public:
    FileTape() : headPointer(0) {

    }

private:
    size_t headPointer;
};

#endif //TAPE_FILETAPE_H
