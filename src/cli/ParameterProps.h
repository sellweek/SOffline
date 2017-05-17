//
// Created by Róbert Selvek on 12/05/2017.
//

#ifndef SEMESTRALKA_PARAMETERPROPS_H
#define SEMESTRALKA_PARAMETERPROPS_H

namespace cli {
    /**
    * Information about a command line argument accepted by a command
    */
    struct ParameterProps {
        /// Name of the argument, after stripping the leading -
        std::string name;
        /// Argument description which will be shown in the help command
        std::string description;
        /// If this is false and the argument doesn't have a default value,
        /// an error will be shown to the user if they don't supply the argument
        bool optional;
        /// Determines whether the argument is just boolean (false) or also accepts a value (true).
        bool hasParameter;
        /// Determines whether, if the parameter is not supplied, it is assigned a default value.
        /// Please note that default values are only assigned if the parameter is not optional,
        /// otherwise if the parameter is not supplied, it just won't appear in the map given to a command.
        bool hasDefault;
        /// The default value itself.
        std::string defaultValue;
    };

}

#endif //SEMESTRALKA_PARAMETERPROPS_H
