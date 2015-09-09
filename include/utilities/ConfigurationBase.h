#ifndef ___CONFIGURATION_BASE_H___
#define ___CONFIGURATION_BASE_H___

#include <string>
#include <vector>

typedef std::vector<std::string> StringVec;

// singleton pattern
class ConfigurationBase
{
public:
    static ConfigurationBase* instance();
    
    virtual void
    readConfig(const std::string& filename);
    
protected:
    ConfigurationBase();
    
    std::string
    readLine(const std::string& filename,
             const std::string& key);
    
private:
    static ConfigurationBase* _instance;
};

#endif // ___CONFIGURATION_BASE_H___
