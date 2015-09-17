#ifndef ___HTML_GEN_DBWORLD_HPP___
#define ___HTML_GEN_DBWORLD_HPP___

#include "htmlgen/HtmlGenBase.h"

namespace findscholarships {

class HtmlGenDbworld : public HtmlGenBase
{
public:
    void
    generate(FetchedInfoScholarship &fis,
             const std::string &filecontent);
    
private:
    void
    initDelimeter(std::string &delimeter)
    {
        delimeter = "<br/>\n";
    }
};

} // namespace findscholarships

#endif // ___HTML_GEN_DBWORLD_HPP___
