#include <iostream>

#include "Title.h"              // htmlgen
#include "utilities/Configuration.h"
#include "utilities/HelperFunctions.h"

namespace findscholarships {

Title::Title()
: m_Title("")
{ }



Title::Title(const std::string& t)
: m_Title(t)
{
    strTrim(m_Title);
}



Title::Title(const Title& other_title)
: m_Title(other_title.m_Title)
{
    strTrim(m_Title);
}



bool
Title::operator==(const Title& other_title) const
{
    return m_Title == other_title.m_Title;
}



Title::TitleClassification
Title::classification() const
{
    std::string tmp = m_Title;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
    
    if ((tmp.find("postdoc") != std::string::npos) ||
        (tmp.find("post-doc") != std::string::npos) ||
        (tmp.find("fellowship") != std::string::npos))
    {
        return PostDoc;
    }
    
    if ((tmp.find("phd") != std::string::npos)  ||
        (tmp.find("ph.d") != std::string::npos) ||
        (tmp.find("p.hd") != std::string::npos) ||
        (tmp.find("doctoral") != std::string::npos)
        )
    {
        return PhD;
    }
    
    if (tmp.find("undergraduate") != std::string::npos)
    {
        return UnderGrad;
    }
    
    if ((tmp.find("master") != std::string::npos)   ||
        (tmp.find("msc") != std::string::npos)      ||
        (tmp.find("graduate") != std::string::npos) ||
        (tmp.find("m.sc") != std::string::npos)     ||
        (tmp.find("mba") != std::string::npos))
    {
        return Master;
    }
    
    if (tmp.find("professor") != std::string::npos ||
        tmp.find("faculty position") != std::string::npos ||
        tmp.find("tenure") != std::string::npos)
    {
        return AcademicJob;
    }
    
    return Unclassified;
}



std::size_t
Title::classifiedIndex() const
{
    switch (classification())
    {
        case Title::UnderGrad:
            return IDX_UNDER_GRADUATE;
            break;
        case Title::Master:
            return IDX_MASTER;
            break;
        case Title::PhD:
            return IDX_PHD;
            break;
        case Title::PostDoc:
            return IDX_POSTDOC;
            break;
        case Title::AcademicJob:
            return IDX_ACADEMIC;
            break;
        case Title::Unclassified:
            return IDX_UNCLASSIFIED;
            break;
    }
    
    return 1000;
}


std::string
Title::strCategory() const
{
    const StringVec& categories = Configuration::instance()->categories();
    std::size_t index = classifiedIndex();
    
    return categories[index];
}


std::string
Title::getTitle() const
{
    return m_Title;
}



std::string
Title::getHtmlTitle() const
{
    std::string html_title = "<title>" + m_Title + "</title>";
    return html_title;
}



std::string
Title::getHeadLineTitle() const
{
    std::string headline_title = "<div><center><h2>" + m_Title + "</h2></center></div>";
    return headline_title;
}




std::string
Title::getTitleNoSpace() const
{
    std::string tmp = m_Title;
    
    killSpecialChar(tmp, ' ');
    killSpecialChar(tmp, ':');
    killSpecialChar(tmp, '/');
    killSpecialChar(tmp, ',');
    killSpecialChar(tmp, '\'');
    
    strReplace(tmp, "&#8217;", "");
    strReplace(tmp, "&#8211;", "");
    strReplace(tmp, "&#038;", "");
    strReplace(tmp, "&amp;", "");
    strReplace(tmp, "&rsquo;", "");

    return tmp;
}



std::string
Title::getFilename(const DatePtr deadline) const
{
    return ( strCategory() + "/" + boost::gregorian::to_iso_string(*deadline) + "-" + getTitleNoSpace() + ".html" );
}



std::string
Title::getFileLocation(const DatePtr deadline) const
{
    return ( Configuration::instance()->pathProductionRoot() + getFilename(deadline) );
}



std::string
Title::getHtmlLink(const DatePtr deadline) const
{
    return ( "<a href=\"" + getFilename(deadline) + "\">" + m_Title + "</a> <small>[Deadline: " + boost::gregorian::to_simple_string(*deadline) + "]</small>" );
}



std::string
Title::getSingleLineNotification(const DatePtr deadline) const
{
    return getNotification(deadline, ". ");
}



std::string
Title::getMultipleLineNotification(const DatePtr deadline) const
{
    return getNotification(deadline, "\n\n");
}



std::string
Title::getNotification(const DatePtr deadline,
                       const std::string &delim) const
{
    return (m_Title + delim + "Deadline: " + boost::gregorian::to_simple_string(*deadline) + delim + getLink(deadline));
}



std::string
Title::getLink(const DatePtr deadline) const
{
    return ( Configuration::instance()->rootDomain() + getFilename(deadline) );
}
    
} // namespace findscholarships
