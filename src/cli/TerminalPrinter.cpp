//
// Created by Róbert Selvek on 14/05/2017.
//

#include "TerminalPrinter.h"

#include <ostream>

cli::TerminalPrinter::TerminalPrinter(std::ostream &os): os(os) {}

void cli::TerminalPrinter::normal(std::string text) {
    os << text;
}

void cli::TerminalPrinter::newline() {
    os << std::endl;
}
