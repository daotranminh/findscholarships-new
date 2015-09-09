#include <string>
#include "utilities/ConstantStrings.h"

namespace findscholarships {

ConstantStrings::ConstantStrings()
: PrefixBegin("__BEGIN_____"),
PrefixDeadline("__DEADLINE__="),
PrefixTitle("__TITLE_____="),
PrefixFilename("__FILENAME__="),
PrefixURL("__URL_______="),
PrefixWebpage("__WEBPAGE___="),
PrefixEnd("__END_______")
{
    std::string sign1 = "application deadline is: ";
    std::string sign2 = "application deadline is";
    std::string sign3 = "deadline to apply is ";
    DeadlineSigns.push_back(sign1);
    DeadlineSigns.push_back(sign2);
    DeadlineSigns.push_back(sign3);
    
    std::string january   = "january";
    std::string february  = "february";
    std::string march     = "march";
    std::string april     = "april";
    std::string may       = "may";
    std::string june      = "june";
    std::string july      = "july";
    std::string august    = "august";
    std::string september = "september";
    std::string october   = "october";
    std::string november  = "november";
    std::string december  = "december";
    
    FullMonthNames.push_back(january);
    FullMonthNames.push_back(february);
    FullMonthNames.push_back(march);
    FullMonthNames.push_back(april);
    FullMonthNames.push_back(may);
    FullMonthNames.push_back(june);
    FullMonthNames.push_back(july);
    FullMonthNames.push_back(august);
    FullMonthNames.push_back(september);
    FullMonthNames.push_back(october);
    FullMonthNames.push_back(november);
    FullMonthNames.push_back(december);
    
    std::string jan = "jan";
    std::string feb = "feb";
    std::string mar = "mar";
    std::string apr = "apr";
    std::string jun = "jun";
    std::string jul = "jul";
    std::string aug = "aug";
    std::string sep = "sep";
    std::string oct = "oct";
    std::string nov = "nov";
    std::string dec = "dec";
    
    ShortMonthNames.push_back(jan);
    ShortMonthNames.push_back(feb);
    ShortMonthNames.push_back(mar);
    ShortMonthNames.push_back(apr);
    ShortMonthNames.push_back(may);
    ShortMonthNames.push_back(jun);
    ShortMonthNames.push_back(jul);
    ShortMonthNames.push_back(aug);
    ShortMonthNames.push_back(sep);
    ShortMonthNames.push_back(oct);
    ShortMonthNames.push_back(nov);
    ShortMonthNames.push_back(dec);
}



ConstantStrings*
ConstantStrings::_instance = NULL;



ConstantStrings*
ConstantStrings::instance()
{
    if (_instance == NULL)
    {
        _instance = new ConstantStrings;
    }
    
    return _instance;
}
    
} // namespace findscholarships
