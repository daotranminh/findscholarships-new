#ifndef ___HTML_GEN_SCHOLARSHIP_POSITION_HPP___
#define ___HTML_GEN_SCHOLARSHIP_POSITION_HPP___

#include "HtmlGenBase.h"    // htmlgen

namespace findscholarships {

class HtmlGenScholarshipPosition : public HtmlGenBase
{
public:
    void
    generate(FetchedInfoScholarship &fis,
             const std::string &filecontent);
};
    
} // namespace findscholarships

#endif // ___HTML_GEN_SCHOLARSHIP_POSITION_HPP___
