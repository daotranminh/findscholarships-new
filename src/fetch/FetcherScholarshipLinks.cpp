#include <streambuf>

#include "fetch/FetcherScholarshipLinks.h"
#include "utilities/ConstantStrings.h"
#include "utilities/DateConverter.h"
#include "utilities/DateType.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"

namespace findscholarships {

FetcherScholarshipLinks::FetcherScholarshipLinks(const std::string &path,
                                                 const std::string &pathDatabase,
                                                 const std::string &filename_html_scholarship_links_gmail,
                                                 const std::string &filename_input_scholarship_links_gmail)
: FetcherBase(path, pathDatabase),
m_FilenameHtmlScholarshipLinksGmail(m_Path + filename_html_scholarship_links_gmail),
m_FilenameInputScholarshipLinksGmail(m_Path + filename_input_scholarship_links_gmail)
{ }



FetcherScholarshipLinks::~FetcherScholarshipLinks()
{ }



void
FetcherScholarshipLinks::fetch()
{
    const std::string now = "slgmail" + currentDateTime();
    std::size_t count = 0;
    
    std::ifstream file_input(m_FilenameHtmlScholarshipLinksGmail.c_str());
    std::ofstream file_output(m_FilenameInputScholarshipLinksGmail.c_str());
    
    if (!file_input.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameHtmlScholarshipLinksGmail << "\" for reading!" << std::endl;
        return;
    }
    
    if (!file_output.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameInputScholarshipLinksGmail << "\" for writing!" << std::endl;
        return;
    }
    
    std::string content_gmail((std::istreambuf_iterator<char>(file_input)), std::istreambuf_iterator<char>());
    strReplace(content_gmail, "=\n", "");
    
    HTML::ParserDom parser;
    tree<HTML::Node> dom = parser.parseTree(content_gmail);
    
    tree<HTML::Node>::iterator beg = dom.begin();
    tree<HTML::Node>::iterator end = dom.end();
    
    for (tree<HTML::Node>::iterator it = beg; it != end; ++it)
    {
        if (it->tagName() == "a")
        {
            std::string link = it->text();
            if (link.find("http://www.scholarships-links.com/viewdetail/") != std::string::npos)
            {
                FetchedInfoScholarship fis;
                fis.m_URL = getStringInBetween(link, "<a href=3D\"", "\">");
                writeInputToManager(file_output, fis, now, count);
                count++;
            }
        }
    }
    
    DBGINFO("Fetched " << count << " scholarship items from ScholarshipLinks-Gmail!")
}
    
} // namespace findscholarships
