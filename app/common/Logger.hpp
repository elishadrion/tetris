
#ifndef LOGGER_HPP
#define	LOGGER_HPP

#include <iostream>
#include <string>

#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

#ifdef SERVER
#define LOGFILE "WizardPoker_server.log"
#else
#define LOGFILE "WizardPoker.log"
#endif

class Logger {
    log4cpp::Appender *_streamAppender;
    log4cpp::Appender *_fileAppender;
    bool _canUseStreamAppender;
    
    /* Must be define here because it's a reference */
    log4cpp::Category& _root = log4cpp::Category::getRoot();
public:
    /* Constructor and destructor */
    Logger(bool);
    ~Logger() = default;
    
    /* API to log messages */
    void printInfo(std::string);
    void printWarn(std::string);
    void printError(std::string);
};

#endif	/* LOGGER_HPP */
