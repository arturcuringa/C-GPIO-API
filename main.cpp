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
#include "BlackBone_GPIO.h"

int main ()
{
	BlackBone_GPIO GPIO("50", GPIO::OUT);
	GPIO.output("50", GPIO::HIGH);

	return 0;
}