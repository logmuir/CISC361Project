/*
 * job.cpp
 *
 *  Created on: May 19, 2018
 *      Author: logsn
 */


#include "job.h"

Job::Job(int jobNum, int arrival, int mem, int dev, int runt, int p){
	this->jobNumber = jobNum;
	this->arrivalTime = arrival;
	this->memRequired = mem;
	this->devices = dev;
	this->runTime = runt;
	this->priority = p;
}
