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
    /**
    * Exception thrown when command line parsing fails:
    * An unkown parameter is encountered, parameter value is missing
    * there is a syntax error and so on.
    */
    class CommandParseException : public std::exception {
    public:
        CommandParseException() {}

        virtual const char *what() const throw() override {
            return "Invalid command-line parameters.";
        }
    };

    /**
    * This class implements basic command-line interface of the program. It parses argv,
    * and according to ParameterProps, creates a map of them that's passed to the requested
    * command's run method or shows an error message if command's requirements are not 
    * fulfilled or argument syntax is incorrect.
    * 
    * The supported syntax is inspired by Plan 9:    
    *   `program command -param1 "param1 value" -boolParam -param2 blergh`
    * 
    * \remark The flag parsing is extremely rudimentary. It will fail when a flag's value begins
    * with - or when an empty string is supplied as the value.
    */
    class Commander {
    public:
        /**
        * Construct a Commander.
        * @param programName Name of the running program that can be used in help messages.
        * @param description A brief description of the purpose of the program.
        */
        Commander(std::string programName, std::string description);
        /*
        * Add a command that can possibly be run.
        * @param cmdName Name which can be used to invoke the command.
        * @param cmd Pointer to an instance of Command, containing all the metadata and a run method.
        */
        void add_command(std::string cmdName, std::unique_ptr<Command> cmd);
        /*
        * Evaluate the command line arguments and run an appropriate command, if possible.
        * @param argc Number of command line arguments.
        * @param argv Command line arguments, beginning with executable name.
        */
        void run(int argc, char **argv);
    private:
        /**
        * Print program's help message.
        */
        void help();

        /**
        * Print detailed information about a command.
        * @param command Command to show help about.
        */
        void help(std::string command);

        /**
        * Process all command line parameters into a map of their names and values.
        * Invocation of `./program command -param1 "param1 value" -boolParam -param2 blergh`
        * will be transformed into a map in the form of:
        * ```
        * "param1": "value"
        * "boolParam": ""
        * "param2": "blergh"
        * ```
        */
        std::unordered_map<std::string, std::string> collect_parameters(int argc, char **argv);

        /**
        * Compares collected parameters with command's requested parameters.
        * @throws CommandParseException If command's requirements are not fulfilled.
        */
        std::unordered_map<std::string, std::string> resolve_parameters(
                const std::unordered_map<std::string, std::string> &received,
                const std::vector<ParameterProps> &requested);
        
        std::unordered_map<std::string, std::unique_ptr<Command>> commands;
        std::string name;
        std::string description;
    };
}


#endif //SEMESTRALKA_COMMANDER_H
