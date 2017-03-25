## BLack Bone C++ API

This a C++ API to control BeagleBone's GPIO and a CPU monitoring system as a exemple of use.
The API is based on Adafruit Python API and can be used to:**setup**, **output**, **input**.
The exemplle use the **CPU_utility** for reading **/proc/stat** and calculates the CPU usagem in porcentage, for sinalize with leds controled by the Black Bone. In case that CPU usage is bigger than **75%** the user can press a button to **kill** the process with the most CPU usage, got by the **/proc/<PID>/stat**.

## Installation

	 No need for extra packages, only **stress** and **cpulimit** if the user want to simulate de CPU load.


## Example of use

```
#include "BlackBone_GPIO.h"

int main ()
{
	BlackBone_GPIO _GPIO;
	_GPIO.setup("50", GPIO::OUT);
	_GPIO.output("50", GPIO::HIGH);
	_GPIO.setup("115", GPIO::IN);
	while(1)
	{
		std::cout << _GPIO.input("115") << std::endl;
	}
	return 0;
}

```

