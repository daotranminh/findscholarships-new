#ifndef __CONSTANT_STRINGS_HPP__
#define __CONSTANT_STRINGS_HPP__

#include <string>
#include <vector>

class ConstantStrings
{
public:
    static ConstantStrings*
    instance();
    
    std::string PrefixBegin;
    std::string PrefixDeadline;
    std::string PrefixTitle;
    std::string PrefixFilename;
    std::string PrefixURL;
    std::string PrefixWebpage;
    std::string PrefixEnd;
    
    std::vector<std::string> DeadlineSigns;
    std::vector<std::string> FullMonthNames;
    std::vector<std::string> ShortMonthNames;
    
private:
    ConstantStrings();
    
    static ConstantStrings *_instance;
};

#endif // __CONSTANT_STRINGS_HPP__
