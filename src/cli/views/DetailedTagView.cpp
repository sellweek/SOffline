//
// Created by Róbert Selvek on 16/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "DetailedTagView.h"
#include "SummaryPostView.h"

cli::DetailedTagView::DetailedTagView(sqlite::Client &db, int64_t id) : TagView(db, id) {
    if (tag.wiki != 0) {
        sqlite::Statement descStmt(db, "SELECT body FROM posts_markdown WHERE id = ?");
        descStmt.bind(1, tag.wiki);
        descStmt.step();
        description = descStmt.get<std::string>(0);
    }
    sqlite::Statement questionsStmt(db, "SELECT post FROM post_tags WHERE tag = ?");
    questionsStmt.bind(1, id);
    while (questionsStmt.step()) {
        questions.push_back(SummaryPostView(db, questionsStmt.get<int64_t>(0)));
    }
}

void cli::DetailedTagView::print(cli::TerminalPrinter &tp) {
    TagView::print(tp);
    if (tag.excerpt != 0) {
        tp.normal("|A shorter version of the description is in post ");
        tp.bold(std::to_string(tag.excerpt));
    }
    if (description != "") {
        tp.newline();
        tp.bold("Description: ");
        tp.normal(description);
    }
    if (questions.size() != 0) {
        tp.newline();
        tp.reverse("Questions tagged:");
        tp.newline();
        for (auto &question: questions) {
            question.print(tp);
            tp.newline();
        }
    }
}
