#include <assert.h>
#include <iostream>
#include <fstream>

#include "utilities/Configuration.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"
#include "htmlgen/DataBase.h"

namespace findscholarships {

typedef Storage::const_iterator StorageConstIterator;
typedef std::pair<StorageConstIterator, StorageConstIterator> StorageConstIteratorPair;

// Database text format:
//
// 3*n lines for n scholarships
//
// Scholarship[i]:
//
// Line 3*i-2: deadline of the form yyyymmdd
// Line 3*i-1: title in string
// Line 3*i:   original link from which the scholarship was crawled


Database::Database()
{
    for (std::size_t i = 0; i < TOTAL_STORAGES; ++i)
    {
        StoragePtr storage(new Storage);
        m_Storages.push_back(storage);
    }
    
    // Initialize lower_bound to today+1month
    // as we only show scholarships having deadline in more than a month from the posting date.
    // Otherwise, it will be useless for the reader.
    
    Date_t today = boost::gregorian::day_clock::local_day();
    boost::gregorian::months one_month(1);
    Date_t in_1_month = today + one_month;
    m_LowerBound = std::make_shared<Date_t>(in_1_month);
    //m_LowerBound = boost::shared_ptr<Date_t>(new Date_t(in_1_month));
}



const StorageVec&
Database::getStorages() const
{
    return m_Storages;
}



void
Database::loadDatabase()
{
    const StringVec& path_storages = Configuration::instance()->pathStorages();
    
    // we don't need to load the homepage's database,
    // as whenever we load a category's database, the data entry
    // is also inserted into the homepage's database.
    for (std::size_t i = 0; i < TOTAL_STORAGES-1; ++i)
    {
        loadDatabase(path_storages[i], m_Storages[i]);
    }
}



void
Database::loadDatabase(const std::string& filename, StoragePtr to_load)
{
    std::ifstream inp(filename.c_str());
    
    if (inp.is_open())
    {
        std::string line;
        while (inp.good())
        {
            std::getline(inp, line);
            if (line == "") break;
            
            Date_t deadline = boost::gregorian::from_simple_string(line);
            //DatePtr deadline_ptr = std::make_shared<Date_t>(deadline);
            DatePtr deadline_ptr(new Date_t(deadline));
            
            std::getline(inp, line);
            Title title(line);
            
            std::getline(inp, line);
            
            insert(to_load, deadline_ptr, title, line);
        }
        
        inp.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Database file \"" << filename << "\" does not exists!")
    }
}



void
Database::storeDatabase()
{
    const StringVec& path_storages = Configuration::instance()->pathStorages();
    for (std::size_t i = 0; i < TOTAL_STORAGES; ++i)
    {
        storeDatabase(path_storages[i], m_Storages[i]);
    }
}



void
Database::storeDatabase(const std::string& filename, StoragePtr to_store)
{
    std::ofstream out(filename.c_str());
    
    if (out.is_open())
    {
        for (Storage::const_iterator it = to_store->begin(); it != to_store->end(); ++it)
        {
            DatePtr deadline = it->first;
            const DataEntry& data_entry = it->second;
            
            out << boost::gregorian::to_iso_extended_string(*deadline) << std::endl;
            out << data_entry.getTitle().getTitle() << std::endl;
            out << data_entry.getOrigLink() << std::endl;
        }
        
        out.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot open file \"" << filename << "\" to store database on disk!")
    }
}



void
Database::insert(std::size_t storage_index,
                 DatePtr deadline,
                 const Title& title,
                 const std::string& orig_link,
                 bool is_new /* = false */)
{
    assert (storage_index < TOTAL_STORAGES);
    StoragePtr to_load = m_Storages[storage_index];
    insert(to_load, deadline, title, orig_link, is_new);
}



void
Database::insert(StoragePtr to_load,
                 DatePtr deadline,
                 const Title& title,
                 const std::string& orig_link,
                 bool is_new /* = false */)
{
    DateCompare dc;
    
    if (*deadline < *m_LowerBound)
    {
        if (!is_new)
        {
            // write to expired list
            const std::string& expired_filename = Configuration::instance()->pathExpired();
            std::ofstream expired_file;
            expired_file.open(expired_filename.c_str(), std::ios::app);
            //	  expired_file << getFileLocation(title, deadline) << std::endl;
            expired_file.close();
        }
    }
    else
    {
        insertWithCheck(to_load, deadline, title, orig_link, is_new);
        
        StoragePtr homepage = m_Storages[IDX_HOMEPAGE];
        insertWithCheck(homepage, deadline, title, orig_link, is_new);
    }
}



