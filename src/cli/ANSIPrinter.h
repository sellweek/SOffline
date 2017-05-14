//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_ANSIPRINTER_H
#define SEMESTRALKA_ANSIPRINTER_H

#include <ostream>
#include <cli/TerminalPrinter.h>

namespace cli {
    class ANSIPrinter : public TerminalPrinter {
    public:
        ANSIPrinter(std::ostream &os);
        virtual void bold(std::string text) override;
        virtual void italic(std::string text) override;
        virtual void underline(std::string text) override;
        virtual void reverse(std::string text) override;
        virtual void color(Color color, std::string text) override;
        virtual void normal(std::string text) override;
    private:
        void sgr_text(int code, std::string text);
        void reset();
        void generate_sgr(int code);
    };
}



#endif //SEMESTRALKA_ANSIPRINTER_H
