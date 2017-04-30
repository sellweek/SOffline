//
// Created by Róbert Selvek on 30/04/2017.
//

#include <ostream>

#include "models.h"

namespace models {
    std::ostream &operator <<(std::ostream &os, const models::Model &m) {
        for (const auto &pair : m.xml_map()) {
            os << pair.first << "=";
            switch (pair.second.first) {
                case ImportType::Int64:
                    os << *((int64_t*)pair.second.second);
                    break;
                case ImportType::String:
                    os << "'" << *((std::string*)pair.second.second) << "'";
                    break;
                case ImportType::Datetime:
                    os << std::put_time((std::tm*)pair.second.second, "%c");
                    break;
                case ImportType::Bool:
                    os << *((bool*)pair.second.second);
                    break;
            }
            os << ' ';
        }
        os << std::endl;
        return os;
    }

    std::unordered_map<std::string, std::pair<ImportType, void*>> Badge::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"UserId", {ImportType::Int64, (void *)&user}},
                {"Name", {ImportType::String, (void *)&name}},
                {"Date", {ImportType::Datetime, (void *)&date}},
                {"Class", {ImportType::Int64, (void *)&badge_class}},
                {"TagBased", {ImportType::Bool, (void *)&tag_based}},
        };
        return m;
    };

    std::unordered_map<std::string, std::pair<ImportType, void *>> Comment::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"UserId", {ImportType::Int64, (void *)&user}},
                {"PostId", {ImportType::Int64, (void *)&post}},
                {"Score", {ImportType::Int64, (void *)&score}},
                {"Text", {ImportType::String, (void *)&text}},
                {"CreationDate", {ImportType::Datetime, (void *)&date}},
        };
        return m;
    }

    std::unordered_map<std::string, std::pair<ImportType, void *>> PostHistoryEntry::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"UserId", {ImportType::Int64, (void *)&user}},
                {"PostId", {ImportType::Int64, (void *)&post}},
                {"PostHistoryTypeId", {ImportType::Int64, (void *)&type}},
                {"CreationDate", {ImportType::Datetime, (void *)&date}},
                {"RevisionGUID", {ImportType::String, (void *)&guid}},
                {"Comment", {ImportType::String, (void *)&comment}},
                {"Text", {ImportType::String, (void *)&text}},
        };
        return m;
    }

    std::unordered_map<std::string, std::pair<ImportType, void *>> Post::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"PostTypeId", {ImportType::Int64, (void *)&type}},
                {"ParentId", {ImportType::Int64, (void *)&parent}},
                {"AcceptedAnswerId", {ImportType::Int64, (void *)&accepted_answer}},
                {"Score", {ImportType::Int64, (void *)&score}},
                {"ViewCount", {ImportType::Int64, (void *)&views}},
                {"Title", {ImportType::String, (void *)&title}},
                {"Body", {ImportType::String, (void *)&body}},
                {"OwnerUserId", {ImportType::Int64, (void *)&owner}},
                {"LastEditorUserId", {ImportType::Int64, (void *)&last_editor}},
                {"LastEditDate", {ImportType::Datetime, (void *)&last_edit}},
                {"LastActivityDate", {ImportType::Datetime, (void *)&last_activity}},
                {"CreationDate", {ImportType::Datetime, (void *)&created_at}},
                {"ClosedDate", {ImportType::Datetime, (void *)&closed_at}},
        };
        return m;
    }

    std::unordered_map<std::string, std::pair<ImportType, void *>> PostLink::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"PostId", {ImportType::Int64, (void *)&source}},
                {"RelatedPostId", {ImportType::Int64, (void *)&target}},
                {"LinkTypeId", {ImportType::Int64, (void *)&type}},
                {"CreationDate", {ImportType::Datetime, (void *)&date}},
        };
        return m;
    }

    std::unordered_map<std::string, std::pair<ImportType, void *>> Tag::xml_map() const {
        std::unordered_map<std::string, std::pair<ImportType, void*>> m {
                {"Id", {ImportType::Int64, (void *)&id}},
                {"WikiPostId", {ImportType::Int64, (void *)&wiki}},
                {"ExcerptPostId", {ImportType::Int64, (void *)&excerpt}},
                {"TagName", {ImportType::String, (void *)&name}},
        };
        return m;
    }
}