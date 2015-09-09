#include <cassert>
#include <iostream>
#include <fstream>

#include "utilities/ConfigurationBase.h"
#include "utilities/Logger.h"

ConfigurationBase*
ConfigurationBase::_instance = 0;
    
ConfigurationBase::ConfigurationBase()
{ }
    

ConfigurationBase*
ConfigurationBase::instance()
{
    if (_instance == 0)
    {
        _instance = new ConfigurationBase;
    }
    return _instance;
}
    
std::string
ConfigurationBase::readLine(const std::string& filename, const std::string& key)
{
    // configuration follows CSV format
    std::ifstream config_file(filename.c_str());
    if (config_file.is_open())
    {
        std::string line;
        while (config_file.good())
        {
            std::getline(config_file, line);
            std::size_t pos = line.find(key);
            if (pos != std::string::npos)
            {
                std::string value = line.substr(pos + key.length() + 1);
                config_file.close();
                return value;
            }
        }
        config_file.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot read configuration file: " << filename << "!")
    }
    
    return "ERROR";
}


void
ConfigurationBase::readConfig(const std::string &filename)
{
    
}