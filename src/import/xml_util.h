//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_EXCEPTIONS_H
#define SEMESTRALKA_EXCEPTIONS_H

#include <exception>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "include/tinyxml2.h"

namespace xml {
    /// Wraps an unexpected error returned by TinyXML parser
    class Exception : public std::exception {
    public:
        Exception(tinyxml2::XMLError err) : err(err) {}

        virtual const char *what() const throw() override {
            return tinyxml2::XMLDocument::ErrorIDToName(err);
        }

    private:
        tinyxml2::XMLError err;
    };

    /// Thrown when an imported XML file has incorrect root element name
    class IncorrectFileException : public std::exception {
    public:
        virtual const char *what() const throw() override {
            return "parsing an incorrect file";
        }
    };

    class DateTimeParseException : public std::exception {
    public:
        virtual const char *what() const throw() override {
            return "couldn't parse datetime string";
        }
    };

    inline std::tm parse_time(const std::string &timeString) {
        std::tm val;
        std::istringstream iss(timeString);
        iss >> std::get_time(&val, "%Y-%m-%dT%H:%M:%S");
        if (iss.fail()) {
            throw DateTimeParseException();
        }
        return val;
    }
}

#endif //SEMESTRALKA_EXCEPTIONS_H
