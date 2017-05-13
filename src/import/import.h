#ifndef SEMESTRALKA_IMPORT_H
#define SEMESTRALKA_IMPORT_H

#include <vector>
#include <memory>
#include <unordered_map>

#include "models.h"
#include "sqlite/sqlite_client.h"

namespace import {
    class Importer {
    public:
        Importer(std::string sources, const std::string &destination_db);
        void import_all();

    private:
        std::string directory;
        sqlite::Client db;
        using XMLData = std::unordered_map<std::string, std::vector<std::shared_ptr<models::Model>>>;

        XMLData import_xml() const;
        void save_to_sqlite(const XMLData &data);
        void prepare_db();
        /**
         * SQLite only supports a limited number of placeholders in a single statement,
         * so an insert of a single vector of models has to be split into multiple statements.
         * This function splits data into multiple insertable vectors inserts those into the database.
         * @param data Models to insert.
         */
        void insert_with_max_len(const std::string &table, const std::vector<std::shared_ptr<models::Model>> &data);
        static const std::string schema;
    };
}

#endif