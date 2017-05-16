#include <iostream>
#include <fstream>
#include <cli/Commander.h>
#include <cli/ANSIPrinter.h>
#include <cli/commands/ImportCommand.h>
#include <cli/commands/ShowPostCommand.h>
#include <cli/commands/ThreadCommand.h>
#include <cli/commands/RecentCommand.h>
#include <cli/commands/SearchCommand.h>
#include <cli/commands/UserCommand.h>
#include <cli/commands/UsersCommand.h>
#include <cli/commands/TagsCommand.h>

int main(int argc, char **argv) {
    cli::Commander cmdr("SOffline", "Imports Stack Overflow data dumps");
    cmdr.add_command("import", std::unique_ptr<cli::Command>(new cli::ImportCommand()));
    cmdr.add_command("thread", std::unique_ptr<cli::Command>(new cli::ThreadCommand()));
    cmdr.add_command("post", std::unique_ptr<cli::Command>(new cli::ShowPostCommand()));
    cmdr.add_command("recent", std::unique_ptr<cli::Command>(new cli::RecentCommand()));
    cmdr.add_command("search", std::unique_ptr<cli::Command>(new cli::SearchCommand()));
    cmdr.add_command("user", std::unique_ptr<cli::Command>(new cli::UserCommand()));
    cmdr.add_command("users", std::unique_ptr<cli::Command>(new cli::UsersCommand()));
    cmdr.add_command("tags", std::unique_ptr<cli::Command>(new cli::TagsCommand()));
    cmdr.run(argc, argv);
    return 0;
}