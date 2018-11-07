/*
  @file get_language_from_filename.cpp

  Implementation of get_language_from_filename()
*/

#include "get_language_from_filename.hpp"

#include <unordered_map>
#include <string>

namespace {

    // mapping from file extension to programming language
    const std::unordered_map<std::string, std::string> ext2lang = {

        { ".c", "C" },
        { ".h", "C" },
        { ".i", "C" },
        { ".cpp", "C++" },
        { ".CPP", "C++" },
        { ".cp", "C++" },
        { ".hpp", "C++" },
        { ".cxx", "C++" },
        { ".hxx", "C++" },
        { ".cc", "C++" },
        { ".hh", "C++" },
        { ".c++", "C++" },
        { ".h++", "C++" },
        { ".C", "C++" },
        { ".H", "C++" },
        { ".tcc", "C++" },
        { ".ii", "C++" },
        { ".java", "Java" },
        { ".aj", "AspectJ" },
        { ".cs", "C#" },
    };
}

/** Language based on the filename
 * @param  filename Name of a source-code file
 * @retval language Programming language, empty string if no associated language
 */
std::string get_language_from_filename(const std::string& filename) {

    // extract the last extension from the filename, including the '.'
    int pos = filename.rfind('.');
    if (pos == std::string::npos)
        return "";
    auto extension = filename.substr(pos);

    // find the extension in the map
    auto extit = ext2lang.find(extension);
    if (extit == ext2lang.end())
        return "";

    // language for this extension from the map
    return extit->second;
}
