#include "FetcherDbworld.h"   // fetch

namespace findscholarships {

FetcherDbworld::FetcherDbworld(const std::string &path,
                               const std::string &pathDatabase,
                               const std::string &filename_marker_dbworld,
                               const std::string &filename_input_dbworld)
: FetcherBase(path, pathDatabase),
m_FilenameMarkerDbworld(m_Path + filename_marker_dbworld),
m_FilenameInputDbworld(m_Path + filename_input_dbworld)
{ }



FetcherDbworld::~FetcherDbworld()
{ }



FetchedInfoScholarship
FetcherDbworld::lastCrawledDbworldJob()
{
    FetchedInfoScholarship result;
    
    std::ifstream file_marker_dbworld(m_FilenameMarkerDbworld.c_str());
    if (file_marker_dbworld.good())
    {
        ConstantStrings* constrings = ConstantStrings::instance();
        std::string line;
        std::getline(file_marker_dbworld, line);
        
        
        assert (line.compare(constrings->PrefixBegin) == 0);
        
        
        while (line != "" && line.compare(constrings->PrefixEnd) != 0)
        {
            if (line.find(constrings->PrefixDeadline) != std::string::npos) result.m_Deadline = line.substr(constrings->PrefixDeadline.length());
            if (line.find(constrings->PrefixTitle) != std::string::npos)    result.m_Title = line.substr(constrings->PrefixTitle.length());
            if (line.find(constrings->PrefixURL) != std::string::npos)      result.m_URL = line.substr(constrings->PrefixURL.length());
            if (line.find(constrings->PrefixWebpage) != std::string::npos)  result.m_Webpage = line.substr(constrings->PrefixWebpage.length());
            std::getline(file_marker_dbworld, line);
        }
        
        file_marker_dbworld.close();
    }
    
    return result;
}



void
FetcherDbworld::cacheCrawledDbworldJob(const FetchedInfoScholarship &fis)
{
    std::ofstream file_marker_dbworld(m_FilenameMarkerDbworld.c_str());
    if (file_marker_dbworld.is_open())
    {
        ConstantStrings* constrings = ConstantStrings::instance();
        file_marker_dbworld << constrings->PrefixBegin << std::endl
        << constrings->PrefixDeadline << fis.m_Deadline << std::endl
        << constrings->PrefixTitle << fis.m_Title << std::endl
        << constrings->PrefixURL << fis.m_URL << std::endl
        << constrings->PrefixWebpage << fis.m_Webpage << std::endl
        << constrings->PrefixEnd << std::endl;
        file_marker_dbworld.close();
    }
}



int
FetcherDbworld::fetchDbworldRow(const std::string &dbworld,
                                tree<HTML::Node>::iterator row_it,
                                FetchedInfoScholarship &fis)
{
    DBGDEBUG("Fetching from dbworld...")
    
    tree<HTML::Node>::iterator beg_row = row_it.begin();
    tree<HTML::Node>::iterator end_row = row_it.end();
    
    std::size_t index = 0;
    int move_on = 0;
    
    std::string type = "";
    
    for (tree<HTML::Node>::iterator column_it = beg_row; column_it  != end_row; column_it++)
    {
        if (column_it->tagName() == "TD")
        {
            move_on = 1; // found an entry
            switch (index++)
            {
                case 1: // type: journal CFP | conf. ann. | ***job ann.*** | news | soft. ann.
                {
                    type = column_it->content(dbworld);
                    if (type != "job ann. ") move_on = -1;
                    break;
                }
                case 3:
                {
                    tree<HTML::Node>::iterator url_it = column_it.begin();
                    fis.m_URL = url_it->text();
                    extractLink(fis.m_URL);
                    fis.m_Title = url_it->content(dbworld);
                    break;
                }
                case 4:
                {
                    std::string deadline = column_it->content(dbworld);
                    boost::gregorian::date d(boost::gregorian::from_uk_string(deadline));
                    fis.m_Deadline = boost::gregorian::to_iso_string(d);
                    break;
                }
                case 5:
                {
                    tree<HTML::Node>::iterator link_it = column_it.begin();
                    fis.m_Webpage = link_it->text();
                    extractLink(fis.m_Webpage);
                    break;
                }
            }
            
            if (move_on == -1) // did NOT get a job announcement
                break;
        }
    }
    
    return move_on;
}



void
FetcherDbworld::fetch()
{
    const std::string now = "dbworld" + currentDateTime();
    std::size_t count = 0;
    
    std::string dbworld = fetchSingle("https://research.cs.wisc.edu/dbworld/browse.html");
    HTML::ParserDom parser;
    tree<HTML::Node> dom = parser.parseTree(dbworld);
    
    FetchedInfoScholarship last_crawled_dbworld_job = lastCrawledDbworldJob();
    std::ofstream file_input_dbworld(m_FilenameInputDbworld.c_str());
    
    DBGDEBUG("Now exploring the table...")
    
    for (tree<HTML::Node>::iterator table_it = dom.begin(); table_it != dom.end(); ++table_it)
    {
        if (table_it->tagName() == "TABLE")
        {
            tree<HTML::Node>::iterator beg_table = table_it.begin();
            tree<HTML::Node>::iterator end_table = table_it.end();
            
            // Table structure:
            // - (0) Sent (upload date)
            // + (1) Message Type
            // - (2) From
            // + (3) Subject
            // + (4) Deadline
            // + (5) Web Page
            
            bool is_head = true;
            for (tree<HTML::Node>::iterator row_it = beg_table; row_it != end_table; ++row_it)
            {
                if (row_it->tagName() == "TR")
                {
                    if (is_head) is_head = false;
                    else // at a row with content
                    {
                        FetchedInfoScholarship fis;
                        
                        int move_on = fetchDbworldRow(dbworld, row_it, fis);
                        
                        if (move_on == 1) // write to file
                        {
                            if (fis == last_crawled_dbworld_job) // check with the marker whether we reached last time's fetched data
                            {
                                DBGDEBUG("Encounter last time's crawled job. Bailing out...")
                                break; 
                            }
                            
                            DBGDEBUG("Got a new job announcement")			 
                            if (++count == 1) cacheCrawledDbworldJob(fis);
                            
                            writeInputToManager(file_input_dbworld, fis, now, count);			    
                        }
                    }
                }
            }
            break;
        }
    }
    
    DBGINFO("Fetched " << count << " scholarship items from dbworld!")
    
    file_input_dbworld.close();
}
    
} // namespace findscholarships


