//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPEEXCEPTION_H
#define TAPE_TAPEEXCEPTION_H

#include <stdexcept>
#include <string>

class TapeException : public std::runtime_error {
public:
    explicit TapeException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //TAPE_TAPEEXCEPTION_H
