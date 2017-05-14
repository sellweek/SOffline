//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_SEARCHCOMMAND_H
#define SEMESTRALKA_SEARCHCOMMAND_H

#include <cli/Command.h>

namespace cli {
    class SearchCommand : public Command {
    public:
        virtual std::vector<ParameterProps> supported_params() const override;
        virtual std::string summary() const override;
        virtual std::string description() const override;
        virtual void run(std::unordered_map<std::string, std::string> args) override;
    };
}

#endif //SEMESTRALKA_SEARCHCOMMAND_H
