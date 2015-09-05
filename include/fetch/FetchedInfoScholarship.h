#ifndef ___FETCHED_INFO_SCHOLARSHIP_HPP___
#define ___FETCHED_INFO_SCHOLARSHIP_HPP___

#include "FetchedInfoBase.h"    // fetch

struct FetchedInfoScholarship : FetchedInfoBase
{
    FetchedInfoScholarship()
    : FetchedInfoBase(),
    m_Deadline(""),
    m_Title(""),
    m_Webpage("")
    { }
    
    FetchedInfoScholarship(const std::string &deadline,
                           const std::string &title,
                           const std::string &url)
    : FetchedInfoBase(url),
    m_Deadline(deadline),
    m_Title(title),
    m_Filename(""),
    m_Webpage("")
    { }
    
    
    FetchedInfoScholarship(const std::string &deadline,
                           const std::string &title,
                           const std::string &url,
                           const std::string &webpage)
    : FetchedInfoBase(url),
    m_Deadline(deadline),
    m_Title(title),
    m_Filename(""),
    m_Webpage(webpage)
    { }
    
    bool operator==(const FetchedInfoScholarship &other)
    {
        return (m_URL == other.m_URL &&
                m_Deadline == other.m_Deadline &&
                m_Title == other.m_Title &&
                m_Webpage == other.m_Webpage &&
                m_HTMLCode == other.m_HTMLCode);
    }
    
    std::string m_Deadline;
    std::string m_Title;
    std::string m_Filename;
    std::string m_Webpage;
};

typedef boost::shared_ptr<FetchedInfoScholarship> FetchedInfoScholarshipPtr;
typedef std::vector<FetchedInfoScholarshipPtr> FetchedInfoScholarshipVec;
typedef boost::shared_ptr<FetchedInfoScholarshipVec> FetchedInfoScholarshipVecPtr;

#endif // ___FETCHED_INFO_SCHOLARSHIP_HPP___
