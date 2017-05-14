//
// Created by Róbert Selvek on 14/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "DetailedPostView.h"

cli::DetailedPostView::DetailedPostView(sqlite::Client &db, int64_t id) : PostView(db, id) {
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

void cli::DetailedPostView::print(cli::TerminalPrinter &tp) {
    PostView::print(tp);
    if (post.title != "") {
        tp.newline();
        tp.underline(post.title);
    }
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
