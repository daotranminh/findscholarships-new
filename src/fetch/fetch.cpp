#include <string>

#include <boost/program_options.hpp>

#include "init/InitFindscholarships.hpp"
#include "fetch/FetcherDbworld.h"
#include "fetch/FetcherScholarshipLinks.h"
#include "fetch/FetcherScholarshipPositions.h"
#include "utilities/ConfigurationFindscholarships.h"
#include "utilities/Logger.h"
#include "utilities/ProgramOptions.h"

using namespace findscholarships;

void
fetchDbworld()
{
    FetcherDbworld fd(ConfigurationFindscholarships::instance()->pathTemp(),
                      ConfigurationFindscholarships::instance()->pathDatabase(),
                      ConfigurationFindscholarships::instance()->markerDbworld(),
                      ConfigurationFindscholarships::instance()->inputDbworld());
    
    fd.fetch();
}



void
fetchScholarshipLinks()
{
    FetcherScholarshipLinks fsl(ConfigurationFindscholarships::instance()->pathTemp(),
                                ConfigurationFindscholarships::instance()->pathDatabase(),
                                ConfigurationFindscholarships::instance()->htmlScholarshipLinksGmail(),
                                ConfigurationFindscholarships::instance()->inputScholarshipLinksGmail());
    
    fsl.fetch();
}



void
fetchScholarshipPositions()
{
    FetcherScholarshipPositions fsp(ConfigurationFindscholarships::instance()->pathTemp(),
                                    ConfigurationFindscholarships::instance()->pathDatabase(),
                                    ConfigurationFindscholarships::instance()->htmlScholarshipPositionsGmail(),
                                    ConfigurationFindscholarships::instance()->inputScholarshipPositionsGmail());
    
    fsp.fetch();
}


int main(int argc, char *argv[])
{
    std::string fetch_from = "slgmail";
    
    
    /*
    std::string fetch_from = "all";
    
    const char *help_description = "\nUsage: fetch [--from=all/manual/dbworld/spgmail/slgmail]\n";
    boost::program_options::options_description desc(help_description);
    
    desc.add_options()
    (HELP, "produce help and usage message")
    (FROM, boost::program_options::value<std::string>(&fetch_from)->default_value("all"), "choose fetching source")
    ;
    
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);
    
    if (vm.count(HELP))
    {
        std::cerr << desc << std::endl;
        exit(1);
    }*/
    
    DBGINIT(std::cerr, Logger::INFO | Logger::ERRO | Logger::VERB | Logger::DEBU);
    
    InitFindscholarships init;
    init.init();
    
    DBGINFO("Fetching starts...");
    
    if (fetch_from == "dbworld")
    {
        DBGDEBUG("inputDatabase = " << ConfigurationFindscholarships::instance()->pathDatabase())
        DBGDEBUG("markerDbworld = " << ConfigurationFindscholarships::instance()->markerDbworld())
        DBGDEBUG("inputDbworld  = " << ConfigurationFindscholarships::instance()->inputDbworld())
        
        fetchDbworld();
    }
    else if (fetch_from == "spgmail") // Scholarship Positions Gmail.
    {
        DBGDEBUG("inputDatabase = " << ConfigurationFindscholarships::instance()->pathDatabase())
        DBGDEBUG("pathTemp      = " << ConfigurationFindscholarships::instance()->pathTemp())
        DBGDEBUG("htmlSPGmail   = " << ConfigurationFindscholarships::instance()->htmlScholarshipPositionsGmail())
        DBGDEBUG("inputSPGmail  = " << ConfigurationFindscholarships::instance()->inputScholarshipPositionsGmail())
        
        fetchScholarshipPositions();
    }
    else if (fetch_from == "slgmail") // Scholarship Links Gmail.
    {
        DBGDEBUG("inputDatabase = " << ConfigurationFindscholarships::instance()->pathDatabase())
        DBGDEBUG("pathTemp      = " << ConfigurationFindscholarships::instance()->pathTemp())
        DBGDEBUG("htmlSLGmail   = " << ConfigurationFindscholarships::instance()->htmlScholarshipLinksGmail())
        DBGDEBUG("inputSLGmail  = " << ConfigurationFindscholarships::instance()->inputScholarshipLinksGmail())
        
        fetchScholarshipLinks();
    }
    else
    {
        assert (fetch_from == "all");
        DBGDEBUG("pathTemp      = " << ConfigurationFindscholarships::instance()->pathTemp())
        DBGDEBUG("inputDatabase = " << ConfigurationFindscholarships::instance()->pathDatabase())
        //DBGDEBUG("inputLinks    = " << ConfigurationFindscholarships::instance()->inputLinks())
        //DBGDEBUG("inputFetched  = " << ConfigurationFindscholarships::instance()->inputFetched())
        DBGDEBUG("markerDbworld = " << ConfigurationFindscholarships::instance()->markerDbworld())
        DBGDEBUG("htmlSLGmail   = " << ConfigurationFindscholarships::instance()->htmlScholarshipLinksGmail())
        DBGDEBUG("inputSLGmail  = " << ConfigurationFindscholarships::instance()->inputScholarshipLinksGmail())
        DBGDEBUG("htmlSPGmail   = " << ConfigurationFindscholarships::instance()->htmlScholarshipPositionsGmail())
        DBGDEBUG("inputSPGmail  = " << ConfigurationFindscholarships::instance()->inputScholarshipPositionsGmail())
        
        //fetchManual();
        fetchDbworld();
        fetchScholarshipLinks();
        fetchScholarshipPositions();
    }
    
    DBGINFO("Fetching finished...");
}
