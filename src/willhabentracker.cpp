#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include <boost/program_options.hpp>

#include "willhabentracker/Manager.hpp"
#include "utilities/ConfigurationWillhabentracker.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"

using namespace willhabentracker;

int main(int argc, const char *argv[])
{
    DBGINIT(std::cerr, Logger::INFO | Logger::ERRO | Logger::VERB | Logger::DEBU)
    
    std::string config_filename = "/Users/minhdt/Documents/softwares/webtracker-storage/config.cfg";
    
    DBGINFO("Read config")
    
    ConfigurationWillhabentracker* config = ConfigurationWillhabentracker::instance();
    config->readConfig(config_filename);
    
    Manager man;
    man.process();
    
    // const TrackedSiteVec &ts = config->trackedSites();
    // std::copy(ts.begin(), ts.end(), std::ostream_iterator<TrackedSite>(std::cout, "\n\n"));
}
