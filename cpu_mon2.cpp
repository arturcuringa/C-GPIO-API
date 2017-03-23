#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>

std::pair<double,double> getCPUtime()
{
		std::fstream fs;
		fs.open("/proc/stat" ,std::fstream::in);
		std::string r;
		getline(fs,r);
		std::stringstream ss;
		ss << r;
		std::string name;
		ss >> name;
		double user, nice, system, idle;
		ss >> user >> nice >> system >> idle ;
		std::pair<double,double> x(user + nice + system,  user + nice + system + idle);
		fs.close();
		return x;
}

double getCPUusage()
{
	std::pair<double, double> t1 = getCPUtime();
	sleep(1);
	std::pair<double, double> t2 = getCPUtime();	
	return (((t2.first - t1.first) / ( t2.second - t1.second) ) ) * 100;
}

int main()
{
	
	while(1)
	{
		
		std::cout << getCPUusage() << std::endl;
	}

	return 0;
}