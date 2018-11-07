/*
  @file get_language_from_filename.hpp

  Declaration of get_language_from_filename()
*/

#ifndef INCLUDE_GET_LANGUAGE_FROM_FILENAME_HPP
#define INCLUDE_GET_LANGUAGE_FROM_FILENAME_HPP

#include <string>

/** Language based on the filename
 * @param  filename Name of a source-code file
 * @retval language Programming language, empty string if no associated language
 */
std::string get_language_from_filename(const std::string& filename);

#endif
