//
// Created by asd on 13-Oct-23.
//
#include <gtest/gtest.h>
#include "../src/Parsing.h"

TEST(ParseTests, WrongNumArgsThrows) {
    std::string in, out;
    ASSERT_THROW(ParseCmdLineArguments(2, new char*[10], in, out), ParseException);
}

TEST(ParseTests, EmptyArgsThrows) {
    std::string in, out;
    char* argv[]= {
            strdup("tape.exe"),
            strdup("-in=input.txt"),
            strdup("-out=output.txt"),
                   strdup("-cfg=")
    };


    ASSERT_THROW(ParseCmdLineArguments(4, argv, in, out), ParseException);
}

TEST(ParseTests, WrongFilePath) {
    std::string in, out;
    char* argv[]= {
            strdup("tape.exe"),
            strdup("-in=dermo.txt"),
            strdup("-out=dermo.txt"),
            strdup("-cfg=dermo.txt")
    };


    ASSERT_THROW(ParseCmdLineArguments(4, argv, in, out), ParseException);
}

TEST(ParseTests, CorrectArgsNoThrow) {
    std::string in, out;

    char* argv[]= {
            strdup("tape.exe"),
            strdup("-in=../../src/tapes/input.txt"),
            strdup("-out=../../src/tapes/output.txt"),
            strdup("-cfg=../../src/cfg/config.txt")
    };


    ASSERT_NO_THROW(ParseCmdLineArguments(4, argv, in, out));
}
