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

}