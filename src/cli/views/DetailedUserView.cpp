//
// Created by Róbert Selvek on 15/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "DetailedUserView.h"
#include "helpers.h"

cli::DetailedUserView::DetailedUserView(sqlite::Client &db, int64_t id) : UserView(db, id) {
    sqlite::Statement asked(db, "SELECT id FROM posts WHERE owner = ? AND post_type=1");
    asked.bind(1, id);
    while (asked.step()) {
        asked_questions.push_back(SummaryPostView(db, asked.get<int64_t>(0)));
    }
    sqlite::Statement answered(db, "SELECT parent FROM posts WHERE owner = ? AND post_type=2");
    answered.bind(1, id);
    while (answered.step()) {
        answered_questions.push_back(SummaryPostView(db, answered.get<int64_t>(0)));
    }
}

void cli::DetailedUserView::print(cli::TerminalPrinter &tp) {
    tp.reverse(user.displayName);
    tp.normal(" ("+std::to_string(user.id) + ")");
    tp.newline();
    tp.normal("A user since ");
    tp.bold(make_date_string(user.createdAt));
    tp.normal(", reputation: ");
    print_reputation(tp);
    tp.newline();
    if (user.location != "") {
        tp.bold(user.location);
    }
    if (user.website != "") {
        tp.normal("|");
        tp.bold(user.website);
    }
    if (user.location != "" || user.website != "") {
        tp.newline();
    }
    if (user.about != "") {
        tp.bold("About me: ");
        tp.normal(user.about);
    }
    tp.newline();
    tp.normal("The last time we've seen this user was on ");
    tp.bold(make_date_string(user.lastAccess));
    tp.normal(" his or her Stack Exchange account has ID: ");
    tp.bold(std::to_string(user.accountID));
    tp.newline();
    if (asked_questions.size() != 0) {
        tp.reverse("QUESTIONS THIS USER HAS ASKED");
        tp.newline();
        for (auto &q : asked_questions) {
            q.print(tp);
            tp.newline();
        }
    }
    if (answered_questions.size() != 0) {
        tp.reverse("QUESTIONS THIS USER HAS ANSWERED");
        tp.newline();
        for (auto &q : answered_questions) {
            q.print(tp);
            tp.newline();
        }
    }
}
