//
// Created by Róbert Selvek on 13/05/2017.
//

#ifndef SEMESTRALKA_POSTVIEW_H
#define SEMESTRALKA_POSTVIEW_H

#include <vector>
#include <ostream>

#include <models.h>
#include <cli/TerminalPrinter.h>
#include <sqlite/SqliteClient.h>
#include "CommentView.h"

namespace cli {
    class PostView {
    public:
        PostView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp);
        models::Post post;
        std::string ownerName;
    };
}


#endif //SEMESTRALKA_POSTVIEW_H
