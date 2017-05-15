//
// Created by Róbert Selvek on 15/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "SummaryUserView.h"
#include "helpers.h"

cli::SummaryUserView::SummaryUserView(sqlite::Client &db, int64_t id) : UserView(db, id) {
    questionCount = 0;
    answerCount = 0;
    sqlite::Statement countsStmt(db, "SELECT post_type, COUNT(*) FROM posts WHERE owner = ? GROUP BY post_type");
    countsStmt.bind(1, id);
    while (countsStmt.step()) {
        int64_t type = countsStmt.get<int64_t>(0);
        int64_t count = countsStmt.get<int64_t>(1);
        if (type == 1) {
            questionCount = count;
        } else if (type == 2) {
            answerCount = count;
        }
    }
    sqlite::Statement acceptedStmt(db, "SELECT COUNT(*) FROM posts WHERE accepted_answer IN (SELECT id FROM posts WHERE owner = ? AND post_type = 2)");
    acceptedCount = execute_simple_int_statement(acceptedStmt, id);
}

void cli::SummaryUserView::print(cli::TerminalPrinter &tp) {
    tp.italic(std::to_string(user.id));
    tp.normal("|");
    tp.bold(user.displayName);
    tp.normal("|");
    print_reputation(tp);
    tp.normal("|");
    tp.bold(std::to_string(questionCount));
    tp.normal("Q|");
    tp.bold(std::to_string(answerCount));
    tp.normal("A|");
    tp.bold(std::to_string(acceptedCount));
    tp.normal("ACC");
}
