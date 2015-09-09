#ifndef ___TRACKED_SITE_HPP___
#define ___TRACKED_SITE_HPP___

#include <iostream>
#include <string>
#include <vector>

namespace willhabentracker {

struct TrackedSite
{
  TrackedSite(const std::string &url,
              const std::string &prefix);

  friend std::ostream&
  operator<<(std::ostream &os, const TrackedSite &ts);

  std::string m_URL;
  std::string m_Prefix;
};

typedef std::vector<TrackedSite> TrackedSiteVec;

} // namespace willhabentracker

    
#endif // ___TRACKED_SITE_HPP___
