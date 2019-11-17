#include<stdio.h>
#include<stdlib.h>

//structure of jobs
typedef struct job{
	int job_id;
	int job_load;
}job;

//structure of machine
typedef struct machine{
	int mach_id;
	int mach_load;
}machine;

									//merge sort logic

void merge(job *jobs,int start,int mid,int k,int end)
{
	job *aux=(job *)malloc((end-start)*sizeof(job)); // auxillary array for outplace algo
	int i=start;
	int l=0;
	
	while(	i<=mid && k<=end )  //inserting elements in order
	{
		if( jobs[i].job_load > jobs[k].job_load)
		{
			aux[l].job_id=jobs[i].job_id;
			aux[l].job_load=jobs[i].job_load;
			i++;
		}
		else
		{
			aux[l].job_id=jobs[k].job_id;
			aux[l].job_load=jobs[k].job_load;
			k++;
		}
		l++;
	}
	
	//inserting left elements
	while(i<=mid)
	{
		aux[l].job_id=jobs[i].job_id;
		aux[l].job_load=jobs[i].job_load;
		i++;
		l++;
	}
	while(k<=end)
	{
		aux[l].job_id=jobs[k].job_id;
		aux[l].job_load=jobs[k].job_load;
		k++;
		i++;
	}
	
	//inserting back all jobs after ordering in real job array
	for(i=0;start<=end;start++)
	{
		jobs[start]=aux[i++];
	}
}	

void mergeSort(job *jobs,int start,int end)
{
	if(start<end)
	{
		int mid = (start+end) / 2;
		mergeSort(jobs,start,mid);
		mergeSort(jobs,mid+1,end);
		merge(jobs,start,mid,mid+1,end);
	}
}

								//Min heap logic

void heapify(machine *mach,int heapSize,int i)
{
	int left = 2*i + 1;
	int right = 2*i + 2;
	
	int minIndex;
	machine temp;
	if(left<=heapSize && mach[i].mach_load>mach[left].mach_load)
	{
		minIndex=left;
	}
	else
	{
		minIndex = i;
	}
	if(right<=heapSize && mach[i].mach_load>mach[right].mach_load)
	{
		minIndex=right;
	}
	if( minIndex != i )
	{
		temp=mach[i];
		mach[i]=mach[minIndex];
		mach[minIndex]=temp;
		heapify(mach,heapSize,minIndex);
	}
}

int main()
{
	job jobs[]={{1,3},{2,3},{3,2},{4,3},{5,3},{6,3},{7,3},{8,3},{9,15}}; //jobs array
	machine mach_heap[]={{1,0},{2,0},{3,0},{4,0}};  //machine array
	
	int n=sizeof(jobs)/sizeof(job); //number of jobs
	int m=sizeof(mach_heap)/sizeof(machine); //number of machines
	
	//sorting of jobs in descending order
	mergeSort(jobs,0,n-1);
	
	//assigning of jobs to machine
	machine temp;
	for(int i=0;i<n;i++)
	{
		heapify(mach_heap,4,0);
		//after heapify we will get min at top always
		mach_heap[0].mach_load += jobs[i].job_load;
		temp=mach_heap[0]; //in min heap every time min is at top
		printf("job id [%d]   job load[%d] --> assigned to ---> machine id [%d]  machine load [%d] \n" ,jobs[i].job_id,jobs[i].job_load,temp.mach_id,temp.mach_load);
		//increase load on machine
		
		//rearrange heap*/
		
		
	}
	
	return 0;
}
