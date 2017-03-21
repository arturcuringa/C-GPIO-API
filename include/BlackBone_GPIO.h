#ifndef __BLACKBONEGPIO__
#define __BLACKBONEGPIO__

#include <cstdio>
#include <iostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <queue>
#include <fstream>
#include <unistd.h>
#include <algorithm>
enum GPIO{
	IN,
	OUT,
	HIGH,
	LOW

};

class BlackBone_GPIO
{
	private:
		std::string GPIO_PATH = "/sys/class/gpio/";
		std::string shell_exec(const char* cmd);
	public:
		BlackBone_GPIO(const std::string port, GPIO SIG);

		void setup(const std::string port, const GPIO Sig );
		void output(const std::string port , const GPIO Sig);
		unsigned int input(const std::string port);
};




#endif