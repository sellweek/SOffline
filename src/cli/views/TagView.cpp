//
// Created by Róbert Selvek on 16/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "TagView.h"
#include "helpers.h"

cli::TagView::TagView(sqlite::Client &db, int64_t id) {
    sqlite::Statement select(db, "SELECT * FROM tags WHERE id = ?");
    select.bind(1, id);
    if (!select.step()) {
        throw DoesNotExistException();
    }
    tag = select.get_mapped<models::Tag>();
    sqlite::Statement countStmt(db, "SELECT COUNT(*) FROM post_tags WHERE tag = ?");
    questionCount = execute_simple_int_statement(countStmt, id);
    if (tag.excerpt != 0) {
        sqlite::Statement descriptionStmt(db, "SELECT body FROM posts_markdown WHERE id = ?");
        descriptionStmt.bind(1, tag.excerpt);
        descriptionStmt.step();
        description = descriptionStmt.get<std::string>(0);
    }
}

void cli::TagView::print(cli::TerminalPrinter &tp) {
    tp.normal(std::to_string(tag.id) + "|");
    tp.bold(tag.name);
    tp.normal("|");
    tp.bold(std::to_string(questionCount));
    tp.normal("Q");
    if (tag.wiki != 0) {
        tp.normal("|Full description in post ");
        tp.bold(std::to_string(tag.wiki));
    }
    if (tag.excerpt != 0) {
        tp.newline();
        tp.normal(description);
    }
}
