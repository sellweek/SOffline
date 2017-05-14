//
// Created by Róbert Selvek on 14/05/2017.
//

#include "ANSIPrinter.h"

cli::ANSIPrinter::ANSIPrinter(std::ostream &os) : TerminalPrinter(os) {
    reset();
}

void cli::ANSIPrinter::bold(std::string text) {
    sgr_text(1, text);
}

void cli::ANSIPrinter::italic(std::string text) {
    sgr_text(3, text);
}

void cli::ANSIPrinter::underline(std::string text) {
    sgr_text(4, text);
}

void cli::ANSIPrinter::reverse(std::string text) {
    sgr_text(7, text);
}

void cli::ANSIPrinter::color(cli::Color color, std::string text) {
    sgr_text(30 + (int) color, text);
}

void cli::ANSIPrinter::normal(std::string text) {
    reset();
    os << text;
}

void cli::ANSIPrinter::sgr_text(int code, std::string text) {
    generate_sgr(code);
    os << text;
    reset();
}

void cli::ANSIPrinter::reset() {
    generate_sgr(0);
}

void cli::ANSIPrinter::generate_sgr(int code) {
    os << "\x1B[" << code << 'm';
}

