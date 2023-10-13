//
// Created by asd on 13-Oct-23.
//

#include "FileTape.h"

FileTape::FileTape(const std::string &filePath, const TapeConfig &cfg)
        : cfg(cfg), tapeFile(filePath, std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc) {
    if (!tapeFile.is_open()) {
        throw TapeException("Can't open tape");
    }

    tapeFile.seekg(0, std::ios::end);
    tapeSize = tapeFile.tellg() / sizeof(int);
}

int FileTape::Read() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.readDelay));

    tapeFile.seekg(headPointer * sizeof(int));
    int res = 0;
    tapeFile.read((char*)&res, sizeof(int));
    return res;
}

void FileTape::Write(int elem) {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.writeDelay));

    tapeFile.seekg(headPointer * sizeof(int));
    tapeFile.write((char*)&elem, sizeof(int));

    if (headPointer == tapeSize) {
        tapeSize++;
    }
}

void FileTape::MoveLeft() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
    headPointer--;
}

void FileTape::MoveRight() {
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.moveTapeDelay));
    headPointer++;
}

bool FileTape::Eot() const {
    return headPointer == tapeSize;
}

size_t FileTape::ElementCount() {
    return tapeSize;
}

void FileTape::ResetPointer() {
    headPointer = 0;
}

size_t FileTape::GetCursor() const {
    return headPointer;
}

TapeConfig FileTape::GetConfig() const {
    return cfg;
}