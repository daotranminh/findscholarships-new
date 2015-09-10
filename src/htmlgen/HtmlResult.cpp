#include "htmlgen/HtmlResult.h"

namespace findscholarships {

HtmlResult::HtmlResult()
: m_FullHtmlCode("")
{ }



HtmlResult::HtmlResult(const std::string& full_html_code,
                       const DatePtr &deadline,
                       const Title &title)
: m_FullHtmlCode(full_html_code),
m_Deadline(deadline),
m_Title(title)
{ }



const std::string&
HtmlResult::getFullHtmlCode() const
{
    return m_FullHtmlCode;
}



void
HtmlResult::setFullHtmlCode(const std::string& fhc)
{
    m_FullHtmlCode = fhc;
}



DatePtr
HtmlResult::getDeadline() const
{
    return m_Deadline;
}


void
HtmlResult::setDeadline(const DatePtr &dl)
{
    m_Deadline = dl;
}


void
HtmlResult::setDeadline(const std::string &str_deadline)
{
    if (str_deadline.length() == 8)
    {
        Date_t dl(boost::gregorian::from_undelimited_string(str_deadline));
        m_Deadline = std::make_shared<Date_t>(dl);
        //m_Deadline = boost::shared_ptr<Date_t>(new Date_t(dl));
    }
    else
    {
        Date_t dl(boost::gregorian::from_uk_string(str_deadline));
        m_Deadline = std::make_shared<Date_t>(dl);
        //m_Deadline = boost::shared_ptr<Date_t>(new Date_t(dl));
    }
}




const Title&
HtmlResult::getTitle() const
{
    return m_Title;
}


void
HtmlResult::setTitle(const Title& t)
{
    m_Title = t;
}
    
} // namespace findscholarships
