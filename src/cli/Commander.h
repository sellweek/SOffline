//
// Created by Róbert Selvek on 12/05/2017.
//

#ifndef SEMESTRALKA_COMMANDER_H
#define SEMESTRALKA_COMMANDER_H

#include <string>
#include <memory>
#include <vector>
#include "ParameterProps.h"
#include "Command.h"

namespace cli {
    class CommandParseException : public std::exception {
    public:
        CommandParseException() {}

        virtual const char *what() const throw() override {
            return "Invalid command-line parameters.";
        }
    };

    class Commander {
        // WARNING!
        // Commander's command line flag parsing is extremely rudimentary.
        // It will fail when a flag's value begins with - or when an empty string
        // is supplied as the value.
    public:
        Commander(std::string programName, std::string description);
        void add_command(std::string cmdName, std::unique_ptr<Command> cmd);
        void run(int argc, char **argv);
    private:
        void help();
        void help(std::string command);
        std::unordered_map<std::string, std::string> collect_parameters(int argc, char **argv);
        std::unordered_map<std::string, std::string> resolve_parameters(
                const std::unordered_map<std::string, std::string> &received,
                const std::vector<ParameterProps> &requested);
        std::unordered_map<std::string, std::unique_ptr<Command>> commands;
        std::string name;
        std::string description;
    };
}


#endif //SEMESTRALKA_COMMANDER_H
