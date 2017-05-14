//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_TERMINALPRINTER_H
#define SEMESTRALKA_TERMINALPRINTER_H


#include <ostream>

namespace cli {
    enum class Color {
        Black = 0,
        Red = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4,
        Magenta = 5,
        Cyan = 6,
        White = 7
    };
    class TerminalPrinter {
    public:
        TerminalPrinter(std::ostream &os);
        virtual void bold(std::string text) = 0;
        virtual void italic(std::string text) = 0;
        virtual void underline(std::string text) = 0;
        virtual void reverse(std::string text) = 0;
        virtual void color(Color color, std::string text) = 0;
        virtual void normal(std::string text);
        virtual void newline();
    protected:
        std::ostream &os;
    };
}


#endif //SEMESTRALKA_TERMINALPRINTER_H
