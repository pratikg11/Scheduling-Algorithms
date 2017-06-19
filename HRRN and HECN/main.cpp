/*
 * main.cpp
 *
 *  Created on: Oct 19, 2016
 *      Author: Pratik
 */
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"Task.h"
using namespace std;

bool getSlice_time(int i)
{
	if(i%20==0 && i!=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double getRandNo_Task()
{
	double number = (double)rand() / RAND_MAX;
	return number;
}
int getRandNo_tkLength()
{
	int number = rand()%40+10;
	return number;
}
double getRandNo_IO()
{
	double number = (double)rand() / RAND_MAX;
	return number;
}
int getRandNo_WT()
{
	int number = rand()%10+5;
	return number;
}
int getRandNo_Energy()
{
	int number = rand()%20+10;
	return number;
}
int main()
{
	int total_completedTask=0;
	int total_completedTask_HECN=0;
	int total_Energy=0;
	int total_executionTime=0;
	int total_executionTime_HECN=0;
	bool IO_Wait=false;
	srand(time(0));
	Task executingTask;
	Task executingTask_HECN;
	std::vector<Task> readyQueue;
	std::vector<Task> waitingQueue;
	std::vector<Task> readyQueue_HECN;
	std::vector<Task> waitingQueue_HECN;

	//---------------------------------------------HRRN--------------------------------------------------------------

	for(int i=0;i<1500;i++)
	{
		if(getRandNo_Task()>0.97)
		{
			Task t;
			//assigning task remaining execution time
			t.set_remainingLength(getRandNo_tkLength());
			//adding Task to ready queue
			readyQueue.push_back(t);
		}
		//assigning 1st task of ready queue to execution queue
		if(readyQueue.size()==1 && !executingTask.get_runningTask())
		{
			executingTask=readyQueue[0];
			executingTask.set_runningTask(true);
			//deleting task from ready queue as it is shifted to execution queue
			readyQueue.erase(readyQueue.begin());
		}
		//checking Input Output event
		if(getRandNo_IO()>0.97 && executingTask.get_runningTask())
		{
			IO_Wait=true;
			//executing task is stopped from execution
			executingTask.set_runningTask(false);
			//assigning waiting time
			executingTask.set_waitTime(getRandNo_WT());
		}
		//checking if slice time is completed
		if(getSlice_time(i))
		{

			if(IO_Wait)
			{
				IO_Wait=false;
				if(executingTask.get_runningTask())
				{
					//adding executing task to waiting queue
					waitingQueue.push_back(executingTask);
				}
			}
			else
			{
				if(executingTask.get_runningTask())
				{
					//adding executing task to ready queue
					readyQueue.push_back(executingTask);
				}
			}

			//Checking waiting time
			for(unsigned k=0;k<waitingQueue.size();k++)
			{
				if(waitingQueue[k].check_waitingTime())
				{
					//on completion,added to ready queue
					readyQueue.push_back(waitingQueue[k]);
					//deleting from waiting queue as it is added to ready queue
					waitingQueue.erase(waitingQueue.begin()+k);
				}
			}
			if(readyQueue.size()!=0 )
			{
				//sorting the ready queue and getting largest HRRN task
				for(unsigned l=0;l<readyQueue.size();l++)
				{
					unsigned j = l;
					while (j > 0 && readyQueue[j].getHRRN() > readyQueue[j-1].getHRRN())
					{
						Task temp = readyQueue[j];
						readyQueue[j] = readyQueue[j-1];
						readyQueue[j-1] = temp;
						j--;
					}
				}
				//assigning the largest HRRN task to executing task
				executingTask=readyQueue[0];
				executingTask.set_runningTask(true);
				//deleting the task from ready queue,as it has now become the executing task
				readyQueue.erase(readyQueue.begin());
			}
		}
		//increasing waiting time,as it is waiting due to I/O event
		if(IO_Wait)
		{
			executingTask.increase_total_waitingTime();
		}

		//increasing waiting time of tasks in waiting queue
		for(unsigned q=0;q<waitingQueue.size();q++)
		{
			waitingQueue[q].decrease_waitTime();
			waitingQueue[q].increase_total_waitingTime();
		}

		if(executingTask.get_runningTask())
		{
			if(!IO_Wait)
			{
				executingTask.decrease_remainingLength();
				//checking if task has successfully completed
				if(executingTask.get_remainingLength()==0)
				{
					total_completedTask++;
					total_executionTime=total_executionTime+(executingTask.get_taskLength()+executingTask.get_total_waitingTime());
					executingTask.set_runningTask(false);
				}
			}
		}

	}

	int Latency_HRRN=total_executionTime/total_completedTask;
			cout<<"---------------------HRRN---------------------"<<endl;
			cout<<"Number of Successful Tasks : "<<total_completedTask<<endl;
			cout<<"Total time taken by all Tasks : "<<total_executionTime<<endl;
			cout<<"System Throughput : "<<(float)total_completedTask/1500<<endl;
			cout<<"Average Latency per Task : "<<Latency_HRRN<<endl;
			cout<<"----------------------------------------------"<<endl;

			//---------------------------------------------HECN---------------------------------------------------------

			IO_Wait=false;

			for(int i=0;i<1500;i++)
				{
					if(getRandNo_Task()>0.97)
					{
						Task t;
						//assigning task remaining execution time
						t.set_remainingLength(getRandNo_tkLength());
						t.set_energy(getRandNo_Energy());
						//adding Task to ready queue
						readyQueue_HECN.push_back(t);
					}
					//assigning 1st task of ready queue to execution queue
					if(readyQueue_HECN.size()==1 && !executingTask_HECN.get_runningTask())
					{
						executingTask_HECN=readyQueue_HECN[0];
						executingTask_HECN.set_runningTask(true);
						//deleting task from ready queue as it is shifted to execution queue
						readyQueue_HECN.erase(readyQueue_HECN.begin());
					}
					//checking Input Output event
					if(getRandNo_IO()>0.97 && executingTask_HECN.get_runningTask())
					{
						IO_Wait=true;
						//executing task is stopped from execution
						executingTask_HECN.set_runningTask(false);
						//assigning waiting time
						executingTask_HECN.set_waitTime(getRandNo_WT());
					}
					//checking if slice time is completed
					if(getSlice_time(i))
					{

						if(IO_Wait)
						{
							IO_Wait=false;
							if(executingTask_HECN.get_runningTask())
							{
								//adding executing task to waiting queue
								waitingQueue_HECN.push_back(executingTask_HECN);
							}
						}
						else
						{
							if(executingTask_HECN.get_runningTask())
							{
								//adding executing task to ready queue
								readyQueue_HECN.push_back(executingTask_HECN);
							}
						}

						//Checking waiting time
						for(unsigned k=0;k<waitingQueue_HECN.size();k++)
						{
							if(waitingQueue_HECN[k].check_waitingTime())
							{
								//on completion,added to ready queue
								readyQueue_HECN.push_back(waitingQueue_HECN[k]);
								//deleting from waiting queue as it is added to ready queue
								waitingQueue_HECN.erase(waitingQueue_HECN.begin()+k);
							}
						}
						if(readyQueue_HECN.size()!=0 )
						{
							//sorting the ready queue and getting largest HRRN task
							for(unsigned l=0;l<readyQueue_HECN.size();l++)
							{
								unsigned j = l;
								while (j > 0 && readyQueue_HECN[j].getHECN() > readyQueue_HECN[j-1].getHECN())
								{
									Task temp = readyQueue_HECN[j];
									readyQueue_HECN[j] = readyQueue_HECN[j-1];
									readyQueue_HECN[j-1] = temp;
									j--;
								}
							}
							//assigning the largest HRRN task to executing task
							executingTask_HECN=readyQueue_HECN[0];
							executingTask_HECN.set_runningTask(true);
							//deleting the task from ready queue,as it has now become the executing task
							readyQueue_HECN.erase(readyQueue_HECN.begin());
						}
					}
					//increasing waiting time,as it is waiting due to I/O event
					if(IO_Wait)
					{
						executingTask_HECN.increase_total_waitingTime();
					}

					//increasing waiting time of tasks in waiting queue
					for(unsigned q=0;q<waitingQueue_HECN.size();q++)
					{
						waitingQueue_HECN[q].decrease_waitTime();
						waitingQueue_HECN[q].increase_total_waitingTime();
					}

					if(executingTask_HECN.get_runningTask())
					{
						if(!IO_Wait)
						{
							executingTask_HECN.decrease_remainingLength();
							//checking if task has successfully completed
							if(executingTask_HECN.get_remainingLength()==0)
							{
								total_completedTask_HECN++;
								total_executionTime_HECN=total_executionTime_HECN+(executingTask_HECN.get_taskLength()+executingTask_HECN.get_total_waitingTime());
								total_Energy=total_Energy+(executingTask_HECN.get_energy()*total_executionTime_HECN);
								executingTask_HECN.set_runningTask(false);
							}
						}
					}

				}

				int Latency_HECN=total_executionTime_HECN/total_completedTask_HECN;
						cout<<"---------------------HECN---------------------"<<endl;
						cout<<"Number of Successful Tasks : "<<total_completedTask_HECN<<endl;
						cout<<"Total time taken by all Tasks : "<<total_executionTime_HECN<<endl;
						cout<<"System Throughput : "<<(float)total_completedTask_HECN/1500<<endl;
						cout<<"Average Latency per Task : "<<Latency_HECN<<endl;
						cout<<"Total Energy dissipated : "<<total_Energy<<endl;
						cout<<"----------------------------------------------"<<endl;

}



