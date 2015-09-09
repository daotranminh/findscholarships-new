#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <boost/program_options.hpp>

#include "init/Init.h"
#include "utilities/Configuration.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"
#include "utilities/ProgramOptions.h"
#include "htmlgen/Database.h"
#include "htmlgen/HtmlGenBase.h"
#include "htmlgen/Manager.h"
#include "htmlgen/Title.h"

using namespace findscholarships;

int
main (int argc, const char *argv[])
{
    //std::string from = "all";
    std::string from = "slgmail";
    
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
    
    DBGINFO("Initializing...")
    findscholarships::Init init;
    init.init();
    
    DBGINFO("Load db")
    
    Database db;
    db.loadDatabase();
    
    DBGINFO("Process batch")
    Manager man;
    
    if (from == "manual")
    {
        DBGINFO("From manual input...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputFetched(), db);
    }
    else if (from == "dbworld")
    {
        DBGINFO("From dbworld...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputDbworld(), db);
    }
    else if (from == "spgmail")
    {
        DBGINFO("From ScholarshipPositions Gmail...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputScholarshipPositionsGmail(), db);
    }
    else if (from == "slgmail")
    {
        DBGINFO("From ScholarshipLinks Gmail...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputScholarshipLinksGmail(), db);
    }
    else
    {
        assert (from == "all");
        // DBGINFO("From manual input...")
        // man.processBatch(config->pathTemp() + config->inputFetched(), db);
        DBGINFO("From dbworld...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputDbworld(), db);
        DBGINFO("From ScholarshipPositions Gmail...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputScholarshipPositionsGmail(), db);
        DBGINFO("From ScholarshipLinks Gmail...")
        man.processBatch(Configuration::instance()->pathTemp() + Configuration::instance()->inputScholarshipLinksGmail(), db);
    }
    
    DBGINFO("Finish!")
    
    return 0;
}
