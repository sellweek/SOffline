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
}

void cli::TagView::print(cli::TerminalPrinter &tp) {
    tp.normal(std::to_string(tag.id) + "|");
    tp.bold(tag.name);
    tp.normal("|");
    tp.bold(std::to_string(questionCount));
    tp.normal("Q");
}
