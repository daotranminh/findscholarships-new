#include "fetch/FetcherBase.h"
#include "utilities/ConstantStrings.h"
#include "utilities/DateConverter.h"
#include "utilities/DateType.h"
#include "utilities/HelperFunctions.h"
#include "utilities/Logger.h"

namespace findscholarships {
    
FetcherBase::FetcherBase(const std::string &path,
                         const std::string &pathDatabase)
:  m_Path(path),
m_PathDatabase(pathDatabase)
{ }



FetcherBase::~FetcherBase()
{
    curl_easy_cleanup(m_Curl);
}



std::string
FetcherBase::fetchSingle(const std::string &url)
{
    DBGDEBUG("Fetching from " << url)
    
    std::string ret = "";
    
    m_Curl = curl_easy_init();
    
    assert (m_Curl);
    
    std::ostringstream stream;
    
    curl_easy_setopt(m_Curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(m_Curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_Curl, CURLOPT_WRITEFUNCTION, writeData1);
    curl_easy_setopt(m_Curl, CURLOPT_WRITEDATA, &stream);
    
    m_Res = curl_easy_perform(m_Curl);
    
    if (m_Res != CURLE_OK)
    {
        DBGDEBUG("FAILED!")
    }
    else
    {
        DBGDEBUG("SUCCEEDED.")
        ret = stream.str();
    }
    
    return ret;
}



void
FetcherBase::writeInputToManager(std::ofstream &file_input_to_manager,
                                 FetchedInfoScholarship &fis,
                                 const std::string &now,
                                 const std::size_t count)
{
    ConstantStrings* constrings = ConstantStrings::instance();
    
    std::ostringstream count_str;
    count_str << count;
    
    std::string filename_scholarship = m_Path + now + count_str.str() + ".txt";
    std::ofstream file_scholarship(filename_scholarship.c_str());
    
    if (!file_scholarship.is_open())
    {
        std::cerr << "Cannot open file \"" << filename_scholarship << "\" for writing!" << std::endl;
    }
    else
    {
        fis.m_HTMLCode = fetchSingle(fis.m_URL);
        file_scholarship << fis.m_HTMLCode;
        file_scholarship.close();
        
        fis.m_Filename = filename_scholarship;
        
        file_input_to_manager << constrings->PrefixBegin    << std::endl;
        
        if (fis.m_Deadline != "") file_input_to_manager << constrings->PrefixDeadline << fis.m_Deadline << std::endl;
        if (fis.m_Title != "") file_input_to_manager << constrings->PrefixTitle << fis.m_Title << std::endl;
        
        file_input_to_manager << constrings->PrefixFilename << fis.m_Filename << std::endl;
        file_input_to_manager << constrings->PrefixURL << fis.m_URL << std::endl;
        
        if (fis.m_Webpage != "")	file_input_to_manager << constrings->PrefixWebpage << fis.m_Webpage << std::endl;
        
        file_input_to_manager << constrings->PrefixEnd << std::endl;
    }
}


// Could not make this a member method of Fetcher.
// Solution for now: put it out.
std::size_t
writeData1(char *ptr,
           std::size_t size,
           std::size_t nmemb,
           void *userdata)
{
    std::ostringstream *stream = (std::ostringstream*)userdata;
    size_t count = size * nmemb;
    stream->write(ptr, count);
    return count;
}
    
} // namespace findscholarships
