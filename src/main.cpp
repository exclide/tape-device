#include <iostream>
#include <vector>
#include "FileTape.h"
#include "ParseException.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw ParseException("Wrong number of arguments. Correct usage: \n"
                             "tape -in=input.txt -out=output.txt");
    }

    const std::vector<std::string> args(argv + 1, argv + argc);

    std::string inputFile;
    std::string outputFile;

    for (const auto& arg : args) {
        if (arg.starts_with("-in=")) {
            inputFile = arg.substr(arg.find('=') + 1);
        } else if (arg.starts_with("-out=")) {
            outputFile = arg.substr(arg.find('=') + 1);
        }
    }

    if (inputFile.empty() || outputFile.empty()) {
        throw ParseException("Wrong arguments");
    }


    return EXIT_SUCCESS;
}
