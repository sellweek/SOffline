//
// Created by Róbert Selvek on 15/05/2017.
//

#ifndef SEMESTRALKA_USERCOMMAND_H
#define SEMESTRALKA_USERCOMMAND_H

#include <cli/Command.h>

namespace cli {
    class UserCommand : public Command {
    public:
        std::vector<ParameterProps, std::allocator<ParameterProps>> supported_params() const override;
        std::string summary() const override;
        std::string description() const override;
        void run(std::unordered_map<std::string, std::string> args) override;
    };
}


#endif //SEMESTRALKA_USERCOMMAND_H
