#include "htmlgen/HtmlGenScholarshipPosition.h"
#include "utilities/HelperFunctions.h"

namespace findscholarships {

void
HtmlGenScholarshipPosition::generate(FetchedInfoScholarship &fis,
                                     const std::string &filecontent)
{
    tree<HTML::Node>::iterator beg = m_Dom.begin();
    tree<HTML::Node>::iterator end = m_Dom.end();
    
    std::string deadline_sign = "Scholarship Application Deadline";
    std::string end_sign1 = "Further Official Scholarship Information and Application";
    std::string end_sign2 = "Further Scholarship Information and Application";
    std::string end_sign3 = "Further Internship Information and Application";
    std::stringstream stream_html_code;
    
    for (tree<HTML::Node>::iterator it = beg; it != end; ++it)
    {
        if (it->tagName() == "p")
        {
            std::string ct = it->content(filecontent);
            strReplace(ct, "atitle", "a title");
            strReplace(ct, "ahref", "a href");
            
            if (ct.find("scholarship-positions.com") != std::string::npos)
            {
                std::string tag_sign = "href=\"http://scholarship-positions.com";
                cleanTag(ct, tag_sign);
            }
            
            stream_html_code << it->text() << std::endl
            << ct << std::endl
            << it->closingText()
            << std::endl;
            
            // TODO: try out boost::date::gregorian for guessing deadline.
            // if (deadline == NULL && std::string::npos != ct.find(deadline_sign))
            //   {
            //     // try to get the deadline, but in case it's not possible, ask the administrate to enter it manually
            //     deadline = guessDate(ct);
            
            //     if (deadline == NULL)
            // 	{
            // 	  std::string guessed_date;
            // 	  std::cout << "HtmlGenScholarshipPosition::generate: please help me to find the deadline for this scholarship (yyyymmdd)" << std::endl;
            // 	  std::cout << "Give N if deadline is not available!" << std::endl;
            // 	  std::cout << ct << std::endl;
            // 	  std::cin >> guessed_date;
            
            // 	  if (guessed_date != "N")
            // 	    {
            // 	      deadline = new YYYYMMDD();
            // 	      deadline->convert(guessed_date);
            // 	    }
            // 	}
            //   }
            
            if (std::string::npos != ct.find(end_sign1) ||
                std::string::npos != ct.find(end_sign2) ||
                std::string::npos != ct.find(end_sign3))
            {
                break;
            }
            
        }		
        // else if (it->text() == "<h1 class=\"post-title\">")
        //   {
        //     fis.m_Title = it->content(filecontent);
        //   }
    }
    
    Title title(fis.m_Title);
    
    std::string full_html_code = stream_html_code.str();
    
    dressUp(full_html_code, title);
    
    m_HtmlResult.setFullHtmlCode(full_html_code);
    m_HtmlResult.setDeadline(fis.m_Deadline);
    m_HtmlResult.setTitle(title);
}

} // namespace findscholarships