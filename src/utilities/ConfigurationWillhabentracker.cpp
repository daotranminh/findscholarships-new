#include <cassert>
#include <iostream>
#include <fstream>

#include "utilities/ConfigurationWillhabentracker.h"
#include "utilities/Logger.h"

namespace willhabentracker {

ConfigurationWillhabentracker*
ConfigurationWillhabentracker::_instance = 0;
    

ConfigurationWillhabentracker::ConfigurationWillhabentracker()
: m_PathRoot("")
{ }



ConfigurationWillhabentracker*
ConfigurationWillhabentracker::instance()
{
    if (_instance == 0)
    {
        _instance = new ConfigurationWillhabentracker;
    }
    return _instance;
}



void
ConfigurationWillhabentracker::readDestination(const std::string &filename)
{
    std::ifstream config_file(filename.c_str());
    if (config_file.is_open())
    {
        std::string line;
        while (config_file.good())
        {
            std::getline(config_file, line);
            std::size_t pos = line.find("URL");
            if (pos == 0)
            {
                std::string link = line.substr(pos + 4); // 4 == length("URL") + 1
                std::getline(config_file, line);
                pos = line.find("PREFIX");
                assert(pos != std::string::npos);
                std::string prefix = line.substr(pos + 7); // 7 == length("PREFIX") + 1
                TrackedSite ts(link, prefix);
                m_TrackedSites.push_back(ts);
            }
        }
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot read configuration file: " << filename << "!")
    }
}



void
ConfigurationWillhabentracker::readIgnoreList(const std::string &filename)
{
    std::ifstream config_file(filename.c_str());
    if (config_file.is_open())
    {
        std::string line;
        while (config_file.good())
        {
            std::getline(config_file, line);
            std::size_t pos = line.find("IGNORE");
            if (pos != std::string::npos)
            {
                std::string ignore = line.substr(pos + 7); // 7 == length("IGNORE") + 1
                m_IgnoreList.push_back(ignore);
            }
        }
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot read configuration file: " << filename << "!")
    }
}


void
ConfigurationWillhabentracker::readConfig(const std::string& filename)
{
    m_PathRoot     = readLine(filename, "PATH_ROOT");
    m_PathDatabase = m_PathRoot + readLine(filename, "DIR_DATABASE");
    m_BeginURL     = readLine(filename, "BEGINURL");
    m_EndURL       = readLine(filename, "ENDURL");
    m_BeginTitle   = readLine(filename, "BEGINTITLE");
    m_EndTitle     = readLine(filename, "ENDTITLE");
    m_BeginDesc    = readLine(filename, "BEGINDESC");
    m_EndDesc      = readLine(filename, "ENDDESC");
    m_BeginPrice   = readLine(filename, "BEGINPRICE");
    m_EndPrice     = readLine(filename, "ENDPRICE");
    
    readDestination(filename);
    readIgnoreList(filename);
}
    
} // namespace willhabentracker
