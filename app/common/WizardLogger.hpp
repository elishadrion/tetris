
#ifndef WIZARDLOGGER_HPP
#define	WIZARDLOGGER_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "include/spdlog/spdlog.h"

//TODO not working... why ?
#ifdef SERVER
    #define LOGFILE "WizardPokerServer"
#else
    #define LOGFILE "WizardPoker"
#endif

#define LOGGER "MainLogger"

class WizardLogger {
public:
    /* We don't need Constructor and destructor */
    WizardLogger() = default;
    ~WizardLogger() = default;
    
    /* Initialization of the static logger */
    static void initLogger(bool);
    
    /* API to log messages (see cpp for doc) */
    static void debug(std::string);
    static void info(std::string);
    static void warn(std::string);
    static void error(std::string);
    static void error(std::string, std::exception);
    static void fatal(std::string);
    static void fatal(std::string, std::exception);
};

#endif	/* WIZARDLOGGER_HPP */
