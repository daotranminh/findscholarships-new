#include "htmlgen/HtmlGenDbworld.h"

namespace findscholarships {

void
HtmlGenDbworld::generate(FetchedInfoScholarship &fis,
                         const std::string &filecontent)
{
    tree<HTML::Node>::iterator beg = m_Dom.begin();
    tree<HTML::Node>::iterator end = m_Dom.end();
    
    std::string full_html_code;
    
    for (tree<HTML::Node>::iterator it = beg; it != end; ++it)
    {
        if (it->tagName() == "PRE")
        {
            full_html_code = it->content(filecontent);
            break;
        }
    }
    
    Title title(fis.m_Title);
    
    if (fis.m_Webpage != "")
    {
        full_html_code = full_html_code + "<br/>\n<a href=\"" + fis.m_Webpage + "\">Further Information</a>\n";
    }
    
    dressUp(full_html_code, title);
    
    m_HtmlResult.setFullHtmlCode(full_html_code);
    m_HtmlResult.setDeadline(fis.m_Deadline);
    m_HtmlResult.setTitle(title);
}

} // namespace findscholarships
