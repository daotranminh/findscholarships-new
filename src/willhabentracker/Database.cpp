#include <fstream>

#include "willhabentracker/Database.hpp"
#include "utilities/ConfigurationWillhabentracker.h"
#include "utilities/Logger.h"

namespace willhabentracker {

Database::Database(const std::string &name)
: m_Name(name)
{
    if (m_Name != "") loadDatabase();
    
}



void
Database::setDatabaseName(const std::string &name)
{
    m_Name = name;
}



void
Database::add(const DataItemPtr &di)
{
    m_DataItems.push_back(di);
}



void
Database::writeDatabase()
{
    ConfigurationWillhabentracker *config = ConfigurationWillhabentracker::instance();
    std::string filename = config->pathDatabase() + m_Name + ".txt";
    std::ofstream file_db(filename.c_str());
    
    if (file_db.is_open())
    {
        for (DataItemVec::const_iterator it = m_DataItems.begin(); it != m_DataItems.end(); ++it)
        {
            const DataItemPtr &di = *it;
            file_db << config->beginURL() << std::endl
            << di->m_URL << std::endl
            << config->endURL() << std::endl
            << config->beginTitle() << std::endl
            << di->m_Title << std::endl
            << config->endTitle() << std::endl
            << config->beginDesc() << std::endl
            << di->m_Description << std::endl
            << config->endDesc() << std::endl
            << config->beginPrice() << std::endl
            << di->m_Price << std::endl
            << config->endPrice() << std::endl;
        }
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot write to database file \"" << m_Name << "\"!")
    }
    
    file_db.close();
}



bool
Database::exists(const DataItemPtr &di)
{
    for (DataItemVec::const_iterator it = m_DataItems.begin(); it != m_DataItems.end(); ++it)
    {
        const DataItemPtr &mydi = *it;
        if (*mydi == *di) return true;
    }
    
    return false;
}



void
Database::compare(const DatabasePtr &db)
{
    for (DataItemVec::const_iterator it = m_DataItems.begin(); it != m_DataItems.end(); ++it)
    {
        const DataItemPtr &di = *it;
        if (!db->exists(di)) di->m_IsNew = true;
    }
}



void
Database::show(bool showNew)
{
    for (DataItemVec::const_iterator it = m_DataItems.begin(); it != m_DataItems.end(); ++it)
    {
        const DataItemPtr &di = *it;
        if (showNew && di->m_IsNew == false) continue;
        
        
        std::cout << *di << std::endl
        << "------------------------------------" << std::endl;
    }
}


std::string
Database::readContent(std::ifstream &file_input,
                      const std::string &beg,
                      const std::string &end)
{
    std::string content = "";
    std::string line;
    
    while (file_input.good() && line != beg)
        std::getline(file_input, line);
    
    std::getline(file_input, line);
    while (file_input.good() && line != end)
    {
        content = content + line + "\n";
        std::getline(file_input, line);
    }
    
    // remove the last \n
    content = content.substr(0, content.length() - 1);
    
    return content;
}


void
Database::loadDatabase()
{
    std::string filename = ConfigurationWillhabentracker::instance()->pathDatabase() + m_Name + ".txt";
    std::ifstream file_db(filename.c_str());
    
    if (file_db.is_open())
    {
        ConfigurationWillhabentracker *config = ConfigurationWillhabentracker::instance();
        while (file_db.good())
        {
            std::string url = readContent(file_db, config->beginURL(), config->endURL());
            std::string title = readContent(file_db, config->beginTitle(), config->endTitle());
            std::string desc = readContent(file_db, config->beginDesc(), config->endDesc());
            std::string str_price = readContent(file_db, config->beginPrice(), config->endPrice());
            float price = ::atof(str_price.c_str());
            
            DataItemPtr di = DataItemPtr(new DataItem(url, title, desc, price));
            m_DataItems.push_back(di);
        }
    }
}
    
} // namespace willhabentracker
