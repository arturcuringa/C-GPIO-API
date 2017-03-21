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


std::string shell_exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
}
std::pair<double,double> getCPUtime()
{
		std::string cmd("cat /proc/stat | grep cpu");
		std::string r;
		std::istringstream f(shell_exec(cmd.c_str()));
		getline(f,r);
		std::stringstream ss;
		ss << r;
		std::string name;
		ss >> name;
		double user, nice, system, idle;
		ss >> user >> nice >> system >> idle ;
		std::pair<double,double> x(user + nice + system,  user + nice + system + idle);
		return x;
}

int main()
{
	
	while(1)
	{
		std::pair<double, double> t1 = getCPUtime();
		//std::cout << t1.first << "!" << std::endl;
		//std::cout << t1.second << "!" << std::endl;
		sleep(1);
		std::pair<double, double> t2 = getCPUtime();
		//std::cout << t2.first << "!" << std::endl;
		//std::cout << t2.second << "!" << std::endl;
		double CPU_usage = (((t2.first - t1.first) / ( t2.second - t1.second) ) ) * 100;
		std::cout << CPU_usage << std::endl;
	}

	return 0;
}