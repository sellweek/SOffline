//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_TERMINALPRINTER_H
#define SEMESTRALKA_TERMINALPRINTER_H


#include <ostream>

namespace cli {
    /// Represents the basic colors that can be reproduced by ANSI terminals
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

    /**
    * Abstracts printing textual data. Implementing classes may generate
    * appropriate formatting sequences for the environment they are used in.
    * The motivation for this class is the necessity of detecting whether the program
    * is printing into a file or into a terminal and generating or not generating 
    * ANSI escape sequences.
    */
    class TerminalPrinter {
    public:
        /**
        * Construct a TerminalPrinter.
        * @param os std::ostream into which the TerminalPrinter will print its output.
        */
        TerminalPrinter(std::ostream &os);

        /**
        * Print the text in bold.
        * @param text Text to print.
        */
        virtual void bold(std::string text) = 0;

        /**
        * Print the text in italics.
        * @param text Text to print.
        */
        virtual void italic(std::string text) = 0;

        /**
        * Print underlined text.
        * @param text Text to print.
        */
        virtual void underline(std::string text) = 0;

        /**
        * Print the text in negative, for example, in a terminal with black
        * background and white text, printed text will have white background
        * and black text.
        * @param text Text to print.
        */
        virtual void reverse(std::string text) = 0;

        /**
        * Print the text in the given color.
        * @param color Color to use when printing
        * @param text Text to print.
        */
        virtual void color(Color color, std::string text) = 0;

        /**
        * Print the text without any formatting.
        * @param text Text to print.
        */
        virtual void normal(std::string text);

        /**
        * Send an std::endl to the stream.
        */
        virtual void newline();
    protected:
        std::ostream &os;
    };
}


#endif //SEMESTRALKA_TERMINALPRINTER_H
