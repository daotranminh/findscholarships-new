#ifndef ___FETCHER_SCHOLARSHIP_LINKS_HPP___
#define ___FETCHER_SCHOLARSHIP_LINKS_HPP___

#include "FetcherBase.h"  // fetch

namespace findscholarships {

class FetcherScholarshipLinks : public FetcherBase
{
public:
    FetcherScholarshipLinks(const std::string &path,
                            const std::string &pathDatabase,
                            const std::string &filename_html_scholarship_links_gmail,
                            const std::string &filename_input_scholarship_links_gmail);
    
    ~FetcherScholarshipLinks();
    
    void
    fetch();
    
private:
    const std::string m_FilenameHtmlScholarshipLinksGmail;
    const std::string m_FilenameInputScholarshipLinksGmail;
};
    
} // namespace findscholarships

#endif // ___FETCHER_SCHOLARSHIP_LINKS_HPP___
