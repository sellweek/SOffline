//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_STATEMENT_H
#define SEMESTRALKA_SQLITE_STATEMENT_H

#include <sqlite3.h>
#include <cstdint>
#include <iterator>
#include <string>
#include <memory>
#include <sstream>

#include "SqliteClient.h"
#include "models.h"

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
        Statement(Client &client, std::string statement) : client(client) {
            create_sqlite3_stmt(statement);
        }

        /**
         * Generate an insert statement for given models. You must take care to only pass in
         * models belonging to the same table (that means, with the same sql_map).
         * @param tableName Name of the table into which the models will be inserted.
         * @param inserted A vector of models to insert.
         * @return A bound statement which only has to be stepped to insert the given models.
         */
        Statement(Client &client, std::string tableName, const std::vector<std::shared_ptr<models::Model>> &inserted): client(client) {
            std::ostringstream ss;
            if (inserted.size() == 0) {
                throw std::length_error("no models to insert");
            }
            ss << "INSERT INTO `" << tableName << "` ";
            const auto &map = inserted[0]->sql_map();
            std::vector<std::string> columns;
            columns.reserve(map.size());
            for (const auto &md : map) {
                columns.push_back(md.columnName);
            }
            ss << sql_list(columns) << " VALUES ";
            auto placeholders = sql_list(std::vector<std::string>(columns.size(), "?"));
            for (int i = 0; i < inserted.size(); i++) {
                ss << placeholders;
                if (i != inserted.size() - 1) {
                    ss << ',';
                }
            }
            create_sqlite3_stmt(ss.str());
            for (int i = 0; i < inserted.size(); i++) {
                bind_mapped(i*map.size()+1, *inserted[i]);
            }
        }

        /// Statements can not be copied.
        Statement(const Statement &) = delete;

        ~Statement() {
            sqlite3_finalize(stmt);
        }

        /**
         * Bind a value to a placeholder.
         * @param idx Index of the placeholder (1-based)
         * @param val Value to bind
         */
        void bind(size_t idx, int64_t val) {
            check_error(sqlite3_bind_int64(stmt, idx, val));
        }
        /// @overload Statement::bind(size_t idx, int64_t val)
        void bind(size_t idx, double val) {
            check_error(sqlite3_bind_double(stmt, idx, val));
        }
        /// @overload Statement::bind(size_t idx, int64_t val)
        void bind(size_t idx, std::string val) {
            size_t len = val.size();
            char *copy = new char[len];
            strncpy(copy, val.c_str(), len);
            check_error(sqlite3_bind_text(stmt, idx, copy, len, &free_c_str));
        }

        /**
         * Bind NULL to a placeholder.
         * @param idx Index of the placeholder (1-based)
         */
        void bind_null(size_t idx) {
            check_error(sqlite3_bind_null(stmt, idx));
        }

        void bind_mapped(int startIdx, const models::Model &m) {
            auto map = m.sql_map();
            for (int i = startIdx; i < startIdx + map.size(); i++) {
                switch (map[i - startIdx].columnType) {
                    case models::ExternalType::Int64:
                        bind(i, *((int64_t*) map.at(i - startIdx).valuePointer));
                        break;
                    case models::ExternalType::String:
                        bind(i, *((std::string*) map.at(i - startIdx).valuePointer));
                        break;
                    case models::ExternalType::Bool:
                        bind(i, (int64_t) *((bool*) map.at(i - startIdx).valuePointer));
                        break;
                    case models::ExternalType::Datetime:
                        auto tm = (std::tm*) map.at(i - startIdx).valuePointer;
                        bind(i, (int64_t) std::mktime(tm));
                        break;
                }
            }
        }

        /**
         * Execute the statement and load values to get. The return value is false only *after* all the values have been
         * returned, so you can easily use this method in a while loop.
         * @return A boolean denoting whether there are any more values to get.
         */
        bool step() {
            int result = sqlite3_step(stmt);
            if (result == SQLITE_ROW) {
                return true;
            } else if (result == SQLITE_DONE) {
                return false;
            }
            check_error(result);
            return false;
        }

        /**
         * Get number of columns returned by the statement. Should only be called after step() has been called at least once.
         * @return Number of columns returned, the maximum index which can be used in get() + 1.
         */
        int columns() const noexcept {
            return sqlite3_column_count(stmt);
        }

        /**
         * Get a column in the currently returned row. Only supports int64_t, std::string and double, compilation will
         * fail if you use any other value.
         * @tparam T Type of value that should be returned. Only supports int64_t, std::string and double.
         * @param col Index of the column which will be returned (0-based).
         * @return Value of the column.
         */
        template <typename T>
        T get(size_t col) const;

        /**
         * Construct a new object of type T and use its sql_map method to map column values loaded from the database
         * into object's members.
         * @tparam T Type to construct, must have sql_map() method.
         * @return A newly constructed object of type T.
         */
        template <typename T>
        T get_mapped() {
            T val {};
            std::vector<models::SQLMetadata> sql_mapping = val.sql_map();
            for (int i = 0; i < sql_mapping.size(); i++) {
                auto md = sql_mapping[i];
                if (md.columnType == models::ExternalType::Int64) {
                    *((std::int64_t *) md.valuePointer) = get<int64_t>(i);
                } else if (md.columnType == models::ExternalType::String) {
                    *((std::string *) md.valuePointer) = get<std::string>(i);
                } else if (md.columnType == models::ExternalType::Datetime) {
                    int64_t timeValue = get<int64_t>(i);
                    auto tm = localtime((time_t *) &timeValue);
                    *((std::tm *) md.valuePointer) = *tm;
                } else if (md.columnType == models::ExternalType::Bool) {
                    *((bool *) md.valuePointer) = get<int64_t>(i) != 0;
                }
            }
            return val;
        }

    private:
        sqlite3_stmt *stmt;
        Client &client;

        void check_error(int code) {
            if (code) {
                sqlite3_finalize(stmt);
                throw Exception(sqlite3_errmsg(client.get_db()));
            }
        }

        void check_get_preconditions(size_t col) const {
            if (col >= columns()) {
                throw ColumnOutOfBoundsException();
            }
        }

        void create_sqlite3_stmt(std::string statement) {
            int error = sqlite3_prepare_v2(client.get_db(), statement.c_str(), (int) statement.size(), &stmt, nullptr);
            if (error) {
                sqlite3_finalize(stmt);
                check_error(error);
            }
        }

        /**
         * Generate parenthesised string of comma separated strings from values
         */
        static std::string sql_list(std::vector<std::string> values) noexcept {
            // Why, tell me why, can't language designers just accept a trailing comma?
            std::ostringstream ss;
            ss << '(';
            for (int i = 0; i < values.size(); i++) {
                ss << values[i];
                if (i != values.size() - 1) {
                    ss << ',';
                }
            }
            ss << ')';
            return ss.str();
        }
        static void free_c_str(void *str) {
            delete [] (char *) str;
        }
    };

    template <>
    inline int64_t Statement::get<int64_t>(size_t col) const {
        check_get_preconditions(col);
        return sqlite3_column_int64(stmt, col);
    }

    template <>
    inline double Statement::get<double>(size_t col) const {
        check_get_preconditions(col);
        return sqlite3_column_double(stmt, col);
    }

    template<>
    inline std::string Statement::get<std::string>(size_t col) const {
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
