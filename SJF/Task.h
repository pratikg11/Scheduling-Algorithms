/*
 * Task.h
 *
 *  Created on: Oct 8, 2016
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
		int task_Time;
		int length;
		int waitingTime;
		int isBtw_Slice;

public :

		Task();
		bool checkSlice();
		bool check_waitingTime();
		void addTime_task();
		void decrease_Lenght();
		void decrease_waitingLength();
		int get_taskLenght();
		void set_taskLength(int num);
		int get_isBtw_Slice();
		void set_isBtw_Slice(int num);
		int getwaitingTime();
		void set_waitingTime(int num);
		int get_task_Time();
};



#endif /* TASK_H_ */
