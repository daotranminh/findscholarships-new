#ifndef __DATE_CONVERTER_HPP__
#define __DATE_CONVERTER_HPP__

#include "DateType.h"

namespace findscholarships {

class DateConverter
{
public:
    static DateConverter*
    instance();
    
    DatePtr
    convert(const std::string &s);
    
private:
    DateConverter();
    
    void
    checkMonth(std::string &s,
               const std::vector<std::string> &strs,
               std::size_t &count_month,
               std::size_t &month);
    
    void
    checkYear(std::string &s,
              const std::size_t testYear,
              std::size_t &year);
    
    void
    checkDay(const std::string &s,
             std::size_t &day);
    
    bool
    isNumber(const std::string &s);
    
    static DateConverter *_instance;
};
    
} // namespace findscholarships

#endif // __DATE_CONVERTER_HPP__
