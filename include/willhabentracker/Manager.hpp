#ifndef ___MANAGER_WILLHABEN_TRACKER_HPP___
#define ___MANAGER_WILLHABEN_TRACKER_HPP___

#include <string>

namespace willhabentracker {

class Manager
{
public:
  void
  process();

private:
  void
  trackSingleSite(const std::string &url,
                  const std::string &prefix);
};
    
} // namespace willhabentrackerWILLHABEN_TRACKER_

#endif // ___MANAGER_WILLHABEN_TRACKER_HPP___
