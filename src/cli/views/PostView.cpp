//
// Created by Róbert Selvek on 13/05/2017.
//

#include "PostView.h"
#include "helpers.h"

cli::PostView::PostView(models::Post post, std::string owner): post(post), ownerName(owner) {}

void cli::PostView::print(bool abbreviated, cli::TerminalPrinter &tp) {
    if (abbreviated) {
        tp.italic(std::to_string(post.id) + "\t");
    }
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
    abbreviated ? tp.normal("\t") : tp.newline();
    tp.underline(post.title);
    if (!abbreviated) {
        tp.newline();
        tp.normal(post.body);
    }
    tp.newline();
}
