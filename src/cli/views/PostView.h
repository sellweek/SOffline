//
// Created by Róbert Selvek on 13/05/2017.
//

#ifndef SEMESTRALKA_POSTVIEW_H
#define SEMESTRALKA_POSTVIEW_H

#include <vector>
#include <ostream>

#include <models.h>
#include <cli/TerminalPrinter.h>

namespace cli {
    class PostView {
    public:
        PostView(models::Post post, std::string owner);
        void print(bool abbreviated, TerminalPrinter &tp);
        models::Post post;
        std::string ownerName;
    };
}


#endif //SEMESTRALKA_POSTVIEW_H