void
Database::insertWithCheck(StoragePtr to_load,
                          DatePtr deadline,
                          const Title& title,
                          const std::string& orig_link,
                          bool is_new /* = false */)
{
    StorageConstIteratorPair p = to_load->equal_range(deadline);
    StorageConstIterator beg = p.first;
    StorageConstIterator end = p.second;
    
    if (beg != end)
    {
        for (StorageConstIterator it = beg; it != end; ++it)
        {
            DataEntry data = it->second;
            const Title& t = data.getTitle();
            
            if (title == t)
            {
                // the same scholarship is already in, no need to insert
                return;
            }
        }
    }
    
    // now insert
    DataEntry data_entry(title, orig_link, is_new);
    to_load->insert(std::pair<DatePtr, DataEntry>(deadline, data_entry));
}




void
Database::writeToCategoryFile()
{
    const StringVec& category_titles = Configuration::instance()->categoryTitles();
    const StringVec& categories = Configuration::instance()->categories();
    
    for (std::size_t i = 0; i < TOTAL_STORAGES; ++i)
    {
        writeToCategoryFile(Configuration::instance()->pathProductionRoot() + categories[i] + ".html", category_titles[i], m_Storages[i]);
    }
}




void
Database::writeToCategoryFile(const std::string& filename,
                              const std::string& title,
                              StoragePtr to_write)
{
    std::ofstream out(filename.c_str());
    
    if (out.is_open())
    {
        out << Configuration::instance()->categoryPart1() << std::endl;
        out << "<title>Findscholarships: " << title << "</title>" << std::endl;
        
        out << Configuration::instance()->categoryPart2() << std::endl;
        out << "<div><center><h2>" << title << "</h2></center></div>" << std::endl;
        out << Configuration::instance()->categoryPart3() << std::endl;
        
        std::string list_new = "";
        std::string list_old = "";
        
        for (Storage::const_iterator it = to_write->begin(); it != to_write->end(); ++it)
        {
            const DatePtr deadline = it->first;
            const DataEntry& data = it->second;
            const Title& title = data.getTitle();
            
            if (data.isNew())
            {
                list_new = "<p>" + list_new + title.getHtmlLink(deadline) + "<img src=\"images/new_icon.gif\"></p>\n\n";
            }
            else
            {
                list_old = "<p>" + list_old + title.getHtmlLink(deadline) + "</p>\n\n";
            }
        }
        
        out << list_new << list_old << std::endl;
        out << Configuration::instance()->categoryPart4() << std::endl;
        out.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot write to category file \"" << filename << "\"!")
    }
}





void
Database::writeNotification(bool single_line)
{
    StoragePtr homepage = m_Storages[IDX_HOMEPAGE];
    
    std::string filename = Configuration::instance()->pathDatabase() + currentDateTime();
    if (single_line)
    {
        filename = filename + ".single";
    }
    else
    {
        filename = filename + ".multiple";
    }
    
    std::ofstream file_notification(filename.c_str());
    if (file_notification.is_open())
    {
        Storage::const_iterator beg = homepage->begin();
        Storage::const_iterator end = homepage->end();
        end--;
        for (Storage::const_iterator it = end; it != beg; it--)
        {
            DatePtr deadline = it->first;
            const DataEntry& data = it->second;
            if (data.isNew())
            {
                if (single_line)
                {
                    file_notification << data.getTitle().getSingleLineNotification(deadline) << std::endl << std::endl;
                }
                else
                {
                    file_notification << data.getTitle().getMultipleLineNotification(deadline) << std::endl << std::endl;
                }
            }
        }
        
        DatePtr deadline = beg->first;
        const DataEntry& data = beg->second;
        if (data.isNew())
        {
            if (single_line)
            {
                file_notification << data.getTitle().getSingleLineNotification(deadline) << std::endl << std::endl;
            }
            else 
            {
                file_notification << data.getTitle().getMultipleLineNotification(deadline) << std::endl << std::endl;
            }
        }		
    }
    else 
    {
        DBGERR(__FUNCTION__ << ": Cannot open file \"" << filename << "\" for writing!")
    }
}




void
Database::showDatabase()
{
    for (std::size_t i = 0; i < TOTAL_STORAGES; ++i)
    {
        std::cout << "Storage[" << i << "]:" << std::endl;
        showStorage(m_Storages[i]);
    }
}



void
Database::showStorage(StoragePtr to_show)
{
    std::cout << "Size = " << to_show->size() << std::endl;
    for (Storage::const_iterator it = to_show->begin(); it != to_show->end(); ++it)
    {
        const DatePtr deadline = it->first;
        const DataEntry& data = it->second;
        
        std::cout << boost::gregorian::to_iso_extended_string(*deadline) << " " << data.getTitle().getTitleNoSpace() << std::endl;
    }
}
    
} // namespace findscholarships

