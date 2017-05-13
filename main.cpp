#include <iostream>
#include <cstdint>
#include <chrono>
#include <string>
#include <fstream>
#include "cli/Commander.h"
#include "cli/commands/TestCommand.h"
#include "cli/commands/ImportCommand.h"

int main(int argc, char **argv) {
    /*
    auto results = xml::import_all("/Users/selvek/Downloads/worldbuilding.stackexchange.com");
    std::cout << "Done, got " << results.users.size() << " users." << std::endl;
    std::cout << "Starting" << std::endl;

    import::Importer imp("/Users/selvek/Downloads/worldbuilding.stackexchange.com", "/Users/selvek/Dev/fit/PA2/semestralka/db.sqlite");
    imp.import_all();
     */
    cli::Commander cmdr("SOffline", "Imports Stack Overflow data dumps");
    cmdr.add_command("test", std::unique_ptr<cli::Command>(new cli::TestCommand()));
    cmdr.add_command("import", std::unique_ptr<cli::Command>(new cli::ImportCommand()));
    cmdr.run(argc, argv);
    return 0;
}