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
    explicit FileTape(const std::string& filePath, const TapeConfig& cfg)
    : cfg(cfg), tapeFile(filePath, std::ios::in|std::ios::out|std::ios::binary|std::ios::trunc) {
        if (!tapeFile.is_open()) {
            throw TapeException("Can't open tape");
        }

        tapeFile.seekg(0, std::ios::end);
        tapeSize = tapeFile.tellg() / sizeof(int);
    }

    int Read() override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.readDelay));

        tapeFile.seekg(headPointer * sizeof(int));
        int res = 0;
        tapeFile.read((char*)&res, sizeof(int));
        return res;
    }

    void Write(int elem) override {
        std::this_thread::sleep_for(std::chrono::milliseconds(cfg.writeDelay));

        tapeFile.seekg(headPointer * sizeof(int));
        tapeFile.write((char*)&elem, sizeof(int));

        if (headPointer == tapeSize) {
            tapeSize++;
        }
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
        return headPointer == tapeSize;
    }

    size_t ElementCount() override {
        return tapeSize;
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
    size_t tapeSize = 0;
    std::fstream tapeFile;
};

#endif //TAPE_FILETAPE_H
