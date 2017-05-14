//
// Created by Róbert Selvek on 14/05/2017.
//

#include "NoOpPrinter.h"

cli::NoOpPrinter::NoOpPrinter(std::ostream &os) : TerminalPrinter(os) {}

void cli::NoOpPrinter::bold(std::string text) {
    TerminalPrinter::normal(text);
}

void cli::NoOpPrinter::italic(std::string text) {
    TerminalPrinter::normal(text);
}

void cli::NoOpPrinter::underline(std::string text) {
    TerminalPrinter::normal(text);
}

void cli::NoOpPrinter::reverse(std::string text) {
    TerminalPrinter::normal(text);
}

void cli::NoOpPrinter::color(cli::Color color, std::string text) {
    TerminalPrinter::normal(text);
}
