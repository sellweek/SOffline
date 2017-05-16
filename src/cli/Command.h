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

namespace cli {
    const std::string DEFAULT_DB_LOCATION = "db.sqlite";
    class Command {
    public:
        virtual std::vector<ParameterProps> supported_params() const = 0;
        virtual std::string summary() const = 0;
        virtual std::string description() const = 0;
        virtual void run(std::unordered_map<std::string, std::string> args) = 0;

    protected:
        std::unique_ptr<TerminalPrinter> getPrinter();
    };
}

#endif //SEMESTRALKA_COMMAND_H
