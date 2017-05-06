#include <iostream>
#include <cstdint>
#include <chrono>
#include <string>
#include <fstream>

#include "import.h"
#include "models.h"

int main() {
    /*
    auto results = xml::import_all("/Users/selvek/Downloads/worldbuilding.stackexchange.com");
    std::cout << "Done, got " << results.users.size() << " users." << std::endl;
    std::cout << "Starting" << std::endl;
     */
    import::Importer imp("/Users/selvek/Downloads/worldbuilding.stackexchange.com", "/Users/selvek/Dev/fit/PA2/semestralka/db.sqlite");
    imp.import_all();
    return 0;
}