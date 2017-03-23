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
