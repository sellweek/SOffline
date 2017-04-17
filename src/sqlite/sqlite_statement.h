//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_STATEMENT_H
#define SEMESTRALKA_SQLITE_STATEMENT_H

#include <sqlite3.h>
#include <cstdint>
#include <iterator>

#include "sqlite_client.h"

namespace sqlite {

    /**
     * Represents an SQLite prepared statement. The lifecycle of a prepared statement starts with its construction.
     * If the textual representation of statement contained any placeholders (?), they are substituted for values
     * by bind methods. It is then executed by step() method. If it is supposed to return multiple rows, step() should
     * be called until it returns false. The statement is then finalized by the destructor.
     */
    class Statement {
    public:
        /**
         * Create a prepared statement.
         * @param client sqlite::Client connecting to the database this statements should be prepared in
         * @param statement Statement SQL
         */
        Statement(Client &client, std::string statement);

        /// Statements can not be copied.
        Statement(const Statement &) = delete;

        ~Statement();

        /**
         * Bind a value to a placeholder.
         * @param idx Index of the placeholder (1-based)
         * @param val Value to bind
         */
        void bind(size_t idx, int64_t val);
        /// @overload Statement::bind(size_t idx, int64_t val)
        void bind(size_t idx, double val);
        /// @overload Statement::bind(size_t idx, int64_t val)
        void bind(size_t idx, std::string val);
        /**
         * Bind NULL to a placeholder.
         * @param idx Index of the placeholder (1-based)
         */
        void bind_null(size_t idx);

        /**
         * Execute the statement and load values to get. The return value is false only *after* all the values have been
         * returned, so you can easily use this method in a while loop.
         * @return A boolean denoting whether there are any more values to get.
         */
        bool step();

        /**
         * Get number of columns returned by the statement. Should only be called after step() has been called at least once.
         * @return Number of columns returned, the maximum index which can be used in get() + 1.
         */
        int columns();

        /**
         * Get a column in the currently returned row. Only supports int64_t, std::string and double, compilation will
         * fail if you use any other value.
         * @tparam T Type of value that should be returned. Only supports int64_t, std::string and double.
         * @param col Index of the column which will be returned (0-based).
         * @return Value of the column.
         */
        template <typename T>
        T get(size_t col);


    private:
        sqlite3_stmt *stmt;
        Client &client;

        void check_error(int code) {
            if (code) {
                sqlite3_finalize(stmt);
                throw Exception(sqlite3_errmsg(client.get_db()));
            }
        }

        void check_get_preconditions(size_t col) {
            if (col >= columns()) {
                throw ColumnOutOfBoundsException();
            }
        }
    };

    template <>
    inline int64_t Statement::get<int64_t>(size_t col) {
        check_get_preconditions(col);
        return sqlite3_column_int64(stmt, col);
    }

    template <>
    inline double Statement::get<double>(size_t col) {
        check_get_preconditions(col);
        return sqlite3_column_double(stmt, col);
    }

    template<>
    inline std::string Statement::get<std::string>(size_t col) {
        check_get_preconditions(col);
        // res will not be freed by me, because sqlite3 manages
        // its storage duration automagically
        const unsigned char *res = sqlite3_column_text(stmt, col);
        if (res == nullptr) {
            return std::string("");
        }
        return std::string((const char *) res);
    }

}
#endif //SEMESTRALKA_SQLITE_STATEMENT_H
