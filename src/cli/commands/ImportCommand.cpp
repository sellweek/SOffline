//
// Created by Róbert Selvek on 13/05/2017.
//

#include "ImportCommand.h"
#include <import/import.h>
#include <import/xml_util.h>

std::vector<cli::ParameterProps, std::allocator<cli::ParameterProps>> cli::ImportCommand::supported_params() const {
    std::vector<ParameterProps> parameters {
            {"db", "SQLite database to create or overwrite", false, true, true, DEFAULT_DB_LOCATION},
            {"src", "Directory with files to import", false, true, false, ""},
    };
    return parameters;
}

std::string cli::ImportCommand::summary() const {
    return "Import a dump in StackExchange format.";
}

std::string cli::ImportCommand::description() const {
    return "Creates an SQLite database filled with the data from data dump xml files in a directory.";
}

void cli::ImportCommand::run(std::unordered_map<std::string, std::string> args) {
	try {
    	import::Importer importer(args.at("src"), args.at("db"));
    	importer.import_all();
    } catch (xml::Exception e) {
        printer->bold("There was an error when parsing XML files: ");
        printer->normal(e.what());
        printer->newline();
        printer->normal("Is your Stack Exchange export data complete?");
        printer->newline();
    } catch (sqlite::Exception e) {
        log_sqlite_exception(e);
    }
}
