//
// Created by Róbert Selvek on 29/04/2017.
//

#ifndef SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
#define SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H

#include "include/tinyxml2.h"
#include "xml_util.h"
#include "models.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/// Containes classes and functions related to deserializing Stack Exchange's
/// data dumps.
namespace xml {

    /**
    * This class implements the Visitor pattern used by tinyXML2 to deserialize models
    * from XML files. It uses models::Model's xml_map() method to automatically convert
    * attributes and save them to correct members of the model.
    * It is implemented to be able to work with Stack Exchange's XML exports which comprise
    * of one root element named after the model contained in the file. Every record is a child
    * of this node and has all of its data contained in the attributes.
    *
    * The preferred way to use this class is through XMLAttributeImporter::construct_and_parse
    * method.
    *
    * @tparam M Model to extract from the XML file. M must implement model's xml_map method.
    */
    template <typename M>
    class XMLAttributeImporter : public tinyxml2::XMLVisitor {
    public:
        /**
        * Construct an XMLAttributeImporter.
        * @param path Path to the XML file that should be imported.
        * @param rootElemName Name of file's root element. This is checked and if it doesn't match, an exception is thrown.
        */
        XMLAttributeImporter(std::string path, std::string rootElemName);

        /**
        * Implemented to satisfy XMLVisitor's interface.
        */
        virtual bool VisitEnter(const tinyxml2::XMLElement &elem, const tinyxml2::XMLAttribute *attr) override;

        /**
        * Parse the XML file.
        * @return Vector of unique_ptrs to deserialized models.
        */
        virtual std::vector<std::unique_ptr<M>> parse();

        /**
        * Creates an XMLAttributeImporter for XML file at the given path and 
        * returns the results of calling parse on it.
        * @param path Path to the XML file that should be imported.
        * @param rootElemName Name of file's root element. This is checked and if it doesn't match, an exception is thrown.
        * @returns Vector of unique_ptrs to deserialized models.
        */
        static std::vector<std::unique_ptr<M>> construct_and_parse(std::string path, std::string rootElemName)  {
            XMLAttributeImporter<M> importer(path, rootElemName);
            return std::move(importer.parse());
        }
    protected:
        std::string rootElemName, path;
        bool rootHandled;
        std::vector<std::unique_ptr<M>> results;
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
            auto m = new M();
            std::unordered_map<std::string, std::pair<models::ExternalType, void*>> mapping = m->xml_map();
            while (attr != nullptr) {
                const auto &iter = mapping.find(std::string(attr->Name()));
                if (iter == mapping.end()) {
                    attr = attr->Next();
                    continue;
                }
                std::pair<models::ExternalType, void*> props = (*iter).second;
                tinyxml2::XMLError err = tinyxml2::XML_SUCCESS;
                switch (props.first) {
                    case models::ExternalType::Int64:
                        err = attr->QueryInt64Value((int64_t *)props.second);
                        break;
                    case models::ExternalType::String:
                        *((std::string*)props.second) = attr->Value();
                        break;
                    case models::ExternalType::Datetime:
                        *((std::tm*)props.second) = parse_time(attr->Value());
                        break;
                    case models::ExternalType::Bool:
                        bool *p = (bool*) props.second;
                        std::string(attr->Value()) == "True" ? (*p = true) : (*p = false);
                        break;
                }
                if (err != tinyxml2::XML_SUCCESS) {
                    throw Exception(err);
                }
                attr = attr->Next();
            }
            results.push_back(std::unique_ptr<M>(m));
        }
        return true;
    }

    template <typename M>
    XMLAttributeImporter<M>::XMLAttributeImporter(std::string path, std::string rootElemName):
            rootElemName(rootElemName), path(path), rootHandled(false), doc() {}

    template <typename M>
    std::vector<std::unique_ptr<M>> XMLAttributeImporter<M>::parse() {
        tinyxml2::XMLError result = doc.LoadFile(path.c_str());
        if (result != tinyxml2::XML_SUCCESS) {
            throw Exception(result);
        }
        doc.Accept(this);
        return std::move(results);
    }
}
#endif //SEMESTRALKA_ATTRIBUTECOLLECTINGVISITOR_H
