
#ifndef WIZARDLOGGER_HPP
#define	WIZARDLOGGER_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "include/spdlog/spdlog.h"

#define SERVER_LOGFILE "WizardPokerServer"
#define CLIENT_LOGFILE "WizardPoker"

#define LOGGER "MainLogger"

namespace WizardLogger {
    /* Initialization of the static logger */
    static void initLogger(bool, std::string);
    
    /* API to log messages (see cpp for doc) */
    static void info(std::string);
    static void warn(std::string);
    static void error(std::string);
    static void error(std::string, std::exception);
    static void fatal(std::string);
    static void fatal(std::string, std::exception);
};

#endif	/* WIZARDLOGGER_HPP */
