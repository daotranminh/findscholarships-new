#include "Node.h"                       // html
#include "HtmlGenScholarshipsLinks.h"   // htmlgen
#include "HelperFunctions.h"            // utilities
#include "Logger.h"                     // utilities

using namespace htmlcxx;

//TODO: Copy here
void
HtmlGenScholarshipsLinks::generate(FetchedInfoScholarship &fis,
                                   const std::string &filecontent)
{
    tree<HTML::Node>::iterator beg = m_Dom.begin();
    tree<HTML::Node>::iterator end = m_Dom.end();
    
    std::string deadline_sign = "Application Deadline : ";
    std::stringstream stream_html_code;
    
    for (tree<HTML::Node>::iterator it = beg; it != end; ++it)
    {
        if (fis.m_Title == "" && it->tagName() == "title")
        {
            fis.m_Title = it->content(filecontent);
            cleanUp(fis.m_Title);
        }
        
        if ((it->tagName() == "div") && (it->text() == "<div id=\"maincol\">"))
        {
            tree<HTML::Node>::iterator beg_main_content = it.begin();
            tree<HTML::Node>::iterator end_main_content = it.end();
            
            // This go a long a DFS way until the leaf, hence some text will be repeated. Need to think how to make it cleaner.
            for (tree<HTML::Node>::iterator content_it = beg_main_content; content_it != end_main_content; content_it++)
            {
                if (content_it->tagName() == "P" ||
                    content_it->tagName() == "p" ||
                    content_it->tagName() == "ul" ||
                    content_it->tagName() == "pre")
                {
                    std::string ct = content_it->content(filecontent);
                    
                    stream_html_code << content_it->text() << std::endl
                    << ct << std::endl
                    << content_it->closingText()
                    << std::endl;
                    
                    if (std::string::npos != ct.find(deadline_sign))
                    {
                        if (fis.m_Deadline == "")
                        {
                            // For ScholarshipLinks, this is normally the case, as the deadline is standardized.
                            tree<HTML::Node>::iterator beg_deadline = content_it.begin();
                            tree<HTML::Node>::iterator end_deadline = content_it.end();
                            
                            for (tree<HTML::Node>::iterator deadline_it = beg_deadline;
                                 deadline_it != end_deadline; deadline_it++)
                            {
                                ct = deadline_it->text();
                                if (std::string::npos != ct.find(deadline_sign))
                                {
                                    fis.m_Deadline = deadline_it->text();
                                    extractDeadline(fis.m_Deadline);
                                    break; // got the deadline, done
                                }
                            }
                        }
                        
                        break; // done with main content
                    }
                }
            }
            
            break;
        }
    }
    
    Title title(fis.m_Title);
    
    std::string full_html_code = stream_html_code.str();
    dressUp(full_html_code, title);
    
    m_HtmlResult.setFullHtmlCode(full_html_code);
    m_HtmlResult.setDeadline(fis.m_Deadline);
    m_HtmlResult.setTitle(title);
}



void
HtmlGenScholarshipsLinks::cleanUp(std::string &s)
{
    strReplace(s, " : ", ": ");
    strReplace(s, " - Scholarships-Links.com", "");
}



void
HtmlGenScholarshipsLinks::extractDeadline(std::string &date_representation)
{
    std::vector<std::string> redundants;
    redundants.push_back("Application Deadline :");
    redundants.push_back("Application Deadline:");
    
    for (std::vector<std::string>::const_iterator it = redundants.begin(); it != redundants.end(); ++it)
    {
        std::size_t pos = date_representation.find(*it);
        if (pos != std::string::npos)
        {
            date_representation = date_representation.substr(pos + it->length());
        }
    }
    
    // string normalization
    while (date_representation[0] == ' ')
    {
        date_representation = date_representation.substr(1);
    }
    
    while (date_representation[date_representation.length()-1] == ' ')
    {
        date_representation = date_representation.substr(0, date_representation.length()-1);
    }
    
    strReplace(date_representation, " ", "-");
}
