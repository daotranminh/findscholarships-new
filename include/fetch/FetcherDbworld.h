#ifndef ___FETCHER_DBWORLD_HPP__
#define ___FETCHER_DBWORLD_HPP__

#include "fetch/FetcherBase.h"
#include "utilities/ConstantStrings.h"
#include "utilities/DateType.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"

namespace findscholarships {

class FetcherDbworld : public FetcherBase
{
public:
    FetcherDbworld(const std::string &path,
                   const std::string &pathDatabase,
                   const std::string &filename_marker_dbworld,
                   const std::string &filename_input_dbworld);
    
    ~FetcherDbworld();
    
    void fetch();
    
private:
    FetchedInfoScholarship
    lastCrawledDbworldJob();
    
    void
    cacheCrawledDbworldJob(const FetchedInfoScholarship &fis);
    
    int
    fetchDbworldRow(const std::string &dbworld,
                    tree<HTML::Node>::iterator row_it,
                    FetchedInfoScholarship &fis);
    
private:
    const std::string m_FilenameMarkerDbworld;
    const std::string m_FilenameInputDbworld;
};
    
} // namespace findscholarships

#endif // ___FETCHER_DBWORLD_HPP__
