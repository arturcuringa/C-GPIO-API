#include "BlackBone_GPIO.h"


BlackBone_GPIO::BlackBone_GPIO()
{

}

void BlackBone_GPIO::setup(const std::string port, const GPIO SIG )
{
    //Check if string is in correct format
 	if(SIG == GPIO::IN || SIG == GPIO::OUT )
    {
    		int n_port = stoi(port);
            //chdir(GPIO_PATH.c_str());
            std::string  folderr;
            folderr = GPIO_PATH + "/gpio" + port;
            struct stat sb;
            //std::string cmd;
            if(!(stat(folderr.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) ))
            {
            		std::fstream fs;
            		fs.open(GPIO_PATH + "/export" ,std::fstream::in | std::fstream::out | std::fstream::app);
                    fs << port;
                    //cmd = "echo " + port + " > export";
                    //std::cout<< cmd <<std::endl;
                    //shell_exec(cmd.c_str());
            		fs.close();
            }
            std::string dir = GPIO_PATH + "/gpio" + port;
            std::fstream fs;
            fs.open(dir + "/direction" ,std::fstream::in | std::fstream::out | std::fstream::app);
            
            if(SIG ==  GPIO::IN)
            {
                fs << "in";
            }
            else if(SIG ==  GPIO::OUT)
            {               
                fs << "out";
            }
            fs.close();
    }
}

void BlackBone_GPIO::output(const std::string port, const GPIO SIG )
{
        std::string dir = GPIO_PATH + "/gpio" + port;
       // chdir(dir.c_str());
    	std::fstream fs;
        switch(SIG)
        {
        	fs.open(dir + "/value" ,std::fstream::in | std::fstream::out | std::fstream::app);
            case GPIO::HIGH:
            {
        		                    
                fs << 1;

            }
            case GPIO::LOW:
            {
                fs << 0;
           	}
            fs.close();
        }
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

// BlackBone_GPIO::const_aux(std::string cmd){
// 		int n_port = stoi(port);
//                 chdir(GPIO_PATH.c_str());
//                 std::string  folderr;
//                 folderr = "/gpio" + port;
//                 struct stat sb;
//                 std::string cmd;
//                 if(!(stat(folderr.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode) ))
//                 {
//                 	cmd = "echo " + port + " > export";
//                         std::cout<< cmd <<std::endl;
//                         shell_exec(cmd.c_str());
//                 }
//                 std::string dir = GPIO_PATH + "/gpio" + port;
//                 chdir(dir.c_str());
//                 cmd = "echo in > direction";
//                 shell_exec(cmd.c_str());
//                  break;
// }

