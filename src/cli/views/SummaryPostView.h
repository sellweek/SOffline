//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_SUMMARYPOSTVIEW_H
#define SEMESTRALKA_SUMMARYPOSTVIEW_H

#include <sqlite/SqliteClient.h>
#include <cli/TerminalPrinter.h>
#include <models.h>
#include "PostView.h"

namespace cli {
    /**
    * Displays basic information about a single post on one line.
    */
    class SummaryPostView : public PostView {
    public:
        SummaryPostView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp) override;
    };
}




#endif //SEMESTRALKA_SUMMARYPOSTVIEW_H
