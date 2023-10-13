//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPE_H
#define TAPE_TAPE_H

class Tape {
public:
    virtual int Read() = 0;
    virtual void Write(int elem) = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;
    virtual bool Eot() const = 0;
    virtual size_t ElementCount() = 0;
    virtual void ResetPointer() = 0;
    virtual size_t GetCursor() const = 0;
};

#endif //TAPE_TAPE_H
