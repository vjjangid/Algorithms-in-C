#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
}node;

node *createNode(int value);
void createSet(node **set);
void findSubSetSum(node **set,int t);
node *mergeList(node *list1,node *list2,int t);
void printSet(node *set);

int main()
{
	node *set=NULL;
	int t;
	printf("Enter the value of t:: ");
	scanf("%d",&t);
	createSet(&set);
	findSubSetSum(&set,t);
	printSet(set);
	return 0;
}

node *createNode(int value)
{
	node *temp=(node*)malloc(sizeof(node));
	temp->next=NULL;
	temp->data=value;
}
void createSet(node **set)
{
	node *start=*set;
	node *lastNode=NULL;
	int choice;
	printf("Enter the element else -1:: ");
	scanf("%d",&choice);
	while(choice!=-1)
	{
		if(start==NULL)
		{
			start=createNode(choice);
			*set=start;
			lastNode=start;
		}
		else
		{
			lastNode->next=createNode(choice);
			lastNode=lastNode->next;
		}
		printf("Enter the element else -1:: ");
		scanf("%d",&choice);
	}
}
void findSubSetSum(node **set,int t)
{
	node *inputSet=*set;
	node *list1=NULL;
	node *lastNode1=NULL;
	node *list2=NULL;
	node *lastNode2=NULL;
	node *temp=NULL; 
	int count=0;
	while(inputSet!=NULL)
	{
		if(list1==NULL)
		{
			list1=createNode(inputSet->data);
			lastNode1=list1;
		}
		else
		{
			list2=createNode(inputSet->data);
			lastNode2=list2;
			temp=list1;
			while(temp!=NULL)
			{
		
				lastNode2->next=createNode(inputSet->data + temp->data);
				lastNode2=lastNode2->next;

				temp=temp->next;
			}
			list1=mergeList(list1,list2,t);
		}
		inputSet=inputSet->next;
	}
	*set=list1;
}
node *mergeList(node *list1,node *list2,int t)
{
	node *newList=NULL;
	node *lastNode=NULL;
	while(list1!=NULL || list2!=NULL)
	{
		if(list1==NULL)
		{
			while(list2!=NULL)
			{
				if(newList==NULL && list2->data<=t)
				{
					newList=list2;
					lastNode=newList;
				}
				if(newList!=NULL && list2->data<=t)
				{
					lastNode->next=list2;
					lastNode=list2;
				}
				list2=list2->next;
			}
			//Next Line needed -- because we are creating new node so last node which have---- 
			//value less than t is still having some node adreess in its next pointer
			lastNode->next=NULL;
			break;
		}
		if(list2==NULL)
		{
			while(list1!=NULL)
			{
				if(newList==NULL && list1->data<=t)
				{
					newList=list1;
					lastNode=newList;
				}
				if(newList!=NULL && list1->data<=t)
				{
					lastNode->next=list1;
					lastNode=list1;
				}
				list1=list1->next;
			}
			//Next Line needed because we are creating new node so last node which have---- 
			//value less than t is still having some node adreess in its next pointer
			lastNode->next=NULL;
			break;
		}
		if(list1->data<list2->data)
		{
			if(list1->data<=t)
			{
				if(newList==NULL)
				{
					newList=list1;
					lastNode=list1;
				}
				else
				{
					lastNode->next=list1;
					lastNode=list1;
				}
				list1=list1->next;
			}
			else
				list1=list1->next;
		}
		else if(list1->data==list2->data)
		{
			if(list1->data<=t)
			{
				if(newList==NULL)
				{
					newList=list1;
					lastNode=list1;
				}
				else
				{
					lastNode->next=list1;
					lastNode=list1;
				}
				list1=list1->next;
				list2=list2->next;
			}
			else
			{
				list1=list1->next;
				list2=list2->next;
			}
		
		}
		else
		{
			if(list2->data<=t)
			{
				if(newList==NULL)
				{
					newList=list2;
					lastNode=list2;
				}
				else
				{
					lastNode->next=list2;
					lastNode=list2;
				}
				list2=list2->next;
			}
			else
				list2=list2->next;
		}
	}
	return newList;
}
void printSet(node *set)
{
	while(set!=NULL)
	{
		printf("%d ",set->data);
		set=set->next;
	}
	printf("\n");
}

