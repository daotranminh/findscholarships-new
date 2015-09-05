#ifndef ___FETCHED_INFO_BASE_HPP___
#define ___FETCHED_INFO_BASE_HPP___

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

struct FetchedInfoBase
{
    FetchedInfoBase()
    : m_URL(""),
    m_HTMLCode("")
    { }
    
    FetchedInfoBase(const std::string &url)
    : m_URL(url),
    m_HTMLCode("")
    { }
    
    std::string m_URL;
    std::string m_HTMLCode;
};

typedef boost::shared_ptr<FetchedInfoBase> FetchedInfoBasePtr;
typedef std::vector<FetchedInfoBasePtr> FetchedInfoBaseVec;
typedef boost::shared_ptr<FetchedInfoBaseVec> FetchedInfoBaseVecPtr;


#endif //  ___FETCHED_INFO_BASE_HPP___
