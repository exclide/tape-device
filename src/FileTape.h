//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_FILETAPE_H
#define TAPE_FILETAPE_H

#include <string>
#include "Tape.h"
#include "TapeException.h"
#include "TapeConfig.h"
#include <thread>
#include <fstream>

class FileTape : public Tape {
public:
    explicit FileTape(const TapeConfig& cfg) : cfg(cfg), tapeFile(cfg.inputFile, std::ios::in|std::ios::out|std::ios::binary) {
        if (!tapeFile.is_open()) {
            throw TapeException("Can't open tape");
        }
    }

    int Read() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.readDelay));

        tapeFile.seekg(headPointer * sizeof(int));
        int res;
        tapeFile.read((char*)&res, sizeof(int));
        return res;
    }

    void Write(int elem) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.writeDelay));

        tapeFile.seekp(headPointer * sizeof(int));
        tapeFile.write((char*)&elem, sizeof(int));
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
        return false;
    }

    size_t ElementCount() override {
        tapeFile.seekg(0, std::ios::end);
        size_t tapeSize = tapeFile.tellg();

        return tapeSize / sizeof(int);
    }

    void ResetPointer() override {
        tapeFile.seekg(0);
    }

    size_t GetCursor() const override {
        return headPointer;
    }

private:
    TapeConfig cfg;
    size_t headPointer = 0;
    std::fstream tapeFile;
};

#endif //TAPE_FILETAPE_H
