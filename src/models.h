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

namespace models {
    enum class ExternalType {
        Int64,
        String,
        Datetime,
        Bool
    };

    struct SQLMetadata {
        const std::string columnName;
        const ExternalType columnType;
        void *valuePointer;

        SQLMetadata(std::string columnName, ExternalType columnType, void *valuePointer);
    };

    class Model {
        virtual std::unordered_map<std::string, std::pair<ExternalType, void*>> xml_map() const = 0;
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
