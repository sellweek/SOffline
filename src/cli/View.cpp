//
// Created by Róbert Selvek on 17/05/2017.
//

#include "View.h"

namespace cli {
    std::string View::make_date_string(const std::tm &time) {
        std::stringstream date;
        date << 1900 + time.tm_year << "-" << 1 + time.tm_mon << "-" << time.tm_mday;
        return date.str();
    }


    int64_t View::execute_simple_int_statement(sqlite::Statement &st, int64_t bound) {
        st.bind(1, bound);
        st.step();
        return st.get<int64_t>(0);
    }
}