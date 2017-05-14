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
    class SummaryPostView : public PostView {
        SummaryPostView(sqlite::Client &db, int64_t id);
        virtual void print(TerminalPrinter &tp) override;
        models::Post post;
        std::string ownerName;
    };
}




#endif //SEMESTRALKA_SUMMARYPOSTVIEW_H
