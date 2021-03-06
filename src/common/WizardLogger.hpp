#ifndef WIZARDLOGGER_HPP
#define	WIZARDLOGGER_HPP

#include <iostream>
#include <stdexcept>
#include <string>

#include "../dependencies/spdlog/spdlog.h"

#define SERVER_LOGFILE "WizardPokerServer"
#define CLIENT_LOGFILE "WizardPoker"

#define LOGGER "MainLogger"

namespace WizardLogger {
    /* Initialization of the static logger */
    void initLogger(bool, std::string);

    /* API to log messages (see cpp for doc) */
    void info(std::string);
    void warning(std::string);
    void error(std::string);
    void error(std::string, std::string);
    void fatal(std::string);
    void fatal(std::string, std::string);
}

#endif	/* WIZARDLOGGER_HPP */
