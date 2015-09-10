//
//  Init.cpp
//  findscholarships-new
//
//  Created by Minh Dao Tran on 07/09/15.
//  Copyright (c) 2015 Minh Dao Tran. All rights reserved.
//

#include <fstream>

#include <boost/filesystem.hpp>

#include "utilities/Logger.h"
#include "init/InitBase.hpp"

bool
InitBase::exists(const std::string &name)
{
    boost::filesystem::path p(name);
    return boost::filesystem::exists(p);
}
    
    
void
InitBase::createDir(const std::string &dir)
{
    boost::filesystem::path p(dir);
    DBGINFO("Init: creating directory " << dir);
    boost::filesystem::create_directory(p);
}
