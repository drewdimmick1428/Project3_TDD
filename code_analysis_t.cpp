/*
  @file code_analysis_t.cpp

  Test program for analysis requests
*/

#include "code_analysis.hpp"

#include <string>
#include <cassert>

int main() {

    // option language
    {
        analysis_request request;
        request.source_code = R"(if (a < b) a = b;)";
        request.disk_filename  = "";
        request.entry_filename  = "";
        request.option_filename = "";
        request.source_url       = "";
        request.option_url      = "";
        request.option_language = "C++";
        request.default_language = "java";
        request.option_loc = -1;

        /*assert(formatAnalysisXML(request) =="(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
									<code:unit xmlns:code="http://mlcollard.net/code" language="C++">
									if (a &lt; b) a = b;
									</code:unit>);*/
		request.source_code = R"(if (a < b) a = b;)";
        
        // Rule #1
		request.disk_filename  = "filename.cpp";
		request.entry_filename = "entry.cpp";
		assert(fileNameAnalysis(request) == request.entry_filename);
        
        // Rule #2
        request.option_filename = "option.cpp";
        assert(fileNameAnalysis(request) == request.option_filename);
        
        // Rule #3
        request.disk_filename = "data";
        assert(fileNameAnalysis(request) == request.disk_filename);
        
        // Rule #4
        request.source_url = "source";
        request.option_url = "optionUrl";
        assert(urlAnalysis(request) == request.option_url);
        
        // Rule #5
        assert(languageAnalysis(request) == request.option_language);
        
        // Rule #6
        request.disk_filename = "file.cpp";
        assert(get_language_from_filename(request.disk_filename) == "C++");
        
        // Rule #7
        request.disk_filename = "-";
        assert(fileNameAnalysis(request) == request.entry_filename);
        request.entry_filename = "";
        assert(fileNameAnalysis(request) == request.option_filename);
        
    }

    return 0;
}
