//
//  Init.cpp
//  findscholarships-new
//
//  Created by Minh Dao Tran on 07/09/15.
//  Copyright (c) 2015 Minh Dao Tran. All rights reserved.
//

#include <fstream>

#include <boost/filesystem.hpp>

#include "utilities/ConfigurationFindscholarships.h"
#include "utilities/Logger.h"
#include "init/Init.h"

namespace findscholarships {
    
void
Init::init()
{
    std::string config_filename = "/Users/minhdt/Documents/softwares/findscholarships-website/config.cfg";
    
    ConfigurationFindscholarships::instance()->readConfig(config_filename);

    // Now check whether expected directories and files are available in the root directory
    if (!exists(ConfigurationFindscholarships::instance()->pathDatabase())) createDir(ConfigurationFindscholarships::instance()->pathDatabase());
    if (!exists(ConfigurationFindscholarships::instance()->pathTemp())) createDir(ConfigurationFindscholarships::instance()->pathTemp());
    if (!exists(ConfigurationFindscholarships::instance()->pathProductionRoot())) createDir(ConfigurationFindscholarships::instance()->pathProductionRoot());
    
    const StringVec &categories = ConfigurationFindscholarships::instance()->categories();
    for (StringVec::const_iterator it = categories.begin(); it != categories.end(); it++)
    {
        std::string category_dir = ConfigurationFindscholarships::instance()->pathProductionRoot() + (*it);
        if (!exists(category_dir)) createDir(category_dir);
    }
    
    const StringVec &storages = ConfigurationFindscholarships::instance()->pathStorages();
    for (StringVec::const_iterator it = storages.begin(); it != storages.end(); it++)
    {
        if(!exists(*it))
        {
            // create an empty database file
            DBGINFO("Init: creating file " << it->c_str());
            std::ofstream newfile;
            newfile.open(it->c_str());
            newfile << "";
            newfile.close();
        }
    }
}

bool
Init::exists(const std::string &name)
{
    boost::filesystem::path p(name);
    return boost::filesystem::exists(p);
}


void
Init::createDir(const std::string &dir)
{
    boost::filesystem::path p(dir);
    DBGINFO("Init: creating directory " << dir);
    boost::filesystem::create_directory(p);
}
    
} // namespace findscholarships
