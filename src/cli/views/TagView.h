//
// Created by Róbert Selvek on 16/05/2017.
//

#ifndef SEMESTRALKA_TAGVIEW_H
#define SEMESTRALKA_TAGVIEW_H

#include <sqlite/SqliteClient.h>
#include <cli/TerminalPrinter.h>
#include <models.h>

namespace cli {
    class TagView {
    public:
        TagView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp);
    private:
        models::Tag tag;
        int64_t questionCount;
        std::string description;
    };
}


#endif //SEMESTRALKA_TAGVIEW_H
