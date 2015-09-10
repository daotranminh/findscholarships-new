#ifndef ___CONFIGURATION_WILLHABEN_TRACKER_HPP___
#define ___CONFIGURATION_WILLHABEN_TRACKER_HPP___

#include "utilities/ConfigurationBase.h"
#include "utilities/TrackedSite.hpp"

namespace willhabentracker {

typedef std::vector<std::string> StringVec;

// singleton pattern
class ConfigurationWillhabentracker : public ::ConfigurationBase
{
public:
  static ConfigurationWillhabentracker* instance();
	
  void
  readConfig(const std::string& filename);
  
  const std::string&
  pathRoot()
  { return m_PathRoot; }
  
  const std::string&
  pathDatabase()
  { return m_PathDatabase; }

  const std::string&
  beginURL() 
  { return m_BeginURL; }

  const std::string&
  endURL() 
  { return m_EndURL; }

  const std::string&
  beginTitle() 
  { return m_BeginTitle; }

  const std::string&
  endTitle() 
  { return m_EndTitle; }

  const std::string&
  beginDesc() 
  { return m_BeginDesc; }

  const std::string&
  endDesc() 
  { return m_EndDesc; }

  const std::string&
  beginPrice() 
  { return m_BeginPrice; }

  const std::string&
  endPrice() 
  { return m_EndPrice; }

  const TrackedSiteVec&
  trackedSites()
  { return m_TrackedSites; }

  const std::vector<std::string>&
  ignoreList()
  { return m_IgnoreList; }

private:
  ConfigurationWillhabentracker();

  void
  readDestination(const std::string &filename);

  void
  readIgnoreList(const std::string &filename);
  
private:
  std::string m_PathRoot;
  std::string m_PathDatabase;         // where to save the list of currently online files
  std::string m_BeginURL;
  std::string m_EndURL;
  std::string m_BeginTitle;
  std::string m_EndTitle;
  std::string m_BeginDesc;
  std::string m_EndDesc;
  std::string m_BeginPrice;
  std::string m_EndPrice;

  TrackedSiteVec m_TrackedSites;

  std::vector<std::string> m_IgnoreList;

  static ConfigurationWillhabentracker* _instance;
};

} // namespace willhabentracker

#endif // ___CONFIGURATION_WILLHABEN_TRACKER_HPP___
