//
// Created by asd on 12-Oct-23.
//

#ifndef TAPEROOT_PARSING_H
#define TAPEROOT_PARSING_H

#include <string>
#include <vector>
#include <fstream>
#include "exceptions/ParseException.h"
#include "TapeConfig.h"

std::string splitAfterDelimiter(const std::string& str, char delimiter = '=') {
    return str.substr(str.find(delimiter) + 1);
}

void ParseConfigFile(const std::string& configFile, TapeConfig& cfg) {
    std::ifstream input(configFile);

    if (!input.is_open()) {
        throw ParseException("Can't open file with path: " + configFile);
    }

    std::string cfgOption;

    while (input >> cfgOption) {
        if (cfgOption.starts_with("ReadDelay=")) {
            cfg.readDelay = std::stoi(splitAfterDelimiter(cfgOption));
        } else if (cfgOption.starts_with("WriteDelay=")) {
            cfg.writeDelay = std::stoi(splitAfterDelimiter(cfgOption));
        } else if (cfgOption.starts_with("MoveTapeDelay=")) {
            cfg.moveTapeDelay = std::stoi(splitAfterDelimiter(cfgOption));
        } else if (cfgOption.starts_with("MaxMemoryElements=")) {
            cfg.maxMemoryElements = std::stoi(splitAfterDelimiter(cfgOption));
        }
    }

}

TapeConfig ParseCmdLineArguments(int argc, char* argv[], std::string& inputTape, std::string& outputTape) {
    if (argc < 4) {
        throw ParseException("Wrong number of arguments");
    }

    const std::vector<std::string> args(argv + 1, argv + argc);

    std::string configFile;

    for (const auto& arg : args) {
        if (arg.starts_with("-in=")) {
            inputTape = splitAfterDelimiter(arg);
        } else if (arg.starts_with("-out=")) {
            outputTape = splitAfterDelimiter(arg);
        } else if (arg.starts_with("-cfg=")) {
            configFile = splitAfterDelimiter(arg);
        }
    }

    if (inputTape.empty() || outputTape.empty() || configFile.empty()) {
        throw ParseException("Wrong arguments");
    }

    TapeConfig cfg;

    ParseConfigFile(configFile, cfg);

    return cfg;
}

#endif //TAPEROOT_PARSING_H
