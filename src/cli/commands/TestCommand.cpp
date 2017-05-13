//
// Created by Róbert Selvek on 13/05/2017.
//

#include <iostream>

#include "TestCommand.h"

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::TestCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"param1", "A first parameter", false, true, false, ""},
            {"param2", "A second parameter", false, true, true, "default"},
            {"boolparam", "A bool parameter", true, false, false, ""},
            {"optionalparam", "An optional parameter", true, true, false, ""},
    };
    return parameters;
}

std::string cli::TestCommand::summary() const {
    return "A simple command";
}

std::string cli::TestCommand::description() const {
    return "This is a very simple command which tests Commander's implementation and operation";
}

void cli::TestCommand::run(std::unordered_map<std::string, std::string> args) {
    for (const auto &param : args) {
        std::cout << param.first << " = " << param.second << std::endl;
    }
}
