/*
 * simulator.cpp
 *
 *  Created on: May 19, 2018
 *      Author: logsn
 */

#include <iostream>
#include "simulator.h"
#include "job.h"

//Constructor
Simulator::Simulator(int start, int mem, int dev, int time, ifstream &iFile){
	this->startTime = start;
	this->mainMem = mem;
	this->numSerialDevices = dev;
	this->timeQuantum = time;
	this->totalMainMem = mem;
	this->totalDevices = dev;
	this->file = &iFile;
	this->holdQ1 = new list<Job>();
	this->holdQ2 = new list<Job>();
	this->readyQ = new list<Job>();
	this->waitQ = new list<Job>();
	this->cpu = NULL;
	this->completeQ = new list<Job>();
	this->clock = startTime;
	this->switchTimer = 1;
}

void Simulator::run(){
	string curr;
	string charOfTime;
	int timeToStart = 0;
	while(clock < 40){


		if(timeToStart < clock){
			*file >> curr;
			*file >> charOfTime;
			timeToStart = stoi(charOfTime);
		}


		if(clock == timeToStart){
			if(curr == "A"){
				submitQueue(timeToStart);
			}else if(curr == "Q"){
				request();
				//cout << "Completed request"<<endl;
			}else if(curr == "L"){
				release();
				//cout << "Completed release"<<endl;
			}else if(curr == "D"){

			}else{
				//prob do nothing
			}
		}else{

		}

		if(cpu == NULL){
			cout << "CPU NULL AT CLOCK TIME: " << clock << endl;
			contextSwitch();
		}
		else if(switchTimer == timeQuantum){
			cout << "	CONTEXT SWITCH OCCURING";
			cout << "clock: " << clock << " timeQuantum: " << timeQuantum << "  arrivalTime: " << cpu->arrivalTime<< endl;
			contextSwitch();
		}



		clock++;
		switchTimer++;
	}
	cout << "Didn't fail in the while loop :)" <<endl;
}

//Represents the Submit Queue for accepting and rejecting potential jobs
void Simulator::submitQueue(int arrival){
	int jobNumber, memRequired, devices, runTime, priority;
	string curr;
	*file >> curr;
	jobNumber = stoi(curr.substr(2));
	*file >> curr;
	memRequired = stoi(curr.substr(2));
	*file >> curr;
	devices = stoi(curr.substr(2));
	*file >> curr;
	runTime = stoi(curr.substr(2));
	*file >> curr;
	priority = stoi(curr.substr(2));
	if(memRequired <= totalMainMem && devices <= totalDevices){
		Job *currJob = new Job(jobNumber, arrival, memRequired,devices,runTime, priority);
		cout << "Job " << jobNumber << " created" << endl; //print job created
		if(memRequired <= mainMem){
			readyQ->push_back(*currJob);
			mainMem = mainMem - currJob->memRequired;
			cout << "JOB " << jobNumber << " added to ready queue." << endl; //added to ready queue
			cout << "   Remaining main memory: " << mainMem << "." <<endl;
		}
		else{
			if(priority == 1){
				if(holdQ1->empty()){
					holdQ1->push_front(*currJob);
				}
				else{
					list<Job>::iterator it = holdQ1->begin();
					int index = 0;
					while(it->runTime < currJob->runTime){ //iterating through list to find first object with run time
						//greater than current time
						index++;
						++it;
					}
					--it;
					holdQ1->insert(it,*currJob);
				}
			}
			else {
				holdQ2->push_back(*currJob);
				cout << "Job " << jobNumber << " added to hold queue 2." << endl; //added to hq2 queue
			}
		}

	}
}

//Represents context switch for CPU every time quantum
void Simulator::contextSwitch(){
	if(!readyQ->empty()){
		if(cpu != NULL){
			cout << "   CPU NOT NULL JOB EQUALS: " << cpu->jobNumber <<endl;
			Job *tempJob = cpu;
			readyQ->push_back(*tempJob);
		}
		Job *currJob = &readyQ->front();
		readyQ->pop_front();
		cpu = currJob;
		cout << "CPU ALLOCATED TO JOB: " << cpu->jobNumber << endl;
	}
	else{
		cout << "No job currently ready to be allocated." <<endl;
	}
	switchTimer = 1;
}

//Represents a job in the CPU requesting devices
void Simulator::request(){
	int rJobNum, rDevices;
	string curr;
	*file >> curr;
	rJobNum = stoi(curr.substr(2));
	*file >> curr;
	rDevices = stoi(curr.substr(2));
	cout << rJobNum << " "<< rDevices << endl;
	if(cpu->jobNumber == rJobNum){
		cout << "CPU number matched job number " <<endl;
		if(numSerialDevices >= rDevices){
			numSerialDevices = numSerialDevices - rDevices;
			cout << "Job " << rJobNum << " successfully requested " << rDevices << "devices" <<endl;
			cout << "    " <<numSerialDevices<< " remaining." <<endl;
			readyQ->push_back(*cpu);
			cpu = NULL;
		}
		else{
			waitQ->push_back(*cpu);
			cpu = NULL;
		}
	}

}


//Represents a job in the CPU releasing devices
void Simulator::release(){
	int rJobNum, rDevices;
	string curr;
	*file >> curr;
	rJobNum = stoi(curr.substr(2));
	*file >> curr;
	rDevices = stoi(curr.substr(2));
	if(cpu->jobNumber == rJobNum){
		numSerialDevices = numSerialDevices + rDevices;
		cout << "Job " << rJobNum << " is releasing " << rDevices << "devices" <<endl;
		cout << "    " <<numSerialDevices<< " remaining." <<endl;
	}

}
