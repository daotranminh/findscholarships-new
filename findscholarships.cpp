#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include "Init.h"               // init
#include "Configuration.h"      // utilities
#include "HelperFunctions.h"    // utilities
#include "Logger.h"             // utilities
#include "ProgramOptions.h"     // utilities
#include "Database.h"           // htmlgen
#include "HtmlGenBase.h"        // htmlgen
#include "Manager.h"            // htmlgen
#include "Title.h"              // htmlgen


int
main (int argc, const char *argv[])
{
    //std::string from = "all";
    std::string from = "dbworld";
    
    /*const char *help_description = "\nUsage: fetch [--from=all/manual/dbworld/spgmail]\n";
    boost::program_options::options_description desc(help_description);
    
    desc.add_options()
    (HELP, "produce help and usage message")
    (FROM, boost::program_options::value<std::string>(&from)->default_value("all"), "choose fetching source")
    ;
    
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);
    
    if (vm.count(HELP))
    {
        std::cerr << desc << std::endl;
        exit(1);
    }*/
    
    DBGINIT(std::cerr, Logger::INFO | Logger::ERRO | Logger::VERB | Logger::DEBU)
    
    std::string config_filename = "/Users/minhdt/Documents/softwares/findscholarships-website/config.cfg";
    
    DBGINFO("Read config")
    
    Configuration* config = Configuration::instance();
    config->readConfig(config_filename);
    
    DBGINFO("Load db")
    
    Database db;
    db.loadDatabase();
    
    DBGINFO("Process batch")
    Manager man;
    
    if (from == "manual")
    {
        DBGINFO("From manual input...")
        man.processBatch(config->pathTemp() + config->inputFetched(), db);
    }
    else if (from == "dbworld")
    {
        DBGINFO("From dbworld...")
        man.processBatch(config->pathTemp() + config->inputDbworld(), db);
    }
    else if (from == "spgmail")
    {
        DBGINFO("From ScholarshipPositions Gmail...")
        man.processBatch(config->pathTemp() + config->inputScholarshipPositionsGmail(), db);
    }
    else if (from == "slgmail")
    {
        DBGINFO("From ScholarshipLinks Gmail...")
        man.processBatch(config->pathTemp() + config->inputScholarshipLinksGmail(), db);
    }
    else
    {
        assert (from == "all");
        // DBGINFO("From manual input...")
        // man.processBatch(config->pathTemp() + config->inputFetched(), db);
        DBGINFO("From dbworld...")
        man.processBatch(config->pathTemp() + config->inputDbworld(), db);
        DBGINFO("From ScholarshipPositions Gmail...")
        man.processBatch(config->pathTemp() + config->inputScholarshipPositionsGmail(), db);
        DBGINFO("From ScholarshipLinks Gmail...")
        man.processBatch(config->pathTemp() + config->inputScholarshipLinksGmail(), db);
    }
    
    DBGINFO("Finish!")
    
    return 0;
}
