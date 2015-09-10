#ifndef ___HELPER_FUNCTIONS_HPP___
#define ___HELPER_FUNCTIONS_HPP___

#include <string>

void
killSpecialChar(std::string& s,
                char c);

void
strReplace(std::string& s,
           const std::string& source,
           const std::string& target);

void
strTrim(std::string& s);


const std::string
currentDateTime();


void
extractLink(std::string &s);


std::string
getStringInBetween(const std::string &s,
                   const std::string &sbeg,
                   const std::string &send);

void
convertToLower(std::string &s);

#endif // ___HELPER_FUNCTIONS_HPP___
