/*
 * Task.cpp
 *
 *  Created on: Oct 9, 2016
 *      Author: Pratik
 */
#include"Task.h"
#include<iostream>
#include<time.h>
#include<cstdlib>

	Task::Task()
	{
		srand(time(0));
		task_Time=0;
		length=0;
		waitingTime=0;
		isBtw_Slice=0;
	}
	bool Task::checkSlice()
	{
		isBtw_Slice++;
		if(isBtw_Slice%20==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Task::check_waitingTime()
	{
		if(waitingTime==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Task::addTime_task()
	{
		task_Time++;
	}
	void Task::decrease_Lenght()
	{
		length--;
	}
	void Task::decrease_waitingLength()
	{
		waitingTime--;
	}
	int Task::get_taskLenght()
	{
		return length;
	}
	void Task::set_taskLength(int num)
	{
		length=num;
	}
	int Task::get_isBtw_Slice()
	{
		return isBtw_Slice;
	}
	void Task::set_isBtw_Slice(int num)
	{
		isBtw_Slice=num;
	}
	int Task::getwaitingTime()
	{
		return waitingTime;
	}
	void Task::set_waitingTime(int num)
	{
		waitingTime=num;
	}
	int Task::get_task_Time()
	{
		return task_Time;
	}


