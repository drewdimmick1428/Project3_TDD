/*
    xmlWrapper.hpp

    Creates XML of a single element around content:
    * Single-include file
    * Processes in UTF-8, and only in UTF-8
    * Requires namespace prefix and uri (non-blank)
*/

#include <string>
#include <cstring>

class xmlWrapper {
public:

    // constructor
    xmlWrapper(const std::string& prefix, const std::string& uri)
        : ns_prefix(prefix), ns_uri(uri) {

        if (uri.empty())
            throw std::invalid_argument("URI for namespace required");

        if (prefix.empty())
            throw std::invalid_argument("Non-default namespace prefix required");

        text = R"^^^(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>)^^^";
        text += "\n";
    }

    // starts the element
    // * Must not be preceded by call to attribute, content(), and endElement()
    // * Can only be called once
    void startElement(const std::string& name) {

        // verify is allowed
        switch (state) {
            case ROOT:
                break;
            case STARTTAG:
            case CONTENT:
            case COMPLETED:
                throw std::out_of_range("startElement() can only be called once");
        }

        // save the element name to write the end element
        local_name = name;

        // start of start tag
        text += "<";
        text += ns_prefix;
        text += ":";
        text += local_name;

        // namespace
        text += " ";
        text += "xmlns:";
        text += ns_prefix;
        text += "=\"";
        text += ns_uri;
        text += "\"";

        state = STARTTAG;
    }

    // appends attribute of form name="value"
    // * Must be preceded by call to startElement(), and before calls to content() and endElement()
    // * Can be called multiple times
    void attribute(const std::string& name, const std::string& value) {

        // verify is allowed
        switch (state) {
            case ROOT:
                throw std::out_of_range("startElement() must be called before attribute()");
            case STARTTAG:
                break;
            case CONTENT:
                throw std::out_of_range("attribute() cannot be called after content()");
            case COMPLETED:
                throw std::out_of_range("attribute() cannot be called after endElement()");
        }

        // attribute of the form name="value"
        text += " ";
        text += name;
        text += "=\"";
        text += value;
        text += "\"";
    }

    // ends wrapping element
    // * Must be preceded by call to startElement()
    // * Only allowed to be called once
    // * No calls to startElement() or content() after
    void endElement() {

        // verify is allowed
        switch (state) {
            case ROOT:
                throw std::out_of_range("startElement() must be called before endElement()");
            case STARTTAG:
            case CONTENT:
                break;
            case COMPLETED:
                throw std::out_of_range("endElement() can only be called once");
        }

        // end previous start tag if not closed
        if (state == STARTTAG)
            text += ">";

        // end element tag
        text += "</";
        text += ns_prefix;
        text += ":";
        text += local_name;
        text += ">\n";

        state = COMPLETED;
    }

    // appends content
    // * Must be preceded by call to startElement()
    // * Cannot be called after endElement()
    // * Multiple calls are allowed
    void content(const std::string& content) {

        switch (state) {
            case ROOT:
                throw std::out_of_range("startElement() must be called before content()");
            case STARTTAG:
            case CONTENT:
                break;
            case COMPLETED:
                throw std::out_of_range("content() cannot be called before endElement()");
        }

        // end previous start tag if not closed
        if (state == STARTTAG)
            text += ">";

        // insert content, escaping if needed
        if (strpbrk(content.c_str(), "<>&") == nullptr) {

            text += content;

        } else {
  
            for (char c : content) {
                if (c == '<') {
                    text += "&lt;";
                } else if (c == '>') {
                    text += "&gt;";
                } else if (c == '&') {
                    text += "&amp;";
                } else {
                    text += c;
                }
            }
        }

        state = CONTENT;
    }

    // current xml
    std::string xml() const { 

        // xml() is allowed for any state
        
        return text;
    }

private:
    std::string local_name;
    std::string ns_uri;
    std::string ns_prefix;
    std::string text;
    enum { ROOT, STARTTAG, CONTENT, COMPLETED } state = ROOT;
};
