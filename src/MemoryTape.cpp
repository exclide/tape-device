//
// Created by asd on 13-Oct-23.
//

#include "MemoryTape.h"

MemoryTape::MemoryTape(const std::vector<int> &tape, const TapeConfig &cfg) : cfg(cfg), tape(tape) {

}

int MemoryTape::Read() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.readDelay));
    return tape[headPointer];
}

void MemoryTape::Write(int elem) {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.writeDelay));
    if (headPointer == tape.size()) {
        tape.push_back(elem);
        return;
    }
    tape[headPointer] = elem;
}

void MemoryTape::MoveLeft() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
    headPointer--;
}

void MemoryTape::MoveRight() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
    headPointer++;
}

bool MemoryTape::Eot() const {
    return headPointer == tape.size();
}

size_t MemoryTape::ElementCount() {
    return tape.size();
}

void MemoryTape::ResetPointer() {
    headPointer = 0;
}

size_t MemoryTape::GetCursor() const {
    return headPointer;
}

TapeConfig MemoryTape::GetConfig() const {
    return cfg;
}
