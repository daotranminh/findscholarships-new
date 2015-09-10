#ifndef ___DATA_ITEM_WILLHABEN_TRACKER_HPP___
#define ___DATA_ITEM_WILLHABEN_TRACKER_HPP___

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace willhabentracker {

struct DataItem
{
  DataItem(const std::string &url,
           const std::string &title,
           const std::string &description,
           const float &price);

  friend
  std::ostream&
  operator<<(std::ostream &os, const DataItem &di);

  bool
  operator==(const DataItem &other);

  bool        m_IsNew;
  std::string m_URL;
  std::string m_Title;
  std::string m_Description;
  float       m_Price;
  //ToDo
  //Date_t      m_PublishedTime;
};

typedef boost::shared_ptr<DataItem> DataItemPtr;
typedef std::vector<DataItemPtr> DataItemVec;

} // namespace willhabentracker
    
#endif // ___DATA_ITEM_WILLHABEN_TRACKER_HPP___
