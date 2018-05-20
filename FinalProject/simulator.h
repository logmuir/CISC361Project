/*
 * simulator.h
 *
 *  Created on: May 19, 2018
 *      Author: logsn
 */


#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <fstream>
#include <list>
#include "job.h"
using namespace std;

class Simulator{

public:

	//System Configuration
	int startTime;
	int mainMem;
	int numSerialDevices;
	int timeQuantum;
	int totalMainMem;
	int totalDevices;
	int clock;
	int switchTimer;
	ifstream *file;

	//queue lists
	list<Job> *holdQ1;
	list<Job> *holdQ2;
	list<Job> *readyQ;
	list<Job> *waitQ;
	Job *cpu;
	list<Job> *completeQ;

	//constructor
	Simulator(int start, int mem, int dev, int time, ifstream &iFile);

	//methods
	void submitQueue(int arrival);
	void contextSwitch();
	void request();
	void release();
	void run();


};



#endif /* SIMULATOR_H_ */
