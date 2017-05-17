//
// Created by Róbert Selvek on 17/05/2017.
//

#ifndef SEMESTRALKA_VIEW_H
#define SEMESTRALKA_VIEW_H

#include <ctime>
#include <string>

#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/TerminalPrinter.h>

namespace cli {
    /**
    * Exception thrown when a model is given an ID which doesn't exist
    * in its associated table.
    */
    class DoesNotExistException: std::exception {
    public:
        virtual const char *what() const throw() override {
            return "Entity not found";
        }
    };
    

    /**
    * A class responsible for printing of models into the terminal. 
    * Generally, views have constructors which accept a sqlite::Client
    * and the database ID of the model user wants to print. They load the
    * model and all the necessary related data from the database and store
    * them inside their object. 
    */
    class View {
    public:
        /**
        * Format and print data loaded from the database on construction.
        * @param tp Printer used to print the data.
        */
        virtual void print(TerminalPrinter &tp) = 0;

    protected:
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
    };
}

#endif