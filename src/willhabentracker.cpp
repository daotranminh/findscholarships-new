#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include <boost/program_options.hpp>

#include "init/InitWillhabentracker.hpp"
#include "willhabentracker/Manager.hpp"

using namespace willhabentracker;

int main(int argc, const char *argv[])
{
    InitWillhabentracker init;
    init.init();
    
    Manager man;
    man.process();
    
    // const TrackedSiteVec &ts = config->trackedSites();
    // std::copy(ts.begin(), ts.end(), std::ostream_iterator<TrackedSite>(std::cout, "\n\n"));
}
