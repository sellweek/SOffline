//
// Created by Róbert Selvek on 13/05/2017.
//

#ifndef SEMESTRALKA_POSTVIEW_CPP
#define SEMESTRALKA_POSTVIEW_CPP

#include <sqlite/sqlite_statement.h>

#include "PostView.h"
#include "helpers.h"

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
    std::vector<int64_t> commentIds;
    sqlite::Statement commentStmt(db, "SELECT id FROM comments WHERE post = ?");
    commentStmt.bind(1, id);
    while (commentStmt.step()) {
        commentIds.push_back(commentStmt.get<int64_t>(0));
    }
    for (auto commentId : commentIds) {
        comments.push_back(CommentView(db, commentId));
    }
    sqlite::Statement tagStmt(db, "SELECT tags.name FROM post_tags JOIN tags ON post_tags.tag = tags.id WHERE post_tags.post = ?");
    tagStmt.bind(1, id);
    while (tagStmt.step()) {
        tags.push_back(tagStmt.get<std::string>(0));
    }
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
    tp.newline();
    tp.underline(post.title);
    tp.newline();
    tp.normal(post.body);
    tp.newline();
    if (tags.size() > 0) {
        for (const auto &tag : tags) {
            tp.italic(tag + " ");
        }
        tp.newline();
    }
    if (comments.size() > 0) {
        tp.underline("Comments:");
        tp.newline();
        for (auto &cv : comments) {
            cv.print(tp);
        }
        tp.newline();
    }

}

#endif