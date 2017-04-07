//
// Created by Róbert Selvek on 07/04/2017.
//

#ifndef SEMESTRALKA_SQLITE_CLIENT_H
#define SEMESTRALKA_SQLITE_CLIENT_H

#include <sqlite3.h>
#include <string>

namespace sqlite {
    class Exception : public std::exception {
    public:
        Exception(const char *errmsg) : msg(std::string("SQLite error: ") + std::string(errmsg)) {}

        virtual const char *what() const throw() {
            return msg.c_str();
        }

    private:
        std::string msg;
    };

    class Client {
    public:
        Client(const std::string &path);

        Client(const Client &) = delete;

        ~Client();

        sqlite3 *get_db() { return db; }

    private:
        sqlite3 *db;
    };
}
#endif //SEMESTRALKA_SQLITE_CLIENT_H
