//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_NOOPPRINTER_H
#define SEMESTRALKA_NOOPPRINTER_H

#include <ostream>

#include <cli/TerminalPrinter.h>

namespace cli {
    class NoOpPrinter : public TerminalPrinter {
    public:
        NoOpPrinter(std::ostream &os);
        virtual void bold(std::string text) override;
        virtual void italic(std::string text) override;
        virtual void underline(std::string text) override;
        virtual void reverse(std::string text) override;
        virtual void color(Color color, std::string text) override;
    };
}



#endif //SEMESTRALKA_NOOPPRINTER_H
