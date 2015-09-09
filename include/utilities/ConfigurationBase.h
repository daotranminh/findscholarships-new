#ifndef ___CONFIGURATION_BASE_H___
#define ___CONFIGURATION_BASE_H___

#include <string>

class ConfigurationBase
{
public:
    virtual void
    readConfig(const std::string& filename);
    
protected:
    ConfigurationBase();
    
    std::string
    readLine(const std::string& filename,
             const std::string& key);
};

#endif // ___CONFIGURATION_BASE_H___
