//
// Created by Róbert Selvek on 16/05/2017.
//

#ifndef SEMESTRALKA_TAGCOMMAND_H
#define SEMESTRALKA_TAGCOMMAND_H

#include <cli/Command.h>

namespace cli {
    class TagCommand : public Command {
    public:
        std::vector<ParameterProps, std::allocator<ParameterProps>> supported_params() const override;

        std::string summary() const override;

        std::string description() const override;

        void run(std::unordered_map<std::string, std::string> args) override;
    };
}



#endif //SEMESTRALKA_TAGCOMMAND_H
