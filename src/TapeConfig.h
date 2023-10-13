//
// Created by asd on 12-Oct-23.
//

#ifndef TAPEROOT_TAPECONFIG_H
#define TAPEROOT_TAPECONFIG_H

#include <string>

struct TapeConfig {
    int readDelay = 0;
    int writeDelay = 0;
    int moveTapeDelay = 0;
    int maxMemoryElements = INT_MAX;
};


#endif //TAPEROOT_TAPECONFIG_H
