//
// Created by Róbert Selvek on 14/05/2017.
//

#include "helpers.h"
#include <sqlite/sqlite_statement.h>

namespace cli {
    std::string make_date_string(const std::tm &time) {
        std::stringstream date;
        date << 1900 + time.tm_year << "-" << 1 + time.tm_mon << "-" << time.tm_mday;
        return date.str();
    }

    PostView get_post_for_id(sqlite::Client &db, int64_t id) {
        sqlite::Statement select(db, "SELECT posts_markdown.*, users.display_name FROM posts_markdown LEFT JOIN users ON"
                " posts_markdown.owner = users.id WHERE posts_markdown.id = ?;");
        select.bind(1, id);
        select.step();
        models::Post post = select.get_mapped<models::Post>();
        PostView v(post, select.get<std::string>(post.sql_map().size()));
        return v;
    }
}