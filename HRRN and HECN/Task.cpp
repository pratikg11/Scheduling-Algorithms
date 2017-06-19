/*
 * Task.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Pratik
 */

#include<iostream>
#include<cstdlib>
#include<ctime>
#include"Task.h"

Task::Task()
{
	taskLength=0;
	total_waitingTime=0;
	waitTime=0;
	remainingLength=0;
	HRRN=0.0;
	running=false;
}
	void Task::set_remainingLength(int num)
	{
		remainingLength=num;
		taskLength=num;
	}
	int Task::get_remainingLength()
	{
		return remainingLength;
	}
	int Task::get_taskLength()
	{
		return taskLength;
	}
	void Task::set_waitTime(int wt)
	{
		waitTime=wt;
	}
	int Task::get_waitTime()
	{
		return waitTime;
	}
	int Task::get_total_waitingTime()
	{
		return total_waitingTime;
	}
	bool Task::get_runningTask()
		{
			return running;
		}
	void Task::set_runningTask(bool val)
		{
			 running=val;
		}

float Task::getHRRN()
{
	HRRN=(total_waitingTime+remainingLength)/remainingLength;
	return HRRN;
}

float Task::getHECN()
{
	HECN=(total_waitingTime+(remainingLength*energy))/(remainingLength*energy);
	return HECN;
}

void Task::set_energy(int e)
{
	energy=e;
}

int Task::get_energy()
{
	return energy;
}
void Task::decrease_waitTime()
{
	waitTime--;
}

void Task::decrease_remainingLength()
{
	remainingLength--;
}

bool Task::check_waitingTime()
{
	if(waitTime==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Task::increase_total_waitingTime()
{
	total_waitingTime++;
}
