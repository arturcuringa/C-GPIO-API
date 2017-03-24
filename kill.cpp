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
            	return stoi(std::string(entity->d_name)) > 100 ;
        }
    }return false;
}
double abs(double x1)
{
	if(x1 < 0)
		return -1 * x1;
	return x1;
}

/*------------------------------*/
struct Process
{
	std::string pid;
	int info;
	double total;
};

bool comp(Process a, Process b){
	return a.total > b.total;
}

std::pair<int,int> getCPUtime()
{
		std::fstream fs;
		fs.open("/proc/stat" ,std::fstream::in);
		std::string r;
		getline(fs,r);
		std::stringstream ss;
		ss << r;
		std::string name;
		ss >> name;
		int user, nice, system, idle;
		ss >> user >> nice >> system >> idle ;
		std::pair<int,int> x(user + nice + system,  user + nice + system + idle);
		fs.close();
		return x;
}

int diffCPUtime(std::pair<int,int>t1 ,std::pair<int,int> t2 ){
	return  ( t2.second - t1.second);
}

int getProcessCPUusage(std::string pid)
{
	std::fstream fs;
	std::string input;
	std::stringstream ss;
	fs.open("/proc/"+std::string(pid)+std::string("/stat") ,std::fstream::in);
	getline(fs,input);
	
	ss << input;
	
	int utime = 0, stime = 0;
	for(int i=0; ss>>input; ++i){
		std::cout << "!!!!" << input << "!!!";
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
	std::cout<<"\n";
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
	std::pair<double, double> t1 = getCPUtime();

	if((dp = opendir(dirToOpen.c_str())) != NULL){
		while((d = readdir(dp)) != NULL){
			if(ProcessEntity(d)){	
				p.pid=std::string(d->d_name);
				p.info = getProcessCPUusage(std::string(d->d_name));
				processes.push_back(p);

			}
		}
	}else{
		std::cout<<"ERROR /PROC"<<std::endl;
		return "-1";
	}
	sleep(1);

	std::pair<double, double> t2 = getCPUtime();	
	
	if((dp = opendir(dirToOpen.c_str())) != NULL){
		for(int i=0; i<processes.size(); ++i){
			if((d = readdir(dp)) != NULL){

				processes[i].total= 100*( std::abs(getProcessCPUusage(std::string(d->d_name)) - processes[i].info) / 
									std::abs( diffCPUtime(t1,t2) ) );
				
				std::cout<<processes[i].pid<<":  "<<processes[i].total<<std::endl;
			}else{
				processes[i].total=0;
			}
		}
	}
	std::sort(processes.begin(),processes.end(),comp);
	// std::cout<<"----------------------"<<std::endl;
	// for(int i=0; i<processes.size(); ++i){
	// 	if(processes[i].pid ==  "7187")
	// 		std::cout << "CARAI " << processes[i].total <<std::endl; 
	// 	std::cout<<processes[i].pid<<":  "<<processes[i].total<<std::endl;
	// }
	// // std::cout<<"----------------------"<<std::endl;
	// std::cout<<"----------------------"<<std::endl;
	// std::cout<<"----------------------"<<std::endl;
	// std::cout<<processes[0].pid<<":  "<<processes[0].total<<std::endl;
	return (processes.empty() ? "-1": processes[0].pid);
}

int main(void){
	std::string p= biggestCPUusage();
	std::cout<< "KILLING PROCESS: "<<stoi(p)<<std::endl;
	kill(stoi(p),SIGQUIT);
	return 0;
}
