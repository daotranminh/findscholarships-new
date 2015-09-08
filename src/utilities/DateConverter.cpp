#include <sstream>

#include "ConstantStrings.h"
#include "DateConverter.h"
#include "HelperFunctions.h"

namespace findscholarships {

DateConverter*
DateConverter::_instance = 0;


DateConverter::DateConverter()
{
}



DateConverter*
DateConverter::instance()
{
    if (_instance == NULL)
    {
        _instance = new DateConverter;
    }
    
    return _instance;
}


void
DateConverter::checkMonth(std::string &s,
                          const std::vector<std::string> &strs,
                          std::size_t &count_month,
                          std::size_t &month)
{
    for (std::vector<std::string>::const_iterator it = strs.begin(); it != strs.end(); ++it)
    {
        std::size_t pos = s.find(*it);
        while (pos != std::string::npos)
        {
            // count and remove the month name from s
            count_month++;
            s.replace(pos, it->length(), "");
            pos = s.find(*it);
            
            month = it - strs.begin() + 1;
        }
    }
}



void
DateConverter::checkYear(std::string &s,
                         const std::size_t testYear,
                         std::size_t &year)
{
    std::stringstream out;
    out << testYear;
    std::string strYear = out.str();
    
    std::size_t pos = s.find(strYear);
    if (pos != std::string::npos)
    {
        s.replace(pos, strYear.length(), "");
        year = testYear;
    }
}



bool
DateConverter::isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    
    while (it != s.end() && (*it == ' ' || isdigit(*it))) ++it;
    
    return (!s.empty() && it == s.end());
}



void
DateConverter::checkDay(const std::string &s,
                        std::size_t &day)
{
    if (isNumber(s))
    {
        day = std::atoi(s.c_str());
    }
}


DatePtr
DateConverter::convert(const std::string &str_date)
{
    DatePtr d;
    
    std::string s = str_date;
    convertToLower(s);
    
    strReplace(s, "&nbsp;", "");
    strReplace(s, "-", " ");
    
    std::size_t day = 0;
    std::size_t month = 0;
    std::size_t year = 0;
    std::size_t count_month = 0;
    
    checkMonth(s, ConstantStrings::instance()->FullMonthNames, count_month, month);
    checkMonth(s, ConstantStrings::instance()->ShortMonthNames, count_month, month);
    
    if (count_month != 1) return d;
    
    time_t now = time(0);
    struct tm *tstruct = localtime(&now);
    std::size_t currentYear = tstruct->tm_year + 1900;
    
    for (std::size_t i = 0; i < 3; i++)
    {
        if (year == 0) checkYear(s, currentYear + i, year);
    }
    
    if (year == 0) return d;
    
    checkDay(s, day);
    
    if (day == 0 || day > 31) return d;
    
    d = DatePtr(new Date_t(year, month, day));
    
    return d;
}
    
} // namespace findscholarships
