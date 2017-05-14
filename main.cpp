#include <iostream>
#include <fstream>
#include <cli/Commander.h>
#include <cli/ANSIPrinter.h>
#include <cli/commands/ImportCommand.h>
#include <cli/commands/ShowPostCommand.h>
#include <cli/commands/ThreadCommand.h>

int main(int argc, char **argv) {
    cli::Commander cmdr("SOffline", "Imports Stack Overflow data dumps");
    cmdr.add_command("import", std::unique_ptr<cli::Command>(new cli::ImportCommand()));
    cmdr.add_command("thread", std::unique_ptr<cli::Command>(new cli::ThreadCommand()));
    cmdr.add_command("post", std::unique_ptr<cli::Command>(new cli::ShowPostCommand()));
    cmdr.run(argc, argv);
    return 0;
}