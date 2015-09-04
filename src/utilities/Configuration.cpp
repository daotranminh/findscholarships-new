#include <cassert>
#include <iostream>
#include <fstream>

#include "Configuration.h"
#include "Logger.h"

Configuration*
Configuration::_instance = 0;

Configuration::Configuration()
: path_root(""),
path_templates(""),
path_production_root("")
{ }



Configuration*
Configuration::instance()
{
    if (_instance == 0)
    {
        _instance = new Configuration;
    }
    return _instance;
}



const std::string&
Configuration::headerPart1()
{
    return header_part1;
}



const std::string&
Configuration::headerPart2()
{
    return header_part2;
}



const std::string&
Configuration::headerMainPart2()
{
    return header_main_part2;
}



const std::string&
Configuration::bodyPart1()
{
    return body_part1;
}



const std::string&
Configuration::bodyPart2()
{
    return body_part2;
}



const std::string&
Configuration::bodyPart3()
{
    return body_part3;
}


const std::string&
Configuration::categoryPart1()
{
    return category1;
}



const std::string&
Configuration::categoryPart2()
{
    return category2;
}



const std::string&
Configuration::categoryPart3()
{
    return category3;
}


const std::string&
Configuration::categoryPart4()
{
    return category4;
}


const std::string&
Configuration::pathRoot()
{
    return path_root;
}


const std::string&
Configuration::pathProductionRoot()
{
    return path_production_root;
}



const std::string&
Configuration::rootDomain()
{
    return root_domain;
}



const std::string&
Configuration::pathDatabase()
{
    return path_database;
}



const StringVec&
Configuration::pathStorages()
{
    return path_storages;
}



const StringVec&
Configuration::categoryTitles()
{
    return category_titles;
}


const StringVec&
Configuration::categories()
{
    return category_vec;
}



const std::string&
Configuration::pathImages()
{
    return path_images;
}



const std::string&
Configuration::pathExpired()
{
    return path_expired;
}



const std::string&
Configuration::inputLinks()
{
    return filename_input_links;
}



const std::string&
Configuration::inputFetched()
{
    return filename_input_fetched;
}


const std::string&
Configuration::markerDbworld()
{
    return filename_marker_dbworld;
}


const std::string&
Configuration::pathTemp()
{
    return path_temp;
}




std::string
Configuration::readLine(const std::string& filename, const std::string& key)
{
    // configuration follows CSV format
    std::ifstream config_file(filename.c_str());
    if (config_file.is_open())
    {
        std::string line;
        while (config_file.good())
        {
            std::getline(config_file, line);
            std::size_t pos = line.find(key);
            if (pos != std::string::npos)
            {
                std::string value = line.substr(pos + key.length() + 1);
                config_file.close();
                return value;
            }
        }
        config_file.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot read configuration file: " << filename << "!")
    }
    
    return "ERROR";
}


void
Configuration::readTemplate(const std::string& fn,
                            std::string& content)
{
    std::string filename = path_templates + fn;
    std::ifstream template_file(filename.c_str());
    content = "";
    
    if (template_file.is_open())
    {
        std::string line;
        while (template_file.good())
        {
            std::getline(template_file, line);
            content = content + line + "\n";
        }
        template_file.close();
    }
    else
    {
        DBGERR(__FUNCTION__ << ": Cannot read template file: " << filename << "!")
    }
}


