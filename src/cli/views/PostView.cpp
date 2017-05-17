//
// Created by Róbert Selvek on 13/05/2017.
//

#ifndef SEMESTRALKA_POSTVIEW_CPP
#define SEMESTRALKA_POSTVIEW_CPP

#include <sqlite/SqliteStatement.h>

#include "PostView.h"

cli::PostView::PostView(sqlite::Client &db, int64_t id) {
    sqlite::Statement select(db, "SELECT posts_markdown.*, users.display_name FROM posts_markdown LEFT JOIN users ON"
            " posts_markdown.owner = users.id WHERE posts_markdown.id = ?;");
    select.bind(1, id);
    select.step();
    post = select.get_mapped<models::Post>();
    if (post.id == 0) {
        throw DoesNotExistException();
    }
    ownerName = select.get<std::string>(post.sql_map().size());
}

void cli::PostView::print(cli::TerminalPrinter &tp) {
    tp.italic(std::to_string(post.id));
    tp.normal("|");
    std::string typeChar;
    if (post.type == 1) {
        typeChar = 'Q';
    } else if (post.type == 2) {
        typeChar = 'A';
    } else if (post.type == 6) {
        typeChar = 'M';
    } else {
        typeChar = 'W';
    }
    tp.bold(typeChar);
    tp.normal(":");
    tp.normal(make_date_string(post.createdAt));
    tp.normal("|");
    tp.bold(std::to_string(post.score));
    tp.normal("P");
    if (post.views != 0) {
        tp.normal("|");
        tp.bold(std::to_string(post.views));
        tp.normal("V");
    }
    if (ownerName != "") {
        tp.normal("|");
        tp.bold(ownerName);
    }
}

#endif