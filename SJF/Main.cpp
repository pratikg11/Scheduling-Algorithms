/*
 * Main.cpp
 *
 *  Created on: Oct 9, 2016
 *      Author: Pratik
 */


#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include"Task.h"
using namespace std;

double getRandNo_Task()
{
	double number = (double)rand() / RAND_MAX;
	return number;
}
double getRandNo_IO()
{
	double number = (double)rand() / RAND_MAX;
	return number;
}
int getRandNo_WT()
{
	int number = rand()%30+10;
	return number;
}
int getRandNo_tkLength()
{
	int number = rand()%50+10;
	return number;
}
int main()
{
	srand(time(0));
	int total_successfulTasks,total_taskTime=0;
	Task t_Slice;
	bool Is_btwSlice=false;

	//Creating Vector of Tasks
	std::vector<Task> tasks_List;
	std::vector<Task> waitingQueue;
	for(int i=0;i<1500;i++)
	{
		//Checking if random no greater than 0.95
		if(getRandNo_Task()>0.95)
			{
				Task t;
				t.set_taskLength(getRandNo_tkLength());
				//adding Task to Vector
				tasks_List.push_back(t);
			}
		if(tasks_List.size()!=0)
		{
			//Checking if task has completed Operating System Slice Time
			if(Is_btwSlice)
			{
				t_Slice.addTime_task();
				//Checks if slice time is complete
				if(t_Slice.checkSlice())
				{
					t_Slice.set_isBtw_Slice(0);
					//random number for waiting length
					t_Slice.set_waitingTime(getRandNo_WT());
					//On Completing Operating System Slice Time,the task is added to waiting queue
					waitingQueue.push_back(t_Slice);
					Is_btwSlice=false;
				}
			}
			else
			{
				//Checks Every Element in waiting Queue
				for(unsigned k=0;k<waitingQueue.size();k++)
					{
						waitingQueue[k].decrease_waitingLength();
						if(waitingQueue[k].check_waitingTime())
						{
							//if Waiting time is completed it is added again to Execution Queue
							tasks_List.push_back(waitingQueue[k]);
						}
					}

				//Sorting the Execution Queue for finding the smallest Task
					for(unsigned l=0;l<tasks_List.size();l++)
						{
						unsigned j = l;
								while (j > 0 && tasks_List[j].get_taskLenght() < tasks_List[j-1].get_taskLenght())
								{
									Task temp = tasks_List[j];
									tasks_List[j] = tasks_List[j-1];
									tasks_List[j-1] = temp;
									j--;
								}
						}

					//Checks if there is any IO event
					if(getRandNo_IO()>0.95)
					{
						t_Slice=tasks_List[0];
						Is_btwSlice=true;
						t_Slice.addTime_task();
						t_Slice.set_isBtw_Slice(i);
						//Removes the task from Execution Queue
						for(unsigned q=0;q<tasks_List.size()-1;q++)
						{
							tasks_List[q]=tasks_List[q+1];
						}
					}
					else
					{
						tasks_List[0].addTime_task();
						tasks_List[0].decrease_Lenght();
					}


			}
			//Checks if task has completed its execution
			if(tasks_List[0].get_taskLenght()==0)
			{
				total_successfulTasks++;
				total_taskTime=total_taskTime+tasks_List[0].get_task_Time();
				//Removes the task from Execution Queue
				for(unsigned p=0;p<tasks_List.size()-1;p++)
					{
						tasks_List[p]=tasks_List[p+1];
					}
			}
		}

	}
	int Latency=total_taskTime/total_successfulTasks;
	cout<<"Number of Successful Tasks : "<<total_successfulTasks<<endl;
	cout<<"Total time taken by all Tasks : "<<total_taskTime<<endl;
	cout<<"System Throughput : "<<(float)total_successfulTasks/1500<<endl;
	cout<<"Average Latency per Task : "<<Latency;

}



