#ifndef ___HTML_GEN_BASE_HPP___
#define ___HTML_GEN_BASE_HPP___

#include "FetchedInfoScholarship.h" // fetch
#include "HtmlResult.h"             // htmlgen
#include "ParserDom.h"              // html

using namespace htmlcxx;

class HtmlGenBase
{
public:
    void
    process(FetchedInfoScholarship &fis);
    
    const HtmlResult&
    getHtmlResult();
    
    virtual
    ~HtmlGenBase();
    
protected:
    void
    readFileAndParse(const std::string &filename,
                     std::string &filecontent,
                     const std::string &delimeter);
    
    void
    dressUp(std::string &html_code,
            const Title &title);
    
    void
    cleanTag(std::string &node_content,
             const std::string &tag_sign);
    
    virtual void
    generate(FetchedInfoScholarship &fis,
             const std::string &filecontent) = 0;
    
    virtual void
    initDelimeter(std::string &delimeter)
    {
        delimeter = "";
    }
    
protected:
    tree<HTML::Node> m_Dom;
    HtmlResult m_HtmlResult;
};


#endif // ___HTML_GEN_BASE_HPP___
