//
// Created by asd on 12-Oct-23.
//

#ifndef TAPE_TAPEEXCEPTION_H
#define TAPE_TAPEEXCEPTION_H

#include <exception>
#include <string>

class TapeException : public std::exception {
public:
    explicit TapeException(const std::string& msg) : msg(msg) {}

    const char* what() const noexcept override {
        return msg.data();
    }

private:
    std::string msg;
};

#endif //TAPE_TAPEEXCEPTION_H
