#ifndef ___CONFIGURATION_HPP___
#define ___CONFIGURATION_HPP___

#include <string>
#include <vector>

#define IDX_UNDER_GRADUATE 0
#define IDX_MASTER         1
#define IDX_PHD            2
#define IDX_POSTDOC        3
#define IDX_ACADEMIC       4
#define IDX_UNCLASSIFIED   5
#define IDX_HOMEPAGE       6
#define TOTAL_STORAGES     7

typedef std::vector<std::string> StringVec;

// singleton pattern
class Configuration
{
public:
    static Configuration* instance();
    
    void
    readConfig(const std::string& filename);
    
    const std::string&
    headerPart1();
    
    const std::string&
    headerPart2();
    
    const std::string&
    headerMainPart2();
    
    const std::string&
    bodyPart1();
    
    const std::string&
    bodyPart2();
    
    const std::string&
    bodyPart3();
    
    const std::string&
    categoryPart1();
    
    const std::string&
    categoryPart2();
    
    const std::string&
    categoryPart3();
    
    const std::string&
    categoryPart4();
    
    const std::string&
    pathRoot();
    
    const std::string&
    pathProductionRoot();
    
    const std::string&
    rootDomain();
    
    const std::string&
    pathDatabase();
    
    const StringVec&
    pathStorages();
    
    const StringVec&
    categoryTitles();
    
    const StringVec&
    categories();
    
    const std::string&
    pathImages();
    
    const std::string&
    pathExpired();
    
    const std::string&
    inputLinks();
    
    const std::string&
    inputFetched();
    
    const std::string&
    markerDbworld();
    
    const std::string&
    inputDbworld()
    {
        return filename_input_dbworld;
    }
    
    const std::string&
    htmlScholarshipPositionsGmail()
    {
        return filename_html_scholarship_positions_gmail;
    }
    
    const std::string&
    inputScholarshipPositionsGmail()
    {
        return filename_input_scholarship_positions_gmail;
    }
    
    const std::string&
    htmlScholarshipLinksGmail()
    {
        return filename_html_scholarship_links_gmail;
    }
    
    const std::string&
    inputScholarshipLinksGmail()
    {
        return filename_input_scholarship_links_gmail;
    }
    
    const std::string&
    pathTemp();
    
private:
    Configuration();
    
    std::string
    readLine(const std::string& filename,
             const std::string& key);
    
    void
    readTemplate(const std::string& fn,
                 std::string& content);
    
private:
    std::string path_root;
    std::string path_templates;        // where to read the templates
    std::string path_production_root;  // where to save the resulting files
    std::string path_database;         // where to save the list of currently online files
    std::string root_domain;           // http://blabla.com/findscholarships/
    std::string path_images;
    std::string path_expired;
    std::string path_temp;
    
    std::string filename_input_links;
    std::string filename_input_fetched;
    std::string filename_marker_dbworld;
    std::string filename_input_dbworld;
    std::string filename_html_scholarship_positions_gmail;
    std::string filename_input_scholarship_positions_gmail;
    std::string filename_html_scholarship_links_gmail;
    std::string filename_input_scholarship_links_gmail;
    
    StringVec path_storages;
    StringVec category_titles;
    StringVec category_vec;
    
    std::string header1_tpl;
    std::string header2_tpl;
    std::string header2_main_tpl;
    std::string body1_tpl;
    std::string body2_tpl;
    std::string body3_tpl;
    
    std::string category1_tpl;
    std::string category2_tpl;
    std::string category3_tpl;
    std::string category4_tpl;
    
    std::string header_part1;
    std::string header_part2;
    std::string header_main_part2;
    std::string body_part1;
    std::string body_part2;
    std::string body_part3;
    
    std::string category1;
    std::string category2;
    std::string category3;
    std::string category4;
    
    static Configuration* _instance;
};

#endif // ___CONFIGURATION_HPP___
