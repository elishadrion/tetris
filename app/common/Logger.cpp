#include "Logger.hpp"

/* We create and configure a new Log4cpp instance for all the program
 * Actually, we define a file appender and a stream appender
 * But only file appender is used when we are the client (in console mode)
 * @param clientConsole : is the client in console mode ? fileAppender only : both
 */
Logger::Logger(bool clientConsole = false) : _canUseStreamAppender(!clientConsole) {
    /* We define the layout for the logger, e.g. "2016-02-10 17:58:22,255 [INFO] test" */
    log4cpp::PatternLayout *customLayout = new log4cpp::PatternLayout();
    customLayout->setConversionPattern("%d (thread : %t) [%p] %m%n");
    
    /* We define the stream appender */
    _streamAppender = new log4cpp::OstreamAppender("console", &std::cout);
    _streamAppender->setLayout(customLayout);
	_root.addAppender(_streamAppender);
    
    /* We define the file appender only if we can use it */
    if (_canUseStreamAppender) {
        _fileAppender = new log4cpp::FileAppender("file", LOGFILE);
        _fileAppender->setLayout(customLayout);
	    _root.addAppender(_fileAppender);
    }
}

/* Print an INFO message
 * Use it for log like "send login request"
 * @param message : the string to log
 */
void Logger::printInfo(std::string message) {
    _root.info(message);
}

/* Print a WARNING message
 * Use it for minor error like "no user found"
 * @param message : the string to log
 */
void Logger::printWarn(std::string message) {
    _root.warn(message);
}

/* Print an ERROR message
 * Use it for major error like "client socket close unexpectedly"
 * @param message : the string to log
 */
void Logger::printError(std::string message) {
    _root.error(message);
}

/* Print an ERROR message
 * Use it for major error like "client socket close unexpectedly"
 * @param message : the string to log
 * @param exception : exception to print
 */
void Logger::printError(std::string message, std::exception exception) {
    _root.error(message+"\n"+exception.what());
}

/* Print an FATAL message
 * Use it for fatal error like "cannot write/read the HDD"
 * @param message : the string to log
 */
void Logger::printFatal(std::string message) {
    _root.fatal(message);
}

/* Print an FATAL message
 * Use it for fatal error like "cannot write/read the HDD"
 * @param message : the string to log
 * @param exception : exception to print
 */
void Logger::printFatal(std::string message, std::exception exception) {
    _root.fatal(message+"\n"+exception.what());
}
