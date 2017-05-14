//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_SHOWPOSTCOMMAND_H
#define SEMESTRALKA_SHOWPOSTCOMMAND_H

#include <cli/Command.h>

namespace cli {
    class ShowPostCommand : public Command {
        virtual std::vector<ParameterProps> supported_params() const override;
        virtual std::string summary() const override;
        virtual std::string description() const override;
        virtual void run(std::unordered_map<std::string, std::string> args) override;
    };
}


#endif //SEMESTRALKA_SHOWPOSTCOMMAND_H
