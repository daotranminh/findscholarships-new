#ifndef ___HTML_GEN_SCHOLARSHIPS_LINKS_HPP___
#define ___HTML_GEN_SCHOLARSHIPS_LINKS_HPP___

#include "HtmlGenBase.h"

class HtmlGenScholarshipsLinks : public HtmlGenBase
{
public:
    void
    generate(FetchedInfoScholarship &fis,
             const std::string &filecontent);
    
private:
    void
    cleanUp(std::string &s);
    
    void
    extractDeadline(std::string &date_representation);
};


#endif // ___HTML_GEN_SCHOLARSHIPS_LINKS_HPP___
