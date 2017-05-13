//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_CLIENT_H
#define SEMESTRALKA_SQLITE_CLIENT_H

#include <sqlite3.h>
#include <string>

/**
 * Contains classes used to interface with an SQLite database.
 * These classes together implement a simple C++ wrapper over
 * the basic C interface sqlite3 library provides which hopefully makes database
 * programming in C++ a little bit nicer.
 */
namespace sqlite {
    /// Wraps an error returned by SQlite
    class Exception : public std::exception {
    public:
        Exception(const char *errmsg) : msg(std::string("SQLite error: ") + std::string(errmsg)) {}

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    private:
        std::string msg;
    };

    /**
     * Thrown when an index supplied to SQLite is out of bounds. It is
     * thrown by Statement::bind and Statement::get methods
     * if the indexes supplied to them are out of bounds.
     */
    class ColumnOutOfBoundsException : public Exception {
    public:
        ColumnOutOfBoundsException(): Exception("Column index out of bounds") {}
    };

    /**
     * Represents a connection to an SQLite database.
     * It automatically manages the connection using C++ constructors and destructors.
     */
    class Client {
    public:
        /**
         * Open the database at the given path in the local filesystem.
         * @param path Path of the sqlite database file.
        */
        Client(const std::string &path);

        /// Client objects can not be copied.
        Client(const Client &) = delete;

        /// Close the database connection.
        ~Client();

        /**
         * Get raw sqlite3 object which can be used in sqlite3's functions.
         * Be careful, this is a pointer to the internal object used by the Client
         * instance and after the instance is destroyed, it will not be valid anymore.
         * @return A pointer to sqlite3 object (for more information about its use, see sqlite3 C/C++ interface docs).
         */
        sqlite3 *get_db() { return db; }

        /**
         * Execute given SQL script, supporting multiple statements.
         * @param sql SQL script to be executed.
         */
        void exec(const std::string &sql);

        int max_variables();

    private:
        sqlite3 *db;
    };
}
#endif //SEMESTRALKA_SQLITE_CLIENT_H
