//
// Created by asd on 13-Oct-23.
//

#include "FileTapeSorter.h"

FileTapeSorter::FileTapeSorter(
        const std::shared_ptr<FileTape> &in,
        const std::shared_ptr<FileTape> &out,
        const std::shared_ptr<TapeMergeAlgorithm>& mergeAlgorithm,
        size_t maxMemElements)
        : TapeSorter(in, out, mergeAlgorithm, maxMemElements) {
}

FileTapeSorter::~FileTapeSorter() {
    tapes.clear();
    std::filesystem::remove_all(tempDir);
}

void FileTapeSorter::WriteBuffer(std::vector<int> &buffer) {
    std::filesystem::create_directory(tempDir); //won't do anything if dir already exists
    std::string tapePath = tempDir + "/" + std::to_string(tapes.size());

    auto tmp = std::make_shared<FileTape>(tapePath, inputTape->GetConfig());

    for (int i : buffer) {
        tmp->Write(i);
        tmp->MoveRight();
    }

    tmp->MoveLeft();

    tapes.push_back(tmp);
}

std::shared_ptr<Tape> FileTapeSorter::GetTmpTape() const {
    std::string tapePath = tempDir + "/" + "mergeTmp" + std::to_string(tapes.size());
    return std::make_shared<FileTape>(tapePath, inputTape->GetConfig());
}
