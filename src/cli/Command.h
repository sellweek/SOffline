//
// Created by Róbert Selvek on 12/05/2017.
//

#ifndef SEMESTRALKA_COMMAND_H
#define SEMESTRALKA_COMMAND_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <sqlite/SqliteClient.h>

#include "ParameterProps.h"
#include "TerminalPrinter.h"

/// Implements the command-line user interface.
namespace cli {
    /// Default location in which commands will look for SQLite database file.
    const std::string DEFAULT_DB_LOCATION = "db.sqlite";

    /**
    * Class representing a command that can be invoked in the command line interface.
    */
    class Command {
    public:
        /**
        * Construct a command.
        */
        Command();

        /**
        * @return A map of command line arguments which can be used with this command.
        */
        virtual std::vector<ParameterProps> supported_params() const = 0;

        /**
        * @return A brief description of the command's purpose.
        */
        virtual std::string summary() const = 0;

        /**
        * @return A more detailed description of the purpose and operation of the command.
        */
        virtual std::string description() const = 0;

        /**
        * Execute the command.
        * @param args Command line arguments that were passed to this argument, already validated and possibly set to their default values.
        */
        virtual void run(std::unordered_map<std::string, std::string> args) = 0;

    protected:
        /**
        * A TerminalPrinter appropriate for the destination of std::cout.
        */
        std::unique_ptr<TerminalPrinter> printer;
        void log_sqlite_exception(sqlite::Exception e);
    };
}

#endif //SEMESTRALKA_COMMAND_H
