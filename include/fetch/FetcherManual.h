#ifndef ___FETCHER_MANUAL_HPP___
#define ___FETCHER_MANUAL_HPP___

#include "FetcherBase.h"    // fetch

class FetcherManual : public FetcherBase
{
public:
    FetcherManual(const std::string &path,
                  const std::string &pathDatabase,
                  const std::string &filename_input,
                  const std::string &filename_output);
    
    ~FetcherManual();
    
    void fetch();
    
private:
    bool
    getInput(std::ifstream &file_input,
             FetchedInfoScholarship &fis);
    
private:
    const std::string m_FilenameInput;
    const std::string m_FilenameOutput;
};

#endif // ___FETCHER_MANUAL_HPP___
