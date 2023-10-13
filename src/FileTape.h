//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_FILETAPE_H
#define TAPE_FILETAPE_H

#include <string>
#include "Tape.h"
#include "exceptions/TapeException.h"
#include "TapeConfig.h"
#include <thread>
#include <fstream>

class FileTape : public Tape {
public:
    explicit FileTape(const std::string& filePath, const TapeConfig& cfg);

    int Read() override;

    void Write(int elem) override;

    void MoveLeft() override;

    void MoveRight() override;

    bool Eot() const override;

    size_t ElementCount() override;

    void ResetPointer() override;

    size_t GetCursor() const override;

    TapeConfig GetConfig() const;

private:
    TapeConfig cfg;
    size_t headPointer = 0;
    size_t tapeSize = 0;
    std::fstream tapeFile;
};


#endif //TAPE_FILETAPE_H
