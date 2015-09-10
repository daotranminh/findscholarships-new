//
//  Init.h
//  findscholarships-new
//
//  Created by Minh Dao Tran on 07/09/15.
//  Copyright (c) 2015 Minh Dao Tran. All rights reserved.
//

#ifndef ___INIT_H___
#define ___INIT_H___

#include <iostream>

namespace findscholarships {

class Init
{
public:
    void
    init();
    
private:
    bool
    exists(const std::string &name);
    
    void
    createDir(const std::string &dir);
};

} // namespace findscholarships

#endif // ___INIT_H___
