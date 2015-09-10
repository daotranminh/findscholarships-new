#ifndef ___INIT_BASE_HPP___
#define ___INIT_BASE_HPP___

#include <string>

class InitBase
{
public:
    virtual void
    init() = 0;
    
protected:
    bool
    exists(const std::string &name);
    
    void
    createDir(const std::string &dir);
};


#endif // ___INIT_BASE_HPP___
