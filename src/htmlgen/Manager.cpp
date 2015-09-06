#include <fstream>

#include "HtmlGenDbworld.h"             // htmlgen
#include "HtmlGenScholarshipPosition.h" // htmlgen
#include "HtmlGenScholarshipsLinks.h"   // htmlgen
#include "Manager.h"                    // htmlgen
#include "ConstantStrings.h"            // utilities
#include "Logger.h"                     // utilities


bool
Manager::getInput(std::ifstream &file_input,
                  FetchedInfoScholarship &fis)
{
    std::string line;
    std::getline(file_input, line);
    
    if (line == "") return false;
    assert (line.compare(ConstantStrings::instance()->PrefixBegin) == 0);
    
    std::getline(file_input, line);
    if (line == "") return false;
    
    while (line.compare(ConstantStrings::instance()->PrefixEnd) != 0)
    {
        bool passed = false;
        if (line.find(ConstantStrings::instance()->PrefixDeadline) != std::string::npos)
        {
            fis.m_Deadline = line.substr(ConstantStrings::instance()->PrefixDeadline.length());
            passed = true;
        }
        
        if (!passed && line.find(ConstantStrings::instance()->PrefixTitle) != std::string::npos)
        {
            fis.m_Title = line.substr(ConstantStrings::instance()->PrefixTitle.length());
            passed = true;
        }
        
        if (!passed && line.find(ConstantStrings::instance()->PrefixFilename) != std::string::npos)
        {
            fis.m_Filename = line.substr(ConstantStrings::instance()->PrefixFilename.length());
            passed = true;
        }
        
        if (!passed && line.find(ConstantStrings::instance()->PrefixURL) != std::string::npos)
        {
            fis.m_URL = line.substr(ConstantStrings::instance()->PrefixURL.length());
            passed = true;
        }
        
        if (!passed && line.find(ConstantStrings::instance()->PrefixWebpage) != std::string::npos)
        {
            fis.m_Webpage = line.substr(ConstantStrings::instance()->PrefixWebpage.length());
            passed = true;
        }
        
        std::getline(file_input, line);
    }
    
    return true;
}



void
Manager::processBatch(const std::string &file_url_collection,
                      Database &db)
{
    // read from file_url_collection and call processSingle for each pair <filename,url>
    std::ifstream file_input(file_url_collection.c_str());
    
    if (file_input.is_open())
    {
        while (file_input.good())
        {
            FetchedInfoScholarship fis;
            
            if (!getInput(file_input, fis)) break;
            
            processSingle(fis, db);
        }
        
        db.showDatabase();
        db.storeDatabase();
        db.writeToCategoryFile();
        db.writeNotification(true /* singleLine */);
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot open file \"" << file_url_collection << "\"!")
    }
    
}



void
Manager::processSingle(FetchedInfoScholarship &fis,
                       Database &db)
{
    HtmlGenBase* generator = getGenerator(fis.m_URL);
    assert (generator != NULL);
    
    generator->process(fis);
    
    const HtmlResult& result = generator->getHtmlResult();
    
    if (result.getDeadline().get() != NULL)
    {
        // write to files
        const std::string& full_html_code = result.getFullHtmlCode();
        std::string full_path = result.getTitle().getFileLocation(result.getDeadline());
        
        std::ofstream html_file(full_path.c_str());
        if (html_file.is_open())
        {
            html_file << full_html_code;
            html_file.close();
            
            // insert to database
            const Title& title = result.getTitle();
            const StorageVec st = db.getStorages();
            std::size_t index = title.classifiedIndex();
            StoragePtr s = st[index];
            
            db.insert(s, result.getDeadline(), fis.m_Title, fis.m_URL, true /* is_new */);
            //db.showDatabase();
        }
        else
        {
            DBGERR(__FUNCTION__ << ": Cannot write to file \"" << full_path << "\"!")
        }
    }
    
    // clean up
    delete generator;
    generator = NULL;
}



HtmlGenBase*
Manager::getGenerator(const std::string &url)
{
    if (url.find("www.scholarships-links.com") != std::string::npos)
    {
        return (new HtmlGenScholarshipsLinks);
    }
    
    if (url.find("scholarship-positions.com") != std::string::npos)
    {
        return (new HtmlGenScholarshipPosition);
    }
    
    if (url.find("www.cs.wisc.edu") != std::string::npos)
    {
        return (new HtmlGenDbworld);
    }
    
    return NULL;
}
