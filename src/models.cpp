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
                case ExternalType::Int64:
                    os << *((int64_t*)pair.second.second);
                    break;
                case ExternalType::String:
                    os << "'" << *((std::string*)pair.second.second) << "'";
                    break;
                case ExternalType::Datetime:
                    os << std::put_time((std::tm*)pair.second.second, "%c");
                    break;
                case ExternalType::Bool:
                    os << *((bool*)pair.second.second);
                    break;
            }
            os << ' ';
        }
        os << std::endl;
        return os;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void*>> Badge::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"UserId", {ExternalType::Int64, (void *)&user}},
                {"Name", {ExternalType::String, (void *)&name}},
                {"Date", {ExternalType::Datetime, (void *)&date}},
                {"Class", {ExternalType::Int64, (void *)&badgeClass}},
                {"TagBased", {ExternalType::Bool, (void *)&tagBased}},
        };
        return m;
    }

    std::vector<SQLMetadata> Badge::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"user", ExternalType::Int64, (void *)&user},
                {"name", ExternalType::String, (void *)&name},
                {"date", ExternalType::Datetime, (void *)&date},
                {"class", ExternalType::Int64, (void *)&badgeClass},
                {"tag_based", ExternalType::Bool, (void *)&tagBased},
        };
        return v;
    };

    std::unordered_map<std::string, std::pair<ExternalType, void *>> Comment::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"UserId", {ExternalType::Int64, (void *)&user}},
                {"PostId", {ExternalType::Int64, (void *)&post}},
                {"Score", {ExternalType::Int64, (void *)&score}},
                {"Text", {ExternalType::String, (void *)&text}},
                {"CreationDate", {ExternalType::Datetime, (void *)&date}},
        };
        return m;
    }

    std::vector<SQLMetadata> Comment::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"post", ExternalType::Int64, (void *)&post},
                {"score", ExternalType::Int64, (void *)&score},
                {"text", ExternalType::String, (void *)&text},
                {"creation_date", ExternalType::Datetime, (void *)&date},
                {"user", ExternalType::Int64, (void *)&user},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> PostHistoryEntry::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"UserId", {ExternalType::Int64, (void *)&user}},
                {"PostId", {ExternalType::Int64, (void *)&post}},
                {"PostHistoryTypeId", {ExternalType::Int64, (void *)&type}},
                {"CreationDate", {ExternalType::Datetime, (void *)&date}},
                {"RevisionGUID", {ExternalType::String, (void *)&guid}},
                {"Comment", {ExternalType::String, (void *)&comment}},
                {"Text", {ExternalType::String, (void *)&text}},
        };
        return m;
    }

    std::vector<SQLMetadata> PostHistoryEntry::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"type", ExternalType::Int64, (void *)&type},
                {"post", ExternalType::Int64, (void *)&post},
                {"guid", ExternalType::String, (void *)&guid},
                {"creation_date", ExternalType::Datetime, (void *)&date},
                {"user", ExternalType::Int64, (void *)&user},
                {"comment", ExternalType::String, (void *)&comment},
                {"text", ExternalType::String, (void *)&text},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> Post::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"PostTypeId", {ExternalType::Int64, (void *)&type}},
                {"ParentId", {ExternalType::Int64, (void *)&parent}},
                {"AcceptedAnswerId", {ExternalType::Int64, (void *)&acceptedAnswer}},
                {"Score", {ExternalType::Int64, (void *)&score}},
                {"ViewCount", {ExternalType::Int64, (void *)&views}},
                {"Title", {ExternalType::String, (void *)&title}},
                {"Body", {ExternalType::String, (void *)&body}},
                {"OwnerUserId", {ExternalType::Int64, (void *)&owner}},
                {"LastEditorUserId", {ExternalType::Int64, (void *)&lastEditor}},
                {"LastEditDate", {ExternalType::Datetime, (void *)&lastEdit}},
                {"LastActivityDate", {ExternalType::Datetime, (void *)&lastActivity}},
                {"CreationDate", {ExternalType::Datetime, (void *)&createdAt}},
                {"ClosedDate", {ExternalType::Datetime, (void *)&closedAt}},
                {"Tags", {ExternalType::String, (void *)&tagString}},
        };
        return m;
    }

    std::vector<SQLMetadata> Post::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"title", ExternalType::String, (void *)&title},
                {"post_type", ExternalType::Int64, (void *)&type},
                {"accepted_answer", ExternalType::Int64, (void *)&acceptedAnswer},
                {"parent", ExternalType::Int64, (void *)&parent},
                {"creation_date", ExternalType::Datetime, (void *)&createdAt},
                {"score", ExternalType::Int64, (void *)&score},
                {"views", ExternalType::Int64, (void *)&views},
                {"body", ExternalType::String, (void *)&body},
                {"owner", ExternalType::Int64, (void *)&owner},
                {"last_editor", ExternalType::Int64, (void *)&lastEditor},
                {"last_edit", ExternalType::Datetime, (void *)&lastEdit},
                {"last_activity", ExternalType::Datetime, (void *)&lastActivity},
                {"closed_at", ExternalType::Datetime, (void *)&closedAt},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> PostLink::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"PostId", {ExternalType::Int64, (void *)&source}},
                {"RelatedPostId", {ExternalType::Int64, (void *)&target}},
                {"LinkTypeId", {ExternalType::Int64, (void *)&type}},
                {"CreationDate", {ExternalType::Datetime, (void *)&date}},
        };
        return m;
    }

    std::vector<SQLMetadata> PostLink::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"created", ExternalType::Datetime, (void *)&date},
                {"source", ExternalType::Int64, (void *)&source},
                {"target", ExternalType::Int64, (void *)&target},
                {"type", ExternalType::Int64, (void *)&type},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> Tag::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"WikiPostId", {ExternalType::Int64, (void *)&wiki}},
                {"ExcerptPostId", {ExternalType::Int64, (void *)&excerpt}},
                {"TagName", {ExternalType::String, (void *)&name}},
        };
        return m;
    }

    std::vector<SQLMetadata> Tag::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"name", ExternalType::String, (void *)&name},
                {"excerpt", ExternalType::Int64, (void *)&excerpt},
                {"wiki", ExternalType::Int64, (void *)&wiki},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> User::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"Reputation", {ExternalType::Int64, (void *)&reputation}},
                {"UpVotes", {ExternalType::Int64, (void *)&upvotes}},
                {"DownVotes", {ExternalType::Int64, (void *)&downvotes}},
                {"AccountId", {ExternalType::Int64, (void *)&accountID}},
                {"DisplayName", {ExternalType::String, (void *)&displayName}},
                {"WebsiteUrl", {ExternalType::String, (void *)&website}},
                {"Location", {ExternalType::String, (void *)&location}},
                {"AboutMe", {ExternalType::String, (void *)&about}},
                {"CreationDate", {ExternalType::Datetime, (void *)&createdAt}},
                {"LastAccessDate", {ExternalType::Datetime, (void *)&lastAccess}},
        };
        return m;
    }

    std::vector<SQLMetadata> User::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"reputation", ExternalType::Int64, (void *)&reputation},
                {"created_at", ExternalType::Datetime, (void *)&createdAt},
                {"display_name", ExternalType::String, (void *)&displayName},
                {"last_access", ExternalType::Datetime, (void *)&lastAccess},
                {"website", ExternalType::String, (void *)&website},
                {"location", ExternalType::String, (void *)&location},
                {"about", ExternalType::String, (void *)&about},
                {"upvotes", ExternalType::Int64, (void *)&upvotes},
                {"downvotes", ExternalType::Int64, (void *)&downvotes},
                {"account_id", ExternalType::Int64, (void *)&accountID},
        };
        return v;
    }

    std::unordered_map<std::string, std::pair<ExternalType, void *>> Vote::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {
                {"Id", {ExternalType::Int64, (void *)&id}},
                {"PostId", {ExternalType::Int64, (void *)&post}},
                {"VoteTypeId", {ExternalType::Int64, (void *)&type}},
                {"UserId", {ExternalType::Int64, (void *)&user}},
                {"CreationDate", {ExternalType::Datetime, (void *)&date}},
        };
        return m;
    }

    std::vector<SQLMetadata> Vote::sql_map() const {
        std::vector<SQLMetadata> v {
                {"id", ExternalType::Int64, (void *)&id},
                {"post", ExternalType::Int64, (void *)&post},
                {"type", ExternalType::Int64, (void *)&type},
                {"user", ExternalType::Int64, (void *)&user},
                {"creation_date", ExternalType::Datetime, (void *)&date},
        };
        return v;
    }

    SQLMetadata::SQLMetadata(const std::string columnName, const ExternalType columnType, void *valuePointer):
            columnName(columnName), columnType(columnType), valuePointer(valuePointer) {}

    // PostTag is an M:N relation table in the SQLite database. It can't be deserialized from XML.
    std::unordered_map<std::string, std::pair<ExternalType, void *>> PostTag::xml_map() const {
        std::unordered_map<std::string, std::pair<ExternalType, void*>> m {};
        return m;
    }

    std::vector<SQLMetadata> PostTag::sql_map() const {
        std::vector<SQLMetadata> v {
                {"post", ExternalType::Int64, (void *)&post},
                {"tag", ExternalType::Int64, (void *)&tag},
        };
        return v;
    }
}