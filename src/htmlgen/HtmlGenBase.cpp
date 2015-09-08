#include "HtmlGenBase.h"        // htmlgen
#include "Configuration.h"      // utilities
#include "ConstantStrings.h"    // utilities
#include "Logger.h"             // utilities

using namespace htmlcxx;

namespace findscholarships {

void
HtmlGenBase::process(FetchedInfoScholarship &fis)
{
    std::string filecontent = "";
    
    std::string delimeter = "";
    initDelimeter(delimeter);
    readFileAndParse(fis.m_Filename, filecontent, delimeter);
    
    generate(fis, filecontent);
}



const HtmlResult&
HtmlGenBase::getHtmlResult()
{
    return m_HtmlResult;
}



void
HtmlGenBase::readFileAndParse(const std::string& filename,
                              std::string& filecontent,
                              const std::string& delimeter)
{
    std::ifstream inputfile(filename.c_str());
    std::string line;
    
    if (inputfile.is_open())
    {
        while (inputfile.good())
        {
            std::getline(inputfile, line);
            filecontent = filecontent + delimeter + line;
        }
        
        HTML::ParserDom parser;
        m_Dom = parser.parseTree(filecontent);
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot open file \"" << filename << "\"!")
    }
}



void
HtmlGenBase::dressUp(std::string &html_code,
                     const Title &title)
{
    html_code = Configuration::instance()->headerPart1() + "\n" +
    title.getHtmlTitle() + "\n" +
    Configuration::instance()->headerPart2() + "\n" +
    Configuration::instance()->bodyPart1() + "\n" +
    title.getHeadLineTitle() + "\n" +
    Configuration::instance()->bodyPart2() + "\n" +
    html_code + "\n" +
    Configuration::instance()->bodyPart3();
}



void
HtmlGenBase::cleanTag(std::string &node_content,
                      const std::string &tag_sign)
{
    std::string start_tag_sign = "<a title=";
    std::string start_tag_sign2 = "<a href=";
    std::string start_tag_sign3 = "<atitle=";
    std::string start_tag_sign4 = "<ahref=";
    std::string start_text_sign = "\">";
    std::string end_tag_sign = "</a>";
    
    std::size_t start_text_length = start_text_sign.length();
    std::size_t end_tag_length = end_tag_sign.length();
    
    std::size_t tag_pos = node_content.find(tag_sign);
    while (tag_pos != std::string::npos)
    {
        std::size_t start_tag = node_content.rfind(start_tag_sign, tag_pos);
        std::size_t start_text = node_content.find(start_text_sign, tag_pos);
        std::size_t end_tag = node_content.find(end_tag_sign, tag_pos);
        
        if (start_tag == std::string::npos)
        {
            start_tag = node_content.rfind(start_tag_sign2, tag_pos);
        }
        
        if (start_tag == std::string::npos)
        {
            start_tag = node_content.rfind(start_tag_sign3, tag_pos);
        }
        
        if (start_tag == std::string::npos)
        {
            start_tag = node_content.rfind(start_tag_sign4, tag_pos);
        }
        
        if (start_tag == std::string::npos)
        {
            DBGDEBUG(node_content << std::endl
                     << "tag_sign = " << tag_sign << std::endl
                     << "tag_pos = " << tag_pos << std::endl
                     << "start_tag = " << start_tag << std::endl
                     << "start_text = " << start_text << std::endl
                     << "end_tag = " << end_tag << std::endl)
        }
        
        assert (start_tag != std::string::npos);
        assert (start_text != std::string::npos);
        assert (end_tag != std::string::npos);
        
        std::string text = node_content.substr(start_text + start_text_length, end_tag - start_text - start_text_length);
        node_content.replace(start_tag, end_tag + end_tag_length - start_tag, text);
        
        tag_pos = node_content.find(tag_sign);
    }
}



HtmlGenBase::~HtmlGenBase()
{ }
    
} // namespace findscholarships

