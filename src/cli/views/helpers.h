//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_HELPERS_H
#define SEMESTRALKA_HELPERS_H

#include <ctime>
#include <string>
#include <sstream>
#include "PostView.h"
#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>

namespace cli {
    class DoesNotExistException: std::exception {
    public:
        virtual const char *what() const throw() override {
            return "Entity not found";
        }
    };
    /**
     * Format given time into a YYYY-M-D string.
     * @param time Time structure to convert.
     * @return Formatted string.
     */
    std::string make_date_string(const std::tm &time);

    /**
     * Execute an sqlite::Statement having one integer placeholder and returning a single
     * row with a single integer column.
     * @param st Statement to execute
     * @param bound Value to bind to the first placeholder.
     * @return The result of the statement.
     * @throws sqlite::Exception when an error occurs while communicating with the database.
     */
    int64_t execute_simple_int_statement(sqlite::Statement &st, int64_t bound);
}

#endif //SEMESTRALKA_HELPERS_H
