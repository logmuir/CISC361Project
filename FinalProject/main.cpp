/*
 * main.cpp
 *
 *  Created on: May 19, 2018
 *      Author: logsn
 */

#include <iostream>
#include <fstream>
#include "simulator.h"
using namespace std;

int main(){


	//initialization
	cout << "Starting..." << endl;
	int startTime;
	int mainMem;
	int numSerialDevices;
	int timeQuantum;

	//reading file
	string line;
	ifstream inputFile;
	inputFile.open("input.txt");
	string curr;
	inputFile >> curr;
	if(curr == "C"){
		inputFile >> curr;
		startTime = stoi(curr);
		inputFile >> curr;
		mainMem = stoi(curr.substr(2));
		inputFile >> curr;
		numSerialDevices = stoi(curr.substr(2));
		inputFile >> curr;
		timeQuantum = stoi(curr.substr(2));
		Simulator *OS_sim = new Simulator(startTime,mainMem,numSerialDevices,timeQuantum, inputFile);
		OS_sim->run();
	}
	else{
		cout << "Improper input file!" << endl;
	}

	return 0;
}
