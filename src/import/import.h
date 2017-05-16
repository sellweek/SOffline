#ifndef SEMESTRALKA_IMPORT_H
#define SEMESTRALKA_IMPORT_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "models.h"
#include "sqlite/SqliteClient.h"

/// Contains classes used to perform the whole process of transferring data
/// from Stack Exchange XML files to SQLite database.
/// import.cpp file also contains the database schema.
namespace import {
    /// Importer imports a Stack Exchange XML export unzipped into a directory
    /// and imports it into SQLite.
    class Importer {
    public:
        /**
        * Construct an Importer.
        * @param sources Path to the directory with XML files.
        * @param destination_db Path to SQLite database that should be created or overwritten.
        */
        Importer(std::string sources, const std::string &destination_db);

        /**
        * Perform the import procedure, logging its progress to std::cout.
        */
        void import_all();

    private:
        std::string directory;
        sqlite::Client db;
        using XMLData = std::unordered_map<std::string, std::vector<std::shared_ptr<models::Model>>>;

        XMLData import_xml() const;
        void save_to_sqlite(const XMLData &data);
        void prepare_db();
        std::vector<std::unique_ptr<models::PostTag>>
        make_post_tags(const std::vector<std::unique_ptr<models::Tag>> &tags,
                       const std::vector<std::unique_ptr<models::Post>> &posts) const;
        /**
         * SQLite only supports a limited number of placeholders in a single statement,
         * so an insert of a single vector of models has to be split into multiple statements.
         * This function splits data into multiple insertable vectors and inserts those into the database.
         * @param data Models to insert.
         */
        void insert_with_max_len(const std::string &table, const std::vector<std::shared_ptr<models::Model>> &data);
        static const std::string schema;
    };
}

#endif