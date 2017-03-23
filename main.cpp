#include "BlackBone_GPIO.h"

int main ()
{
	BlackBone_GPIO GPIO;
	GPIO.setup("50", GPIO::OUT);
	GPIO.output("50", GPIO::HIGH);

	return 0;
}
