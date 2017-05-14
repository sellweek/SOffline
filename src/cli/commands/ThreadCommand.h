//
// Created by Róbert Selvek on 14/05/2017.
//

#ifndef SEMESTRALKA_THREADCOMMAND_H
#define SEMESTRALKA_THREADCOMMAND_H

#include <sqlite/SqliteClient.h>
#include <sqlite/SqliteStatement.h>
#include <cli/Command.h>

namespace cli {
    class ThreadCommand : public Command {
    public:
        virtual std::vector<ParameterProps> supported_params() const override;
        virtual std::string summary() const override;
        virtual std::string description() const override;
        virtual void run(std::unordered_map<std::string, std::string> args) override;
    private:
        int64_t get_post_parent(sqlite::Client &db, int64_t postId);
        std::vector<int64_t> get_answers(sqlite::Client &db, int64_t postId);
    };
}

#endif //SEMESTRALKA_THREADCOMMAND_H
