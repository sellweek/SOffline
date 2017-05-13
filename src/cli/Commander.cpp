//
// Created by Róbert Selvek on 12/05/2017.
//

#include "Commander.h"
#include "ParameterProps.h"

#include <iostream>

cli::Commander::Commander(std::string programName,
                          std::string description): commands(), name(programName), description(description) {}

void cli::Commander::add_command(std::string cmdName, std::unique_ptr<cli::Command> cmd) {
    commands[cmdName] = std::move(cmd);
}

void cli::Commander::run(int argc, char **argv) {
    if (argc < 2) {
        help();
        return;
    }
    std::string commandName(argv[1]);
    if (commandName == "help") {
        if (argc == 2) {
            help();
        } else {
            help(std::string(argv[2]));
        }
        return;
    }
    auto commandIt = commands.find(commandName);
    if (commandIt == commands.end()) {
        std::cout << "Unknown command. Use `" << name << " help` to get help" << std::endl;
        return;
    }
    const std::unique_ptr<Command> &command = commandIt->second;
    std::unordered_map<std::string, std::string> collected;
    try {
        collected = collect_parameters(argc, argv);
    } catch (CommandParseException e) {
        std::cout << "Invalid parameter format supplied. Use Plan 9 format (e. g. -param1 value -boolparam -param2 value)"
                  << std::endl;
        return;
    }
    std::unordered_map<std::string, std::string> resolved;
    try {
        resolved = resolve_parameters(collected, command->supported_params());
    } catch (CommandParseException e) {
        std::cout << "Invalid parameters supplied. Please refer to command's documentation (help "
                  << commandIt->first << ")" << std::endl;
        return;
    }

    command->run(resolved);
}

void cli::Commander::help() {
    std::cout << description << std::endl
              << "This program supports following commands:" << std::endl;
    for (auto &c : commands) {
        std::cout << c.first << ": " << c.second->summary() << std::endl;
    }
}

void cli::Commander::help(std::string commandName) {
    auto commandIt = commands.find(commandName);
    if (commandIt == commands.end()) {
        std::cout << "Unknown command." << std::endl;
        help();
        return;
    }
    const auto &command = commandIt->second;
    std::cout << "Command " << commandName << std::endl
              << command->description() << std::endl
              << "Accepted parameters:" << std::endl;
    for (const auto &param : command->supported_params()) {
        std::cout << "\t-" << param.name;
        if (!param.optional) {
            std::cout << " (required)";
        }
        std::cout << " - " << param.description;
        if (param.hasDefault) {
            std::cout << " (default value: \"" << param.defaultValue << "\")";
        }
        std::cout << std::endl;
    }
}

// Fails if a parameter is supplied with a value beginning with -
std::unordered_map<std::string, std::string> cli::Commander::collect_parameters(int argc, char **argv) {
    std::unordered_map<std::string, std::string> params;
    size_t i = 2;
    while (i < argc) {
        std::string name(argv[i]);
        if (name.size() == 0 || name[0] != '-') {
            throw CommandParseException();
        }
        name.erase(0, 1);
        if (i != argc - 1) {
            std::string next(argv[i+1]);
            if (next[0] != '-') {
                params[name] = next;
                i += 2;
                continue;
            }
        }
        params[name] = "";
        i += 1;
    }
    return params;
}

std::unordered_map<std::string, std::string> cli::Commander::resolve_parameters(
        const std::unordered_map<std::string, std::string> &received,
        const std::vector<ParameterProps> &requested) {
    std::unordered_map<std::string, ParameterProps> parameter_details;
    for (auto &props : requested) {
        parameter_details[props.name] = props;
    }
    std::unordered_map<std::string, std::string> processed;
    for (const auto &param : received) {
        auto propsIt = parameter_details.find(param.first);
        if (propsIt == parameter_details.end()) {
            throw CommandParseException();
        }
        const auto &props = propsIt->second;
        if (props.hasParameter) {
            if (param.second != "") {
                processed[param.first] = param.second;
            } else {
                throw CommandParseException();
            }
        } else {
            processed[param.first] = "";
        }
    }
    for (const auto &cmdParam : parameter_details) {
        auto paramIt = processed.find(cmdParam.first);
        if (paramIt == processed.end()) {
            if (!cmdParam.second.optional && !cmdParam.second.hasDefault) {
                throw CommandParseException();
            }
            if (!cmdParam.second.optional) {
                processed[cmdParam.first] = cmdParam.second.defaultValue;
            }
        }
    }
    return processed;
};