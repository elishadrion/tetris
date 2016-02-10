#include "Logger.hpp"

/* We create and configure a new Log4cpp instance for all the program
 * Actually, we define a file appender and a stream appender
 * But only file appender is used when we are the client (in console mode)
 * @param clientConsole : is the client in console mode ? fileAppender only : both
 */
Logger::Logger(bool clientConsole = false) : _canUseStreamAppender(!clientConsole) {
    /* We define the layout for the logger, e.g. "2016-02-10 17:58:22,255 [INFO] test" */
    log4cpp::PatternLayout *customLayout = new log4cpp::PatternLayout();
    customLayout->setConversionPattern("%d [%p] %m%n");
    
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

void Logger::printInfo(std::string message) {
    _root.info(message);
}

void Logger::printWarn(std::string message) {
    _root.warn(message);
}

void Logger::printError(std::string message) {
    _root.error(message);
}
