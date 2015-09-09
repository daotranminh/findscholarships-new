#include <iostream>
#include "utilities/Logger.h"

namespace findscholarships {

Logger::Logger(std::ostream &outStream, unsigned int levels)
: out(outStream), printLevels(levels)
{ }



void
Logger::create(std::ostream &outStream, unsigned int levels)
{
    if (!_instance)
    {
        _instance = new Logger(outStream, levels);
    }
    else
    {
        std::cerr << "WARNING: Logger already created!" << std::endl;
    }
}



Logger*
Logger::instance()
{
    if (!_instance)
    {
        std::cerr << "ERROR: Logger was not initialized!" << std::endl;
        return NULL;
    }
    
    return _instance;
}



bool
Logger::shallPrint(unsigned int level)
{
    return ((printLevels & level) != 0);
}


std::string
Logger::strLevel(unsigned int level)
{
    std::string tmp = "";
    
    switch (level)
    {
        case INFO:
            tmp = "I: ";
            break;
        case WARN:
            tmp = "W: ";
            break;
        case ERRO:
            tmp = "E: ";
            break;
        case VERB:
            tmp = "V: ";
            break;
        case DEBU:
            tmp = "D: ";
            break;
    }
    
    return tmp;
}


void
Logger::print(unsigned int level, const std::string& message)
{
    if (shallPrint(level))
    {
        out << strLevel(level) << message << std::endl;
    }
}


Logger*
Logger::_instance = NULL;
    
} // namespace findscholarships
