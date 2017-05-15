//
// Created by Róbert Selvek on 14/05/2017.
//

#include "helpers.h"
#include <sqlite/SqliteStatement.h>

namespace cli {
    std::string make_date_string(const std::tm &time) {
        std::stringstream date;
        date << 1900 + time.tm_year << "-" << 1 + time.tm_mon << "-" << time.tm_mday;
        return date.str();
    }


    int64_t execute_simple_int_statement(sqlite::Statement &st, int64_t bound) {
        st.bind(1, bound);
        st.step();
        return st.get<int64_t>(0);
    }
}