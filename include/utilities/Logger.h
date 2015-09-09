#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#define ENABLE_DEBUG

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Logger
{
public:
    static void create(std::ostream& outStream = std::cerr,
                       unsigned int level = ~static_cast<unsigned int>(0));
    
    static Logger* instance();
    
    void
    print(unsigned int level,
          const std::string& message);
    
public:
    static const unsigned int INFO = 0x01;
    static const unsigned int WARN = 0x02;
    static const unsigned int ERRO = 0x04;
    static const unsigned int VERB = 0x08;
    static const unsigned int DEBU = 0x10;
    
private:
    Logger(std::ostream& outStream, unsigned int levels);
    
    bool
    shallPrint(unsigned int level);
    
    std::string
    strLevel(unsigned int level);
    
private:
    std::ostream& out;
    unsigned int printLevels;
    
    static Logger* _instance;
};


#ifdef ENABLE_DEBUG
#   define DBGINIT(outStream, level) Logger::create(outStream, level);

#   define DBGLOG(level, message)    { std::ostringstream __debug_stream__; \
__debug_stream__ << message; \
::Logger::instance()->print(level, __debug_stream__.str()); }

#   define DBGINFO(message)          DBGLOG(Logger::INFO, message)
#   define DBGWARN(message)          DBGLOG(Logger::WARN, message)
#   define DBGERR(message)           DBGLOG(Logger::ERRO, message)
#   define DBGVERB(message)          DBGLOG(Logger::VERB, message)
#   define DBGDEBUG(message)         DBGLOG(Logger::DEBU, message)
#else
#   define DBGINIT(outStream, level) do { } while (false);
#   define DBGLOG(level, message)    do { } while (false);
#   define DBGINFO(message)          do { } while (false);
#   define DBGWARN(message)          do { } while (false);
#   define DBGERR(message)           do { } while (false);
#   define DBGVERB(message)          do { } while (false);
#   define DBGDEBUG(message)         do { } while (false);
#endif // ENABLE_DEBUG

#endif // __LOGGER_HPP__
