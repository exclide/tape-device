//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPE_H
#define TAPE_TAPE_H

class Tape {
public:
    virtual int read() = 0;
    virtual void write(int elem) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
};

#endif //TAPE_TAPE_H
