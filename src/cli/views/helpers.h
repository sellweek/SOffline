//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_HELPERS_H
#define SEMESTRALKA_HELPERS_H

#include <ctime>
#include <string>
#include <sstream>
#include "PostView.h"
#include <sqlite/sqlite_client.h>

namespace cli {
    std::string make_date_string(const std::tm &time);
    PostView get_post_for_id(sqlite::Client &db, int64_t id);
}

#endif //SEMESTRALKA_HELPERS_H
