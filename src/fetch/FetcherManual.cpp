#include "FetcherManual.h"      // fetch
#include "ConstantStrings.h"    // utilities
#include "DateType.h"           // utilities
#include "HelperFunctions.h"    // utilities
#include "Logger.h"             // utilities


FetcherManual::FetcherManual(const std::string &path,
                             const std::string &pathDatabase,
                             const std::string &filename_input,
                             const std::string &filename_output)
: FetcherBase(path, pathDatabase),
m_FilenameInput(m_Path + filename_input),
m_FilenameOutput(m_Path + filename_output)
{ }



FetcherManual::~FetcherManual()
{ }



void
FetcherManual::fetch()
{
    DBGDEBUG("Fetching from manual input...")
    
    std::ifstream file_input(m_FilenameInput.c_str());
    std::ofstream file_output(m_FilenameOutput.c_str());
    
    if (!file_input.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameInput << "\" for reading!" << std::endl;
        return;
    }
    
    if (!file_output.is_open())
    {
        std::cerr << "Cannot open file \"" << m_FilenameOutput << "\" for writing!" << std::endl;
        return;
    }
    
    const std::string now = currentDateTime();
    std::size_t count = 0;
    
    ConstantStrings *constrings = ConstantStrings::instance();
    
    while (file_input.good())
    {
        FetchedInfoScholarship fis;
        if (!getInput(file_input, fis)) break;
        
        writeInputToManager(file_output, fis, now, count);
        count++;
    }
    
    DBGINFO("Fetched " << count << " scholarship items from manual input!")
    
    file_input.close();
    file_output.close();
}
