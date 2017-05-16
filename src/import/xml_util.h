//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_EXCEPTIONS_H
#define SEMESTRALKA_EXCEPTIONS_H

#include <exception>
#include <string>
#include <ctime>
#include <sstream>
#include <time.h>

#include <include/tinyxml2.h>

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

    /// Thrown when a timestamp in an XML file can't be parsed.
    class DateTimeParseException : public std::exception {
    public:
        virtual const char *what() const throw() override {
            return "couldn't parse datetime string";
        }
    };

    /**
    * Parse time fromatted as in Stack Exchange data dumps.
    * @param timeString a timestamp in YYYY-M-DTH:M:S format
    * @return std::tm filled with information coming from the string
    */
    inline std::tm parse_time(const std::string &timeString) {
        std::tm val;
        // Another place where we can't use C++ functions because G++ developers
        // lied about feature-completeness of G++ 4.8
        if (strptime(timeString.c_str(), "%Y-%m-%dT%H:%M:%S", &val) == nullptr) {
            throw DateTimeParseException();
        }

        return val;
    }
}

#endif //SEMESTRALKA_EXCEPTIONS_H
