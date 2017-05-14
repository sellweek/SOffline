//
// Created by Róbert Selvek on 14/05/2017.
//


#include "CommentView.h"
#include "helpers.h"
#include <sqlite/sqlite_statement.h>

cli::CommentView::CommentView(sqlite::Client &db, int64_t id) {
    sqlite::Statement select(db, "SELECT comments.*, users.display_name FROM comments "
            "LEFT JOIN users ON comments.user = users.id WHERE comments.id = ?;");
    select.bind(1, id);
    select.step();
    comment = select.get_mapped<models::Comment>();
    if (comment.id == 0) {
        throw DoesNotExistException();
    }
    userName = select.get<std::string>(select.columns() - (size_t) 1);
}

void cli::CommentView::print(cli::TerminalPrinter &tp) {
    tp.normal("• " + comment.text);
    tp.bold(" " + make_date_string(comment.date));
    if (comment.score != 0) {
        tp.normal("|");
        tp.bold(std::to_string(comment.score));
        tp.normal("P");
    }
    if (userName != "") {
        tp.normal("|");
        tp.bold(userName);
    }
    tp.newline();

}
