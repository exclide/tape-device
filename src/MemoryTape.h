//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_MEMORYTAPE_H
#define TAPE_MEMORYTAPE_H

#include <vector>
#include <thread>
#include "Tape.h"
#include "TapeConfig.h"
#include "exceptions/TapeException.h"

class MemoryTape : public Tape {
public:
    explicit MemoryTape(const std::vector<int>& tape, const TapeConfig& cfg);

    int Read() override;

    void Write(int elem) override;

    void MoveLeft() override;

    void MoveRight() override;

    bool Eot() const override;

    size_t ElementCount();

    void ResetPointer() override;

    size_t GetCursor() const override;

    TapeConfig GetConfig() const;

private:
    TapeConfig cfg;
    size_t headPointer = 0;
    std::vector<int> tape;
};

#endif //TAPE_MEMORYTAPE_H
