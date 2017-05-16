//
// Created by Róbert Selvek on 16/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "SummaryTagView.h"

cli::SummaryTagView::SummaryTagView(sqlite::Client &db, int64_t id) : TagView(db, id) {
    if (tag.excerpt != 0) {
        sqlite::Statement descriptionStmt(db, "SELECT body FROM posts_markdown WHERE id = ?");
        descriptionStmt.bind(1, tag.excerpt);
        descriptionStmt.step();
        description = descriptionStmt.get<std::string>(0);
    }
}

void cli::SummaryTagView::print(cli::TerminalPrinter &tp) {
    TagView::print(tp);
    if (tag.wiki != 0) {
        tp.normal("|Full description in post ");
        tp.bold(std::to_string(tag.wiki));
    }
    if (tag.excerpt != 0) {
        tp.newline();
        tp.normal(description);
    }
}
