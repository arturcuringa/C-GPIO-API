#include "BlackBone_GPIO.h"

BlackBone_GPIO::BlackBone_GPIO(const std::string port, GPIO SIG)
{
	switch(SIG)
	{
		case GPIO::IN:
		{
			int n_port = stoi(port);
			chdir(GPIO_PATH.c_str());
			std::string cmd("echo " + port + " > export");
			shell_exec(cmd.c_str());
			std::string dir = GPIO_PATH + "/gpio" + port;
			chdir(dir.c_str());
			cmd = "echo in > direction";
			shell_exec(cmd.c_str());
			break;
		}	
		case GPIO::OUT:
		{
			int n_port = stoi(port);
			chdir(GPIO_PATH.c_str());
			std::string cmd("echo " + port + " > export");
			shell_exec(cmd.c_str());
			std::string dir = GPIO_PATH + "/gpio" + port;
			chdir(dir.c_str());
			cmd = "echo out > direction";
			shell_exec(cmd.c_str());
			break;
		}
		default:	
			break;
	}
	//STUB
}

void BlackBone_GPIO::setup(const std::string port, const GPIO sig )
{
	//Check if string is in correct format 
	
	//STUB
}

void BlackBone_GPIO::output(const std::string port, const GPIO SIG )
{
	std::string dir = GPIO_PATH + "/gpio" + port;
	chdir(dir.c_str());
	switch(SIG)
	{
		case GPIO::HIGH:
		{
			std::string cmd = "echo 1 > value";
			shell_exec(cmd.c_str());
			break;
		}
		case GPIO::LOW:
		{
			std::string cmd = "echo 0 > value";
			shell_exec(cmd.c_str());
			break;
		}			
	}
	std::string cmd("echo ");
}

unsigned BlackBone_GPIO::input(const std::string port)
{
	//STUB
}

std::string BlackBone_GPIO::shell_exec(const char* cmd) {
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
