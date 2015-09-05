#ifndef ___FETCHER_SCHOLARSHIP_POSITIONS_HPP___
#define ___FETCHER_SCHOLARSHIP_POSITIONS_HPP___

#include "FetcherBase.h"  // fetch

class FetcherScholarshipPositions : public FetcherBase
{
public:
    FetcherScholarshipPositions(const std::string &path,
                                const std::string &pathDatabase,
                                const std::string &filename_html_scholarship_positions_gmail,
                                const std::string &filename_input_scholarship_positions_gmail);
    
    ~FetcherScholarshipPositions();
    
    void
    fetch();
    
private:
    void
    fetchOneScholarshipPosition(std::ofstream &file_output,
                                const std::string &now,
                                std::size_t &count,
                                const std::string &link_title_str,
                                const std::string &deadline_str);
    
private:
    const std::string m_FilenameHtmlScholarshipPositionsGmail;
    const std::string m_FilenameInputScholarshipPositionsGmail;
};

#endif // ___FETCHER_SCHOLARSHIP_POSITIONS_HPP___
