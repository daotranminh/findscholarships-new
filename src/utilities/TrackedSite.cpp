#include "utilities/TrackedSite.hpp"

namespace willhabentracker {

TrackedSite::TrackedSite(const std::string &url,
                         const std::string &prefix)
: m_URL(url),
  m_Prefix(prefix)
{ }


std::ostream&
operator<<(std::ostream &os, const TrackedSite &ts)
{
    os << ts.m_URL << std::endl << ts.m_Prefix;
    
    return os;
}
    
} // namespace willhabentracker
