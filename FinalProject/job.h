/*
 * job.h
 *
 *  Created on: May 19, 2018
 *      Author: logsn
 */

#ifndef JOB_H_
#define JOB_H_

class Job{

public:
	//A in the text file starts the job
	int jobNumber;
	int arrivalTime;
	int memRequired;
	int devices;
	int runTime;
	int priority;
	Job(int jobNum, int arrival, int mem, int dev, int runt, int p);
};



#endif /* JOB_H_ */
