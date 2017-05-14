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
    class DoesNotExistException: std::exception {
    public:
        virtual const char *what() const throw() override {
            return "Entity not found";
        }
    };
    std::string make_date_string(const std::tm &time);
}

#endif //SEMESTRALKA_HELPERS_H
