//
// Created by Róbert Selvek on 12/05/2017.
//

#include "Command.h"
#include "NoOpPrinter.h"
#include "ANSIPrinter.h"
#include <unistd.h>
#include <cstdio>
#include <iostream>

std::unique_ptr<cli::TerminalPrinter> cli::Command::getPrinter() {
    if (ttyname(fileno(stdout)) == nullptr) {
        return std::unique_ptr<TerminalPrinter>(new NoOpPrinter(std::cout));
    } else {
        return std::unique_ptr<TerminalPrinter>(new ANSIPrinter(std::cout));
    }
}
