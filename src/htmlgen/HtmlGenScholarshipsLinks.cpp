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
        // encounter main content
        if (it->tagName() == "p")
        {
            while (true) {
                if (it->tagName() == "p")
                {
                    std::string ct = it->content(filecontent);
                    stream_html_code << it->text() << std::endl
                    << ct << std::endl
                    << it->closingText()
                    << std::endl;
                    
                    if (std::string::npos != ct.find(deadline_sign))
                    {
                        if (fis.m_Deadline == "")
                        {
                            // For ScholarshipLinks, this is normally the case, as the deadline is standardized.
                            tree<HTML::Node>::iterator beg_deadline = it.begin();
                            tree<HTML::Node>::iterator end_deadline = it.end();
                            
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
                it++;
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
