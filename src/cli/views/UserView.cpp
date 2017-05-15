//
// Created by Róbert Selvek on 15/05/2017.
//

#include <sqlite/SqliteStatement.h>
#include "UserView.h"
#include "helpers.h"

cli::UserView::UserView(sqlite::Client &db, int64_t id) {
    sqlite::Statement select(db, "SELECT * FROM users WHERE id = ?");
    select.bind(1, id);
    if (!select.step()) {
        throw DoesNotExistException();
    }
    user = select.get_mapped<models::User>();
}

void cli::UserView::print_reputation(cli::TerminalPrinter &tp) {
    tp.bold(std::to_string(user.reputation));
    tp.normal("(");
    tp.color(Color::Green, std::to_string(user.upvotes));
    tp.normal("↑ ");
    tp.color(Color::Red, std::to_string(user.downvotes));
    tp.normal("↓)");
}
