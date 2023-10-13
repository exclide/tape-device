//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPESORTER_H
#define TAPE_TAPESORTER_H

#include "Tape.h"
#include "TapeSorter.h"
#include <iostream>
#include <vector>
#include <filesystem>

class FileTapeSorter : public TapeSorter {
public:
    FileTapeSorter(const std::shared_ptr<FileTape>& in, const std::shared_ptr<FileTape>& out, size_t maxMemElements)
    : TapeSorter(in, out, maxMemElements) {
    }

    ~FileTapeSorter() override {
        tapes.clear();
        std::filesystem::remove_all(tempDir);
    }

private:
    void WriteBuffer(std::vector<int>& buffer) override {
        std::sort(buffer.begin(), buffer.end());

        std::filesystem::create_directory(tempDir); //won't do anything if dir already exists
        std::string tapePath = tempDir + "/" + std::to_string(tapes.size());
        auto tmp = std::make_shared<FileTape>(tapePath, inputTape->GetConfig());

        for (int i : buffer) {
            tmp->Write(i);
            tmp->MoveRight();
        }

        tmp->ResetPointer();

        tapes.push_back(tmp);

    }

    std::shared_ptr<Tape> GetTmpTape() const override {
        std::string tapePath = tempDir + "/" + "mergeTmp" + std::to_string(tapes.size());
        return std::make_shared<FileTape>(tapePath, inputTape->GetConfig());
    }

    const std::string tempDir = "tmp";
};

#endif //TAPE_TAPESORTER_H
