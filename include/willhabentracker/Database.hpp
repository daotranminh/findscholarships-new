#ifndef ___DATABASE_WILLHABEN_TRACKER_HPP___
#define ___DATABASE_WILLHABEN_TRACKER_HPP___

#include <boost/shared_ptr.hpp>

#include "willhabentracker/DataItem.hpp"

namespace willhabentracker {

class Database
{
public:
  Database(const std::string &name = "");

  void
  setDatabaseName(const std::string &name);

  void
  add(const DataItemPtr &di);

  void
  writeDatabase();

  bool
  exists(const DataItemPtr &di);

  void
  compare(const boost::shared_ptr<Database> &db);

  void
  show(bool showNew = false);

private:
  void
  loadDatabase();

  std::string
  readContent(std::ifstream &file_input,
              const std::string &beg,
              const std::string &end);

private:
  std::string m_Name;
  DataItemVec m_DataItems;
};

typedef boost::shared_ptr<Database> DatabasePtr;

} // namespace willhabentracker

#endif // ___DATABASE_WILLHABEN_TRACKER_HPP___
