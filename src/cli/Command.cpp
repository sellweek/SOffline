//
// Created by Róbert Selvek on 12/05/2017.
//

#include "Command.h"
#include "NoOpPrinter.h"
#include "ANSIPrinter.h"
#include <unistd.h>
#include <cstdio>
#include <iostream>


cli::Command::Command() {
    if (ttyname(fileno(stdout)) == nullptr) {
        printer = std::unique_ptr<TerminalPrinter>(new NoOpPrinter(std::cout));
    } else {
        printer = std::unique_ptr<TerminalPrinter>(new ANSIPrinter(std::cout));
    }
}

void cli::Command::log_sqlite_exception(sqlite::Exception e) {
    printer->bold("An error occurred when communicating with the database: ");
    printer->normal(e.what());
    printer->newline();
}