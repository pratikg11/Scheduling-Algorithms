/*
 * Task.h
 *
 *  Created on: Oct 19, 2016
 *      Author: Pratik
 */

#ifndef TASK_H_
#define TASK_H_

#include<iostream>
#include<cstdlib>
#include<ctime>

class Task
{
private:
	int remainingLength;
	int taskLength;
	int total_waitingTime;
	int waitTime;
	int energy;
	float HRRN;
	float HECN;
	bool running;
public:
	Task();
	void set_remainingLength(int num);
	int get_remainingLength();
	int get_taskLength();
	void set_waitTime(int wt);
	int get_waitTime();
	int get_total_waitingTime();
	bool get_runningTask();
	void set_runningTask(bool val);
	float getHRRN();
	float getHECN();
	void set_energy(int e);
	int get_energy();
	void decrease_waitTime();
	void decrease_remainingLength();
	void increase_total_waitingTime();
	bool check_waitingTime();

};


#endif /* TASK_H_ */
