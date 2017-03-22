#include "BlackBone_GPIO.h"

BlackBone_GPIO::BlackBone_GPIO(const std::string port, GPIO SIG)
{
        switch(SIG)
        {
                case GPIO::IN:
                {
                        int n_port = stoi(port);
                        chdir(GPIO_PATH.c_str());
                        std::string  folderr;
                        folderr = "/gpio" + port;
                        struct stat sb;
                        std::string cmd;
                        if(!(stat(folderr.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) ))
                        {
                                cmd = "echo " + port + " > export";
                                std::cout<< cmd <<std::endl;
                                shell_exec(cmd.c_str());
                        }
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
                        std::string  folderr;
                        folderr = GPIO_PATH +"/gpio" + port;
                        struct stat sb;
                        std::string cmd;
                        if(!(stat(folderr.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) ))
                        {
                                cmd = "echo " + port + " > export";
                                std::cout<< cmd << std::endl;
                                shell_exec(cmd.c_str());
                        }
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


std::map<std::string, std::string> GPIOSystem::pinToIO = {
	{"P9_11", "gpio30"},
	{"P9_12", "gpio60"},
	{"P9_13", "gpio31"},
	{"P9_14", "gpio50"},
	{"P9_15", "gpio48"},
	{"P9_16", "gpio51"},
	{"P9_17", "gpio5"},
	{"P9_18", "gpio4"},
	{"P9_21", "gpio3"},
	{"P9_22", "gpio2"},
	{"P9_23", "gpio49"},
	{"P9_25", "gpio117"},
	{"P9_26", "gpio14"},
	{"P9_27", "gpio115"},
	{"P9_28", "gpio113"},
	{"P9_29", "gpio111"},
	{"P9_30", "gpio112"},
	{"P9_31", "gpio110"},
	{"P9_41", "gpio20"},
	{"P9_42", "gpio7"},
	{"P8_03", "gpio38"},
	{"P8_04", "gpio39"},
	{"P8_05", "gpio34"},
	{"P8_06", "gpio35"},
	{"P8_07", "gpio66"},
	{"P8_08", "gpio67"},
	{"P8_09", "gpio69"},
	{"P8_10", "gpio68"},
	{"P8_11", "gpio45"},
	{"P8_12", "gpio44"},
	{"P8_13", "gpio23"},
	{"P8_14", "gpio26"},
	{"P8_15", "gpio47"},
	{"P8_16", "gpio46"},
	{"P8_17", "gpio27"},
	{"P8_18", "gpio65"},
	{"P8_19", "gpio22"},
	{"P8_20", "gpio63"},
	{"P8_21", "gpio62"},
	{"P8_22", "gpio37"},
	{"P8_23", "gpio36"},
	{"P8_24", "gpio33"},
	{"P8_25", "gpio32"},
	{"P8_26", "gpio61"},
	{"P8_27", "gpio86"},
	{"P8_28", "gpio88"},
	{"P8_29", "gpio87"},
	{"P8_30", "gpio89"},
	{"P8_31", "gpio10"},
	{"P8_32", "gpio11"},
	{"P8_33", "gpio9"},
	{"P8_34", "gpio81"},
	{"P8_35", "gpio8"},
	{"P8_36", "gpio80"},
	{"P8_37", "gpio78"},
	{"P8_38", "gpio79"},
	{"P8_39", "gpio76"},
	{"P8_40", "gpio77"},
	{"P8_41", "gpio74"},
	{"P8_42", "gpio75"},
	{"P8_43", "gpio72"},
	{"P8_44", "gpio73"},
	{"P8_45", "gpio70"},
	{"P8_46", "gpio71"}
};
