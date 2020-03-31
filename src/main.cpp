#include <iostream>
#include "util/Logger.h"
LOGGER::CLogger logger(LOGGER::LogLevel_Info, LOGGER::CLogger::GetAppAbsolutePath().append("log\\"));

int main(int argc, char *argv[])
{
    std::cout << "news block chain" << std::endl;
    logger.traceInfo("News Block Chain Inited");
    return 0;
}
