//
// Created by Róbert Selvek on 13/05/2017.
//

#ifndef SEMESTRALKA_IMPORTCOMMAND_H
#define SEMESTRALKA_IMPORTCOMMAND_H

#include "cli/Command.h"
#include "cli/ParameterProps.h"

namespace cli {
    class ImportCommand : public Command {
        virtual std::vector<ParameterProps> supported_params() const override;
        virtual std::string summary() const override;
        virtual std::string description() const override;
        virtual void run(std::unordered_map<std::string, std::string> args) override;
    };
}


#endif //SEMESTRALKA_IMPORTCOMMAND_H
