/***********************************************************************************
 *                                                                                 *
 * Voreen - The Volume Rendering Engine                                            *
 *                                                                                 *
 * Copyright (C) 2005-2013 University of Muenster, Germany.                        *
 * Visualization and Computer Graphics Group <http://viscg.uni-muenster.de>        *
 * For a list of authors please refer to the file "CREDITS.txt".                   *
 *                                                                                 *
 * This file is part of the Voreen software package. Voreen is free software:      *
 * you can redistribute it and/or modify it under the terms of the GNU General     *
 * Public License version 2 as published by the Free Software Foundation.          *
 *                                                                                 *
 * Voreen is distributed in the hope that it will be useful, but WITHOUT ANY       *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR   *
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.      *
 *                                                                                 *
 * You should have received a copy of the GNU General Public License in the file   *
 * "LICENSE.txt" along with this file. If not, see <http://www.gnu.org/licenses/>. *
 *                                                                                 *
 * For non-commercial academic use see the license exception specified in the file *
 * "LICENSE-academic.txt". To get information about commercial licensing please    *
 * contact the authors.                                                            *
 *                                                                                 *
 ***********************************************************************************/

#ifndef VRN_STRINGUTILS_H
#define VRN_STRINGUTILS_H

#include "voreen/core/voreencoreapi.h"
#include "voreen/core/utils/exception.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace voreen {

/// Converts an int to a string.
VRN_CORE_API std::string itos(int i, int stringLength = -1, char fillChar = '0');

/// Converts an uint32_t to a string.
VRN_CORE_API std::string itos(uint32_t i, int stringLength = -1, char fillChar = '0');

/// Converts an uint64_t to a string.
VRN_CORE_API std::string itos(uint64_t i, int stringLength = -1, char fillChar = '0');

/**
 * Converts a float to a string.
 *
 * @param precision number of decimals to print.
 *  For precision=-1, sprintf's standard floating point formatting is used (%f).
 */
VRN_CORE_API std::string ftos(float f, int precision = -1);

/**
 * Converts a double to a string.
 *
 * @param precision number of decimals to print.
 *  For precision=-1, sprintf's standard floating point formatting is used (%f).
 */
VRN_CORE_API std::string dtos(double d, int precision = -1);

/**
 * Converts the string to a null-terminated char array with length s.size()+1.
 * Deleting the allocated memory is up to the caller.
 */
VRN_CORE_API char* strToChr(const std::string& s);

/// Generic to-string conversion using a stringstream.
template<class T>
std::string genericToString(const T& value);

/**
 * Generic from-string conversion using a stringstream.
 *
 * @throw VoreenException if the conversion failed
 */
template<class T>
T genericFromString(const std::string& str)
    throw (VoreenException);

/// MSVC++ 2010 and later already provides the sto* functions in the <string> header
#if !defined(_MSC_VER) || (_MSC_VER < 1600)
/// Converts a string to an int using stringstreams
VRN_CORE_API int stoi(const std::string& s);

/// Converts a string to a float using stringstreams
VRN_CORE_API float stof(const std::string& s);

/// Converts a string to a double using stringstreams
VRN_CORE_API double stod(const std::string& s);
#endif // !defined(_MSC_VER) || (_MSC_VER < 1600)

/**
 * Returns a copy of \p str where all occurrences of \p from have been replaced by \p to.
 */
VRN_CORE_API std::string strReplaceAll(const std::string& str, const std::string& from, const std::string& to);

/// Returns a copy of \p str where the first occurrence of \p from has been replaced by \p to.
VRN_CORE_API std::string strReplaceFirst(const std::string& str, const std::string& from, const std::string& to);

/// Returns a copy of \p str where the last occurrence of \p from has been replaced by \p to.
VRN_CORE_API std::string strReplaceLast(const std::string& str, const std::string& from, const std::string& to);

/**
 * Removes whitespaces from beginning and end of a string.
 *
 * @param str Input string.
 * @param charlist Characters to remove, defaults to space, tab, newline, carriage return, 0, vertical tab.
 */
VRN_CORE_API std::string trim(std::string str, const std::string& charlist = " \t\n\r\0\x0B");

/// Converts a string to lower case.
VRN_CORE_API std::string toLower(const std::string& str);

/// Converts a string to upper case.
VRN_CORE_API std::string toUpper(const std::string& str);

/**
 * Splits a string by the specified delimiter and returns the items in a vector.
 */
VRN_CORE_API std::vector<std::string> strSplit(const std::string& str, char delim);
/// @overload
VRN_CORE_API std::vector<std::string> strSplit(const std::string& str, const std::string& delim);

/**
 * Joins a sequence of tokens to a string. The converted tokens
 * are separated by the specified delimiter.
 */
template<typename T>
std::string strJoin(const std::vector<T>& tokens, const std::string& delim);

/// Returns true if \p input ends with \p ending
VRN_CORE_API bool endsWith(const std::string& input, const std::string& ending);

/// Returns true if \p input starts with \p ending
VRN_CORE_API bool startsWith(const std::string& input, const std::string& start);


// ----------------------------------------------------------------------------
// template definitions

template<class T>
std::string genericToString(const T& value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

template<class T>
T genericFromString(const std::string& str) throw (VoreenException) {
    T result;
    std::istringstream stream;
    stream.str(str);
    if ((stream >> result) == 0)
        throw VoreenException("failed to convert string '" + str + "'");
    return result;
}

template<typename T>
std::string strJoin(const std::vector<T>& tokens, const std::string& delim) {
    if (tokens.empty())
        return "";
    std::stringstream s;
    s << tokens.at(0);
    for (size_t i=1; i<tokens.size(); i++)
        s << delim << tokens.at(i);
    return s.str();
}

} // namespace

#endif // VRN_STRINGUTILS_H
