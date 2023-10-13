//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_MEMORYTAPE_H
#define TAPE_MEMORYTAPE_H

#include <vector>
#include "Tape.h"
#include "TapeConfig.h"
#include "TapeException.h"
#include <thread>

class MemoryTape : public Tape {
public:
    explicit MemoryTape(const std::vector<int>& tape, const TapeConfig& cfg) : cfg(cfg), tape(tape) {

    }

    int Read() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.readDelay));
        return tape[headPointer];
    }

    void Write(int elem) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.writeDelay));
        if (headPointer == tape.size()) {
            tape.push_back(elem);
            return;
        }
        tape[headPointer] = elem;
    }

    void MoveLeft() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
        headPointer--;
    }

    void MoveRight() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
        headPointer++;
    }

    bool Eot() const override {
        return headPointer == tape.size();
    }

    size_t ElementCount() {
        return tape.size();
    }

    void ResetPointer() override {
        headPointer = 0;
    }

    size_t GetCursor() const override {
        return headPointer;
    }

    TapeConfig GetConfig() const {
        return cfg;
    }

private:
    TapeConfig cfg;
    size_t headPointer = 0;
    std::vector<int> tape;
};

#endif //TAPE_MEMORYTAPE_H
