#include "init/InitWillhabentracker.hpp"
#include "utilities/ConfigurationWillhabentracker.h"
#include "utilities/Logger.h"


namespace willhabentracker {
    
void
InitWillhabentracker::init()
{
    DBGINIT(std::cerr, Logger::INFO | Logger::ERRO | Logger::VERB | Logger::DEBU)
    
    std::string config_filename = "/Users/minhdt/Documents/softwares/willhabentracker/config.cfg";
    
    DBGINFO("Read config")
    
    ConfigurationWillhabentracker* config = ConfigurationWillhabentracker::instance();
    config->readConfig(config_filename);
    
    if (!exists(config->pathDatabase())) createDir(config->pathDatabase());
}
    
} // namespace willhabentracker
