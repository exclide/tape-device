#include <iostream>
#include "FileTape.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Example:\n"
                     "tape -in=input.txt -out=output.txt";
    }

    return EXIT_SUCCESS;
}
