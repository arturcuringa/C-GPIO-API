#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unistd.h>
#include "BlackBone_GPIO.h"
#include "CPU_utility.h"
#include <algorithm> 
#include <signal.h>


int main()
{
	BlackBone_GPIO _GPIO;
	_GPIO.setup("P9_12", GPIO::OUT);
	_GPIO.setup("P9_14", GPIO::OUT);
	_GPIO.setup("P9_16", GPIO::OUT);
	_GPIO.setup("P9_27", GPIO::IN);
	while(1)
	{
		double CPU_usage = getCPUusage();

		if(CPU_usage < 25.0)
		{
			_GPIO.output("P9_12", GPIO::HIGH);
			_GPIO.output("P9_14", GPIO::LOW);
			_GPIO.output("P9_16", GPIO::LOW);
			
		}
		else if(CPU_usage < 50.0)
		{
			_GPIO.output("P9_12", GPIO::LOW);
			_GPIO.output("P9_14", GPIO::HIGH);
			_GPIO.output("P9_16", GPIO::LOW);
			
		}
		else if(CPU_usage < 75.0)
		{
			_GPIO.output("P9_12", GPIO::LOW);
			_GPIO.output("P9_14", GPIO::LOW);
			_GPIO.output("P9_16", GPIO::HIGH);
			
		}else
		{
			_GPIO.output("P9_12", GPIO::HIGH);
			_GPIO.output("P9_14", GPIO::HIGH);
			_GPIO.output("P9_16", GPIO::HIGH);
			
			if(_GPIO.input("P9_27"))
			{
				std::string p = biggestCPUusage(); 
				std::cout<< p << std:;endl;
				kill(stoi(p),SIGQUIT);
			}
			else
				sleep(1);
			_GPIO.output("P9_12", GPIO::LOW);
			_GPIO.output("P9_14", GPIO::LOW);
			_GPIO.output("P9_16", GPIO::LOW);
		}
	}

	return 0;
}