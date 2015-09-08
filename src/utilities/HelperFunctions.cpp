#include "HelperFunctions.h"
#include <iostream>


void
killSpecialChar(std::string& s,
                char c)
{
    std::size_t pos = s.find(c);
    while (pos != std::string::npos)
    {
        s.replace(pos, 1, "");
        pos = s.find(c);
    }
}



void
strReplace(std::string& s,
           const std::string& source,
           const std::string& target)
{
    std::size_t pos = s.find(source);
    while (pos != std::string::npos)
    {
        s.replace(pos, source.length(), target);
        pos = s.find(source);
    }
}



// trim spaces
void
strTrim(std::string& s)
{
    size_t position = s.find_last_not_of(" \t");
    
    if (std::string::npos != position)
    {
        s = s.substr(0, position+1);
    }
    
    position = s.find_first_not_of(" \t");
    if (std::string::npos != position)
    {
        s = s.substr(position);
    }
}



// Get current date/time, format is YYYYMMDDHHmmss
const std::string
currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tstruct);
    
    return buf;
}



void
extractLink(std::string &s)
{
    // s is of the form: <A HREF=link>
    strReplace(s, "\"", "");
    strReplace(s, "<A HREF=", "");
    strReplace(s, "rel=nofollow", "");
    strReplace(s, ">", "");
    strReplace(s, " ", "");
    
    if (s != "" && s.find("http://") == std::string::npos) s = "http://" + s;
}



std::string
getStringInBetween(const std::string &s,
                   const std::string &sbeg,
                   const std::string &send)
{
    std::size_t beg = s.rfind(sbeg) + sbeg.length();
    std::size_t end = s.rfind(send);
    
    return s.substr(beg, end - beg);
}



void
convertToLower(std::string &s)
{
    for(std::size_t i = 0; s[i]; i++)
    {
        s[i] = std::tolower(s[i]);
    }  
}
