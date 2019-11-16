#include<stdio.h>
#include<stdlib.h>

//structure of list node
typedef struct node
{
	int data;
	int setSize;
	struct node *next;
}node;

node *newNode(int data,int setSize)
{
	node *temp=(node *)malloc(sizeof(node));
	temp->data=data;
	temp->setSize=setSize;
	temp->next=NULL;
	return temp;
}

node *addNewNode(node *list,int nodeData,int setSize)
{
	node *temp=list;
	if(list)
	{
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=newNode(nodeData,setSize);
		return list;
	}
	else
		return(newNode(nodeData,setSize));
}
node *merge(node *oldList,node *newList)
{
	if(!oldList)
		return newList;
	if(!newList)
		return oldList;
	node *head=NULL, *last=NULL, *temp=NULL;
	while(oldList && newList)
	{
		if( oldList->data < newList->data )
		{
			if(!head)
			{
				head=oldList;
			}
			else
			{
				last->next=oldList;
			}
			last=oldList;
			oldList=oldList->next;
		}
		else
		{
			if(!head)
				head=newList;
			else
				last->next=newList;
			last=newList;
			newList=newList->next;
		}
		if(oldList && oldList->data == last->data)
		{
			temp = oldList;
			oldList = oldList->next;
			free(temp);
		}
	}
	if(oldList) 
		last->next = oldList;
	if(newList) 
		last->next = newList;
	return head;	
}

node *trim(node *oldList,int delta)
{
	node *head=NULL;
	node *last=NULL;
	node *temp=NULL;
	//add first element to new list head
	head=last=oldList;
	oldList=oldList->next;
	while(oldList!=NULL)
	{
		if( oldList->data > ( last->data * ( 1 + delta) ) )
		{
			last->next=oldList;
			last=oldList;
			oldList=oldList->next;
		}
		else
		{
			temp=oldList;
			oldList=oldList->next;
			free(temp);
		}
	}
	last->next=NULL;
	return head;
}
node *createAddList(node *oldList,int element,int t)
{
	node *temp=oldList;
	node *newList=NULL;
	while(temp)
	{
		if((temp->data+element)<=t)
		{
			//if sum<=t then add that element to list with setSize and change oldList
			newList=addNewNode(newList, temp->data + element, temp->setSize+1);
		}
		temp=temp->next;
	}
	return newList;
}


node *findSubSetSum(node *oldList,int *set,int t,int noOfElem,int delta)
{
	int element=0;
	node *newList=NULL;
	for(int i=0;i<noOfElem;i++)
	{
		newList=NULL;
		element=set[i];
		//creating a list with addition of each element to previous list elements
		newList=createAddList(oldList,element,t);
		//merging of new list with old list in order
		oldList=merge(oldList,newList);
		//triming of old list using triming parameter
		oldList=trim(oldList,delta);
	}
	return oldList;
}
int main()
{
	int set[]={1,4,5,8,11};
	int t=20;
	int e=0.40; //approximation parameter
	int delta = e/10; //trimming parameter given by approximation parameter / 2n (n=set size)
	node *answer=findSubSetSum(newNode(0,0),set,t,5/*setsize*/,delta);
	while(answer)
	{
		printf("sum is %d and size of set having that sum is %d\n",answer->data,answer->setSize);
		answer=answer->next;
	}
	return 0;
}
