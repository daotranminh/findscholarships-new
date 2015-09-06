#ifndef ___HTML_RESULT_HPP___
#define ___HTML_RESULT_HPP___

#include "Title.h"  // htmlgen

class HtmlResult
{
public:
    HtmlResult();
    
    HtmlResult(const std::string &full_html_code,
               const DatePtr &deadline,
               const Title &title);
    
    const std::string&
    getFullHtmlCode() const;
    
    void
    setFullHtmlCode(const std::string &fhc);
    
    DatePtr
    getDeadline() const;
    
    void
    setDeadline(const DatePtr &dl);
    
    void
    setDeadline(const std::string &str_deadline);
    
    const Title&
    getTitle() const;
    
    void
    setTitle(const Title &t);
    
private:
    std::string m_FullHtmlCode;
    DatePtr     m_Deadline;
    Title       m_Title;
};

#endif // ___HTML_RESULT_HPP___
