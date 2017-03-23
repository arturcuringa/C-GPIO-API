#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <algorithm> 

bool is_number(const std::string& s){
    std::string::const_iterator it = s.begin();
    	while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool ProcessEntity(struct dirent* entity){
    if(entity->d_type == DT_DIR){
        if(entity->d_name[0] != '.'){
            if(is_number(std::string(entity->d_name)))
            	return stoi(std::string(entity->d_name)) > 10000 ;
        }
    }return false;
}

/*------------------------------*/
struct Process
{
	std::string pid;
	double info;
	std::pair<double,double> cpu;
	double total;
};

bool comp(Process a, Process b){
	return a.total > b.total;
}

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

double diffCPUtime(std::pair<double,double>t1 ,std::pair<double,double> t2 ){
	return (((t2.first - t1.first) / ( t2.second - t1.second)));
}

int getProcessCPUusage(std::string pid)
{
	std::fstream fs;
	std::string input;
	std::stringstream ss;
	fs.open("/proc/"+std::string(pid)+std::string("/stat") ,std::fstream::in);
	getline(fs,input);
	
	ss << input;
	
	int utime, stime;
	for(int i=0; ss>>input; ++i){
		if(i>12){
			std::stringstream ss2(input);
			if(i==13){
				ss2>>utime;
			}else if(i==14){
				ss2>>stime;
				break;
			}
		}
	}
	fs.close();
	std::cout<<utime << "   "<<stime<<std::endl;
	return (utime + stime);;
}

std::string biggestCPUusage(){
	std::string dirToOpen = "/proc";
	std::vector<Process> processes;
 	
	dirent *d;
	DIR *dp;

	Process p;

	if((dp = opendir(dirToOpen.c_str())) != NULL){
		while((d = readdir(dp)) != NULL){
			if(ProcessEntity(d)){	
				p.pid=std::string(d->d_name);
				p.info=getProcessCPUusage(std::string(d->d_name));
				p.cpu=getCPUtime();

				processes.push_back(p);
			}
		}
	}else{
		std::cout<<"ERROR /PROC"<<std::endl;
		return "-1";
	}

	if((dp = opendir(dirToOpen.c_str())) != NULL){
		for(int i=0; i<processes.size(); ++i){
			if((d = readdir(dp)) != NULL){
				processes[i].total= 100*(std::abs(getProcessCPUusage(std::string(d->d_name)) - processes[i].info) / 
									std::abs(diffCPUtime(p.cpu,getCPUtime())));
				
				std::cout<<processes[i].pid<<":  "<<processes[i].total<<std::endl;
			}else{
				processes[i].total=0;
			}
		}
	}
	std::sort(processes.begin(),processes.end(),comp);
	std::cout<<"----------------------"<<std::endl;
	for(int i=0; i<processes.size(); ++i){
		std::cout<<processes[i].pid<<":  "<<processes[i].total<<std::endl;
	}
	std::cout<<"----------------------"<<std::endl;
	std::cout<<"----------------------"<<std::endl;
	std::cout<<"----------------------"<<std::endl;
	std::cout<<processes[0].pid<<":  "<<processes[0].total<<std::endl;
	return (processes.empty() ? "-1": processes[0].pid);
}

int main(void){
	std::string p= biggestCPUusage();
	std::cout<< "KILLING PROCESS: "<<stoi(p)<<std::endl;
	//kill(stoi(p),SIGQUIT);
	return 0;
}
