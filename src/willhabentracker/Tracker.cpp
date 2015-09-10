#include "willhabentracker/Tracker.hpp"
#include "utilities/ConfigurationWillhabentracker.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"

using namespace htmlcxx;

namespace willhabentracker {

Tracker::Tracker(const std::string &url)
: m_URL(url)
{ }



std::string
Tracker::fetch()
{
    DBGDEBUG("Fetching from " << m_URL)
    
    std::string ret = "";
    
    m_Curl = curl_easy_init();
    
    assert (m_Curl);
    
    std::ostringstream stream;
    
    curl_easy_setopt(m_Curl, CURLOPT_URL, m_URL.c_str());
    curl_easy_setopt(m_Curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, &stream);
    
    m_Res = curl_easy_perform(m_Curl);
    
    if (m_Res != CURLE_OK)
    {
        DBGDEBUG("FAILED!")
    }
    else
    {
        DBGDEBUG("SUCCEEDED.")
        ret = stream.str();
    }
    
    return ret;
}


std::size_t
writeData(char *ptr,
          std::size_t size,
          std::size_t nmemb,
          void *userdata)
{
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}


DataItemPtr
Tracker::getOneDataItem(const std::string &content,
                        tree<HTML::Node>::iterator &it,
                        bool gratis)
{
    bool link_read = false;
    std::string url = "";
    std::string title = "";
    std::string str_price = "";
    float price = 0;
    std::string desc = "";
    
    while (it->text() != "<p class=\"dealer\">")
    {
        ++it;
        
        // get url and title
        if (it->tagName() == "a" && !link_read)
        {
            url = it->text();
            url = getStringInBetween(url, "<a href=\"", "\" >");
            url = "http://www.willhaben.at" + url;
            
            title = it->content(content);
            strReplace(title, "\n", "");
            strTrim(title);
            
            link_read = true;
        }
        
        // get price
        if (it->tagName() == "p" && it->text().find("class=\"price\"") != std::string::npos)
        {
            if (!gratis)
            {
                while (it->tagName() != "span") ++it;
                ++it;
                ++it;
                str_price = it->text();
                strReplace(str_price, "\n", "");
                strTrim(str_price);
                price = ::atof(str_price.c_str());
            }
        }
        else
        {
            // zu verschenken vs verschenkt
            // for now price := 0 in this case.
        }
        
        // get description
        if (it->tagName() == "p" && it->text().find("class=\"description\"") != std::string::npos)
        {
            desc = it->content(content);
            desc = desc.substr(1);
            desc = desc.substr(1, desc.find("\n")-1);
            strTrim(desc);
        }
    }
    
    DataItemPtr di = DataItemPtr(new DataItem(url, title, desc, price));
    
    return di;
}



bool
Tracker::inIgnoreList(const std::string &url)
{
    const std::vector<std::string> & ignoreList = ConfigurationWillhabentracker::instance()->ignoreList();
    
    for (std::vector<std::string>::const_iterator it = ignoreList.begin(); it != ignoreList.end(); ++it)
    {
        if (url.find(*it) != std::string::npos) return true;
    }
    
    return false;
}



DatabasePtr
Tracker::track(bool gratis)
{
    DatabasePtr db = DatabasePtr(new Database);
    
    std::string content = fetch();
    
    HTML::ParserDom parser;
    tree<HTML::Node> dom = parser.parseTree(content);
    
    for (tree<HTML::Node>::iterator it = dom.begin(); it != dom.end(); ++it)
    {
        if (it->tagName() == "li" && it->text().find("clearfix") != std::string::npos)
        {
            // ToDo: check for ignore list
            
            DataItemPtr di = getOneDataItem(content, it, gratis);
            if (!inIgnoreList(di->m_URL))
                db->add(di);
        }
    }
    
    return db;
}

} // namespace willhabentracker