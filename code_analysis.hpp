/*
  @file code_analysis.hpp

  Header for analysis requests
*/

#ifndef INCLUDE_CODE_ANALYSIS_HPP
#define INCLUDE_CODE_ANALYSIS_HPP

#include "analysis_request.hpp"

#include <string>

/** Generate source analysis XML based on the request
 * Content is wrapped with an XML element that includes the metadata
 * @param request Data that forms the request
 * @retval Source analysis request in XML format
 * @retval Empty string if invalid
 */
std::string formatAnalysisXML(const analysis_request& request);

#endif
