#ifndef ___FETCHER_BASE_HPP___
#define ___FETCHER_BASE_HPP___

#include <curl/curl.h>
#include "fetch/FetchedInfoScholarship.h" // fetch
#include "html/ParserDom.h"              // html

using namespace htmlcxx;

namespace findscholarships {

class FetcherBase
{
public:
    FetcherBase(const std::string &path,
                const std::string &pathDatabase);
    
    ~FetcherBase();
    
    virtual void
    fetch() = 0;
    
protected:
    std::string
    fetchSingle(const std::string &url);
    
    void
    writeInputToManager(std::ofstream &file_input_to_manager,
                        FetchedInfoScholarship &fis,
                        const std::string &now,
                        const std::size_t count);
    
protected:
    const std::string m_Path;
    const std::string m_PathDatabase;
    
private:
    CURL *m_Curl;
    CURLcode m_Res;
};



// Could not make this a member method of Fetcher.
// Solution for now: put it out.
std::size_t
writeData1(char *ptr,
           std::size_t size,
           std::size_t nmemb, 
           void *userdata);
    
} // namespace findscholarships

#endif // ___FETCHER_BASE_HPP___