void
Configuration::readConfig(const std::string& filename)
{
    path_root = readLine(filename, "PATH_ROOT");
    path_templates = path_root + readLine(filename, "DIR_TEMPLATES");
    path_production_root = path_root + readLine(filename, "DIR_PRODUCTION_ROOT");
    path_database = path_root + readLine(filename, "DIR_DATABASE");
    path_images = path_root + readLine(filename, "DIR_IMAGES");
    path_expired = path_database + readLine(filename, "EXPIRED");
    path_temp = path_root + readLine(filename, "DIR_TEMPORARY");
    root_domain = readLine(filename, "ROOT_DOMAIN");
    filename_input_links = readLine(filename, "INPUT_LINKS");
    filename_input_fetched = readLine(filename, "INPUT_FETCHED");
    filename_marker_dbworld = readLine(filename, "MARKER_DBWORLD");
    filename_input_dbworld = readLine(filename, "INPUT_DBWORLD");
    filename_html_scholarship_positions_gmail = readLine(filename, "HTML_SCHOLARSHIP_POSITIONS_GMAIL");
    filename_input_scholarship_positions_gmail = readLine(filename, "INPUT_SCHOLARSHIP_POSITIONS_GMAIL");
    filename_html_scholarship_links_gmail = readLine(filename, "HTML_SCHOLARSHIP_LINKS_GMAIL");
    filename_input_scholarship_links_gmail = readLine(filename, "INPUT_SCHOLARSHIP_LINKS_GMAIL");
    
    path_storages.reserve(TOTAL_STORAGES);
    
    path_storages.push_back(path_database + readLine(filename, "DB_UNDERGRAD"));    // IDX_UNDERGRAD
    path_storages.push_back(path_database + readLine(filename, "DB_MASTER"));       // IDX_MASTER
    path_storages.push_back(path_database + readLine(filename, "DB_PHD"));          // IDX_PHD
    path_storages.push_back(path_database + readLine(filename, "DB_POSTDOC"));      // IDX_POSTDOC
    path_storages.push_back(path_database + readLine(filename, "DB_ACADEMIC_JOB")); // IDX_ACADEMIC
    path_storages.push_back(path_database + readLine(filename, "DB_UNCLASSIFIED")); // IDX_UNCLASSIFIED
    path_storages.push_back(path_database + readLine(filename, "DB_HOMEPAGE"));     // IDX_HOMEPAGE
    
    category_titles.push_back(readLine(filename, "TITLE_UNDERGRAD"));
    category_titles.push_back(readLine(filename, "TITLE_MASTER"));
    category_titles.push_back(readLine(filename, "TITLE_PHD"));
    category_titles.push_back(readLine(filename, "TITLE_POSTDOC"));
    category_titles.push_back(readLine(filename, "TITLE_ACADEMIC_JOB"));
    category_titles.push_back(readLine(filename, "TITLE_UNCLASSIFIED"));
    category_titles.push_back(readLine(filename, "TITLE_HOMEPAGE"));
    
    category_vec.push_back(readLine(filename, "CATEGORY_UNDERGRAD"));
    category_vec.push_back(readLine(filename, "CATEGORY_MASTER"));
    category_vec.push_back(readLine(filename, "CATEGORY_PHD"));
    category_vec.push_back(readLine(filename, "CATEGORY_POSTDOC"));
    category_vec.push_back(readLine(filename, "CATEGORY_ACADEMIC_JOB"));
    category_vec.push_back(readLine(filename, "CATEGORY_UNCLASSIFIED"));
    category_vec.push_back(readLine(filename, "CATEGORY_HOMEPAGE"));
    
    assert (path_storages.size() == TOTAL_STORAGES);
    
    header1_tpl = readLine(filename, "HEADER_PART1");
    header2_tpl = readLine(filename, "HEADER_PART2");
    header2_main_tpl = readLine(filename, "HEADER_MAIN_PART2");
    body1_tpl = readLine(filename, "BODY_PART1");
    body2_tpl = readLine(filename, "BODY_PART2");
    body3_tpl = readLine(filename, "BODY_PART3");
    
    category1_tpl = readLine(filename, "CATEGORY_PART1");
    category2_tpl = readLine(filename, "CATEGORY_PART2");
    category3_tpl = readLine(filename, "CATEGORY_PART3");
    category4_tpl = readLine(filename, "CATEGORY_PART4");
    
    readTemplate(header1_tpl, header_part1);
    readTemplate(header2_tpl, header_part2);
    readTemplate(header2_main_tpl, header_main_part2);
    readTemplate(body1_tpl, body_part1);
    readTemplate(body2_tpl, body_part2);
    readTemplate(body3_tpl, body_part3);
    
    readTemplate(category1_tpl, category1);
    readTemplate(category2_tpl, category2);
    readTemplate(category3_tpl, category3);
    readTemplate(category4_tpl, category4);
}
