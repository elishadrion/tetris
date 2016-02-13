
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
    /* Constructor and destructor */
    WizardLogger(bool);
    ~WizardLogger() = default;
    
    /* API to log messages (see cpp for doc) */
    void debug(std::string);
    void info(std::string);
    void warn(std::string);
    void error(std::string);
    void error(std::string, std::exception);
    void fatal(std::string);
    void fatal(std::string, std::exception);
};

#endif	/* WIZARDLOGGER_HPP */
