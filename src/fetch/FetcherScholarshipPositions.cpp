#include "FetcherScholarshipPositions.h"    // fetch
#include "ConstantStrings.h"                // utilities
#include "DateConverter.h"                  // utilities
#include "DateType.h"                       // utilities
#include "HelperFunctions.h"                // utilities
#include "Logger.h"                         // utilities

namespace findscholarships {

FetcherScholarshipPositions::FetcherScholarshipPositions(const std::string &path,
                                                         const std::string &pathDatabase,
                                                         const std::string &filename_html_scholarship_positions_gmail,
                                                         const std::string &filename_input_scholarship_positions_gmail)
: FetcherBase(path, pathDatabase),
m_FilenameHtmlScholarshipPositionsGmail(m_Path + filename_html_scholarship_positions_gmail),
m_FilenameInputScholarshipPositionsGmail(m_Path + filename_input_scholarship_positions_gmail)
{ }



FetcherScholarshipPositions::~FetcherScholarshipPositions()
{ }


void
FetcherScholarshipPositions::fetchOneScholarshipPosition(std::ofstream &file_output,
                                                         const std::string &now,
                                                         std::size_t &count,
                                                         const std::string &link_title_str,
                                                         const std::string &deadline_str)
{
    std::string sign1 = "<a class=\"validating\" href=\"";
    std::string sign2 = "\">";
    std::string sign3 = "\">";
    std::string sign4 = "</a>";
    
    std::string s = link_title_str;
    strReplace(s, "\n", " ");
    
    FetchedInfoScholarship fis;
    fis.m_URL = getStringInBetween(s, sign1, sign2);
    fis.m_Title = getStringInBetween(s, sign3, sign4);
    
    DatePtr deadline = DateConverter::instance()->convert(deadline_str);
    
    if (deadline.get())
    {
        fis.m_Deadline = boost::gregorian::to_iso_string(*deadline);
        
        writeInputToManager(file_output, fis, now, count);
        count++;
    }
}



void
FetcherScholarshipPositions::fetch()
{
    const std::string now = "spgmail" + currentDateTime();
    std::size_t count = 0;
    
    std::ifstream file_input(m_FilenameHtmlScholarshipPositionsGmail.c_str());
    std::ofstream file_output(m_FilenameInputScholarshipPositionsGmail.c_str());
    
    if (!file_input.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameHtmlScholarshipPositionsGmail << "\" for reading!" << std::endl;
        return;
    }
    
    if (!file_output.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameInputScholarshipPositionsGmail << "\" for writing!" << std::endl;
        return;
    }
    
    std::string content_gmail((std::istreambuf_iterator<char>(file_input)), std::istreambuf_iterator<char>());
    
    HTML::ParserDom parser;
    tree<HTML::Node> dom = parser.parseTree(content_gmail);
    
    tree<HTML::Node>::iterator beg = dom.begin();
    tree<HTML::Node>::iterator end = dom.end();
    
    std::string ct = "";
    std::string link_title_str = "";
    std::string deadline_str = "";
    
    tree<HTML::Node>::iterator previous_bold_it = NULL;
    
    for (tree<HTML::Node>::iterator it = beg; it != end; ++it)
    {
        if (it->tagName() == "strong")
        {
            ct = it->content(content_gmail);
            
            // 20150908:
            // The link to the scholarship can be in the text content of this node or the previous node with tag <strong>.
            //
            if (ct.find("Provided by:") != std::string::npos)
            {
                link_title_str = it->content(content_gmail);
                if (link_title_str.find("href=\"") == std::string::npos) link_title_str = previous_bold_it->content(content_gmail);
                assert(link_title_str.find("href=\"") != std::string::npos);
            }
            if (ct.find("Application Deadline") != std::string::npos)
            {
                tree<HTML::Node>::iterator jt = it;
                
                // To deal with the following form:
                // <strong><span style="background: white">Application Deadline</span></strong>
                // <span style="background: white">&nbsp;22 September 2014</span><br />
                ++jt;
                ++jt;
                ++jt;
                deadline_str = jt->content(content_gmail);
                
                //
                // To deal with the following form:
                // <strong>Application Deadline</strong> 31 October 2014<br />
                //
                if (deadline_str == "")
                {
                    for (jt = it; jt != end; ++jt)
                    {
                        if (jt->tagName() == "br")
                        {
                            jt--;
                            deadline_str = jt->text();
                            break;
                        }
                    }
                }
                
                fetchOneScholarshipPosition(file_output, now, count,
                                            link_title_str, deadline_str);
            }
            previous_bold_it = it;
        }
    }
    
    DBGINFO("Fetched " << count << " scholarship items from ScholarshipPositions-Gmail!")
}
    
} // namespace findscholarships
