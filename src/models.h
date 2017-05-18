//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_MODELS_H
#define SEMESTRALKA_MODELS_H

#include <cstdint>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <ostream>
#include <unordered_map>

/**
* Namespace models contains classes and structures used to move data through the program,
* representing different entities from Stack Exchange Data Dump and the ways they should
* be deserialized from XML and SQL and serialized to SQL.
*/
namespace models {
    /**
    * Enum representing different scalar types that can be loaded from an external source (XML or SQL).
    */
    enum class ExternalType {
        Int64,
        String,
        Datetime,
        Bool
    };

    /**
    * Represents metadata about a column in an SQL table.
    */
    struct SQLMetadata {
        const std::string columnName; /// Name of the column
        const ExternalType columnType; /// Type of the column
        void *valuePointer; /// Pointer to the respective member of the object returning this struct.

        SQLMetadata(std::string columnName, ExternalType columnType, void *valuePointer);
    };

    /**
    * Represents a data object that can be deserialized from XML and SQL and serialized to SQL.
    * XML files these models are based on are documented at
    * https://meta.stackexchange.com/questions/2677/database-schema-documentation-for-the-public-data-dump-and-sede
    */
    class Model {
    public:
        /**
        * Get a map which maps XML field names to their type and a pointer to the respective
        * member of the deserialized object into which they should be saved.
        * @return A map of XML deserialization metadata
        */
        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const = 0;
        /**
        * Get a vector of column medata in the object's SQL table.
        * *NOTE:* The columns must be returned in the same order they are used in the database,
        * otherwise many convenience functions will fail.
        * @return Column metadata, in the order of the columns in the database.
        */
        virtual std::vector<SQLMetadata> sql_map() const = 0;
        friend std::ostream &operator <<(std::ostream &os, const models::Model &m);
    };

    std::ostream &operator <<(std::ostream &os, const models::Model &m);


    struct Badge : public Model {
        int64_t id;
        int64_t user;
        std::string name;
        std::tm date;
        int64_t badgeClass;
        bool tagBased;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };


    struct Comment : public Model {
        int64_t id;
        int64_t post;
        int64_t score;
        std::string text;
        std::tm date;
        int64_t user;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };



    struct PostHistoryEntry : public Model {
        int64_t id;
        int64_t post;
        int64_t type;
        int64_t user;
        std::tm date;
        std::string guid;
        std::string comment;
        std::string text;
        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };


    struct PostLink : public Model {
        int64_t id;
        int64_t source;
        int64_t target;
        int64_t type;
        std::tm date;
        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

    struct Post : public Model {
        int64_t id;
        int64_t type;
        int64_t parent;

        int64_t acceptedAnswer;

        int64_t score;
        int64_t views;

        std::string title;
        std::string body;
        std::string tagString;

        int64_t owner;
        int64_t lastEditor;
        std::tm lastEdit;
        std::tm lastActivity;
        std::tm createdAt;
        std::tm closedAt;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

    struct Tag : public Model {
        int64_t id;
        int64_t wiki;
        int64_t excerpt;
        std::string name;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

    struct PostTag : public Model {
        int64_t post;
        int64_t tag;
        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

    struct User : public Model {
        int64_t id;
        int64_t reputation;
        int64_t upvotes;
        int64_t downvotes;
        int64_t accountID;
        std::string displayName;
        std::string website;
        std::string location;
        std::string about;
        std::tm createdAt;
        std::tm lastAccess;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

    struct Vote : public Model {
        int64_t id;
        int64_t post;
        int64_t type;
        int64_t user;
        std::tm date;

        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const override;
        virtual std::vector<SQLMetadata> sql_map() const override;
    };

}
#endif //SEMESTRALKA_MODELS_H
