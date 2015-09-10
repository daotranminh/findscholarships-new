#include "willhabentracker/Manager.hpp"
#include "willhabentracker/Tracker.hpp"
#include "utilities/ConfigurationWillhabentracker.h"

namespace willhabentracker {

void
Manager::process()
{
    const TrackedSiteVec &trackedSites = ConfigurationWillhabentracker::instance()->trackedSites();
    
    for (TrackedSiteVec::const_iterator it = trackedSites.begin(); it != trackedSites.end(); ++it)
    {
        trackSingleSite(it->m_URL, it->m_Prefix);
    }
}



void
Manager::trackSingleSite(const std::string &url,
                         const std::string &prefix)
{
    // ToDo: dynamically create corresponding Tracker based on the URL.
    // For now, we just have a tracker for willhaben.at
    
    bool gratis = false;
    if (url.find("zu-verschenken") != std::string::npos) gratis = true;
    
    Tracker tk(url);
    DatabasePtr newItems = tk.track(gratis); // ToDo: zuverschenken!!!
    DatabasePtr oldItems = DatabasePtr(new Database(prefix));
    
    // compare items to find the real new ones.
    newItems->compare(oldItems);
    newItems->show(true);
    newItems->setDatabaseName(prefix);
    newItems->writeDatabase();
}

} // namespace willhabentracker