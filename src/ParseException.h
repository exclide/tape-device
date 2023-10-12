//
// Created by asd on 12-Oct-23.
//

#ifndef TAPEROOT_PARSEEXCEPTION_H
#define TAPEROOT_PARSEEXCEPTION_H

#include <stdexcept>
#include <string>

class ParseException : public std::runtime_error {
public:
    explicit ParseException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif //TAPEROOT_PARSEEXCEPTION_H
