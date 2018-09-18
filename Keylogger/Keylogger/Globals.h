#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <string>
#include <Windows.h>

class GlobalResources {
public:
	static std::string LOGFILE_NAME;
};

std::string GlobalResources::LOGFILE_NAME = "";

#endif	//_GLOBALS_H_