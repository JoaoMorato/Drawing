#ifndef _CONFIGFILE_
#pragma once

#include <sstream>

class Configuration {
private:
	std::string nameProject;
public:
	Configuration(std::string);

};

class Tab {
public:
	unsigned int id = 0;
	unsigned short width = 0;
	unsigned short height;
	std::string dir;
};


#endif // !_CONFIGFILE_