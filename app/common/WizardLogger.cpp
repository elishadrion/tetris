#include "WizardLogger.hpp"

/* We create and configure a new Log4cpp instance for all the program
 * Actually, we define a file appender and a stream appender
 * But only file appender is used when we are the client (in console mode)
 * @param useConsole : if we are client, can we use console log ?
 * @param logFileName : name for the log file
 * @throw exception : cannot initialize logger
 */
void WizardLogger::initLogger(bool useConsole, std::string logFileName) {
    try {
        /* Active async logger with a queue size of 1048576 (must be power of 2)
         * Lets default blocking policy when queue is full
         * If error occure, it's throw at the next call of the logger
         */
        spdlog::set_async_mode(1048576);
        
        /* We prepare to use combined logger (file and console)
         * So we only need to call once and both logger get message
         */
         std::vector<spdlog::sink_ptr> sinks;
        
        /* Create a log file with rotation
         * with these parameters : 
         * <file's name>, <file's extention>
         * <max size before rotate (here 5 Mib)>, <max file (with rotation)>
         * <force flush>
         */
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logFileName, "log", 1048576 * 5, 2, true));
        
        /* If we can, we create some console logger */
        if (useConsole) {
            sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
        }
        
        /* We register combined logger to use it */
        spdlog::register_logger(std::make_shared<spdlog::logger>(LOGGER, begin(sinks), end(sinks)));
        
        /* We define formating for logger
         * "[YYYY-MM-DD HH:mm:ss.ms] [log level] message"
         */
        spdlog::get(LOGGER)->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l]\t%v");
        
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[FATAL ERROR] Impossible d'initialiser le Logger :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print an INFO message
 * Use it for log like "send login request"
 * @param message : the string to log
 * @throw exception : cannot log "message"
 */
void WizardLogger::info(std::string message) {
    try {
        spdlog::get(LOGGER)->info(message);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print a WARNING message
 * Use it for minor error like "no user found"
 * @param message : the string to log
 * @throw exception : cannot log "message"
 */
void WizardLogger::warn(std::string message) {
   try {
        spdlog::get(LOGGER)->warn(message);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print an ERROR message
 * Use it for major error like "client socket close unexpectedly"
 * @param message : the string to log
 * @throw exception : cannot log "message"
 */
void WizardLogger::error(std::string message) {
    try {
        spdlog::get(LOGGER)->error(message);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print an ERROR message
 * Use it for major error like "client socket close unexpectedly"
 * @param message : the string to log
 * @param exception : exception to print
 * @throw exception : cannot log "message"
 */
void WizardLogger::error(std::string message, std::exception ex) {
    try {
        spdlog::get(LOGGER)->error(message+"\n***\n"+ex.what()+"\n***");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print an FATAL message
 * Use it for fatal error like "cannot write/read the HDD"
 * @param message : the string to log
 * @throw exception : cannot log "message"
 */
void WizardLogger::fatal(std::string message) {
    try {
        spdlog::get(LOGGER)->emerg(message);
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}

/* Print an FATAL message
 * Use it for fatal error like "cannot write/read the HDD"
 * @param message : the string to log
 * @param exception : exception to print
 * @throw exception : cannot log "message"
 */
void WizardLogger::fatal(std::string message, std::exception ex) {
    try {
        spdlog::get(LOGGER)->emerg(message+"\n***\n"+ex.what()+"\n***");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cerr << "[ERREUR] Impossible d'afficher le log :\n" << ex.what() << std::endl;
        throw; 
    }
}
