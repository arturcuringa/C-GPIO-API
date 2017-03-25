ARM_COMPILER = arm-linux-gnueabihf-g++

all:
	g++ -std=c++11 -I include/ src/* cpu_mon.cpp -o main

arm:
	ARM_COMPILER -std=c++11 -I include/ src/* cpu_mon.cpp -o main

clean:
	rm main
