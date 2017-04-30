//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
#define SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H

#include "tinyxml2.h"
#include "xml/util.h"
#include "models.h"
#include <iostream>
#include <string>
#include <vector>

namespace xml {

    template <typename M>
    class XMLAttributeImporter : public tinyxml2::XMLVisitor {
    public:
        XMLAttributeImporter(std::string path, std::string rootElemName);

        virtual bool VisitEnter(const tinyxml2::XMLElement &elem, const tinyxml2::XMLAttribute *attr) override;

        virtual std::vector<M> parse();

    protected:
        std::string rootElemName, path;
        bool rootHandled;
        std::vector<M> results;
        tinyxml2::XMLDocument doc;
    };

    template <typename M>
    bool XMLAttributeImporter<M>::VisitEnter(const tinyxml2::XMLElement &elem, const tinyxml2::XMLAttribute *attr) {
        if (!rootHandled ) {
            if (std::string(elem.Name()) != rootElemName) {
                std::cout << elem.Name() << std::endl;
                throw IncorrectFileException();
            } else {
                rootHandled = true;
                return true;
            }
        }


        if (rootHandled) {
            M m {};
            std::unordered_map<std::string, std::pair<models::ImportType, void*>> mapping = m.xml_map();
            while (attr != nullptr) {
                const auto &iter = mapping.find(std::string(attr->Name()));
                if (iter == mapping.end()) {
                    attr = attr->Next();
                    continue;
                }
                std::pair<models::ImportType, void*> props = (*iter).second;
                tinyxml2::XMLError err = tinyxml2::XML_SUCCESS;
                switch (props.first) {
                    case models::ImportType::Int64:
                        err = attr->QueryInt64Value((int64_t *)props.second);
                        break;
                    case models::ImportType::String:
                        *((std::string*)props.second) = attr->Value();
                        break;
                    case models::ImportType::Datetime:
                        *((std::tm*)props.second) = parse_time(attr->Value());
                        break;
                    case models::ImportType::Bool:
                        bool *p = (bool*) props.second;
                        std::string(attr->Value()) == "True" ? (*p = true) : (*p = false);
                        break;
                }
                if (err != tinyxml2::XML_SUCCESS) {
                    throw Exception(err);
                }
                attr = attr->Next();
            }
            results.push_back(std::move(m));
        }
        return true;
    }

    template <typename M>
    XMLAttributeImporter<M>::XMLAttributeImporter(std::string path, std::string rootElemName):
            rootElemName(rootElemName), rootHandled(false), doc(), path(path) {}

    template <typename M>
    std::vector<M> XMLAttributeImporter<M>::parse() {
        tinyxml2::XMLError result = doc.LoadFile(path.c_str());
        if (result != tinyxml2::XML_SUCCESS) {
            throw Exception(result);
        }
        doc.Accept(this);
        return results;
    }
}
#endif //SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
