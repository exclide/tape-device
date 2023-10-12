//
// Created by asd on 12-Oct-23.
//

#ifndef TAPEROOT_TAPECONFIG_H
#define TAPEROOT_TAPECONFIG_H

#include <string>

struct TapeConfig {
    std::string inputFile;
    std::string outputFile;

    int readDelay = 0;
    int writeDelay = 0;
    int moveTapeDelay = 0;
    int memoryBlockSize = INT_MAX;
};

#endif //TAPEROOT_TAPECONFIG_H
