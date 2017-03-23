#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "BlackBone_GPIO.h"


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
	BlackBone_GPIO _GPIO;
	_GPIO.setup("60", GPIO::OUT);
	_GPIO.setup("50", GPIO::OUT);
	_GPIO.setup("51", GPIO::OUT);

	while(1)
	{
		double CPU_usage = getCPUusage();

		if(CPU_usage < 25.0)
		{
			_GPIO.output("60", GPIO::HIGH);
			_GPIO.output("50", GPIO::LOW);
			_GPIO.output("51", GPIO::LOW);
			
		}
		else if(CPU_usage < 50.0)
		{
			_GPIO.output("60", GPIO::LOW);
			_GPIO.output("50", GPIO::HIGH);
			_GPIO.output("51", GPIO::LOW);
			
		}
		else if(CPU_usage < 75.0)
		{
			_GPIO.output("60", GPIO::LOW);
			_GPIO.output("50", GPIO::LOW);
			_GPIO.output("51", GPIO::HIGH);
			
		}else
		{
			_GPIO.output("60", GPIO::HIGH);
			_GPIO.output("50", GPIO::HIGH);
			_GPIO.output("51", GPIO::HIGH);
			sleep(1);
			_GPIO.output("60", GPIO::LOW);
			_GPIO.output("50", GPIO::LOW);
			_GPIO.output("51", GPIO::LOW);
		}
	}

	return 0;
}