#include<stdio.h>
#include<stdlib.h>
#define MAX 20
#define TRUE 1
#define FALSE 0
typedef struct node
{
	int data;
	struct node *next;
}node;
node *(verPtr[MAX]);
int visited[MAX]={};

node * newNode(int vertex);
void createGraph();
void findVertexCover();

int main()
{
	createGraph();
	findVertexCover();
}
node * newNode(int vertex)
{
	node *temp=(node *)malloc(sizeof(node));
	temp->data=vertex;
	temp->next=NULL;
	return temp;
}
void createGraph()
{
	int vertices;
	printf("Enter the number of vertices you want to have:: ");
	scanf("%d",&vertices);
	node *lastNode=NULL;
	int i;
	int j=0;
	int choice;
	for(i=0;i<MAX;i++)
		verPtr[i]=NULL;
	for(i=0;i<vertices;i++)
	{
		while(j < vertices)
		{
			if(i==j)
			{
				j++;
				continue;
			}	
			printf("Does %d have edge to %d Press 1 if yes else 0:: ",i,j);
			scanf("%d",&choice);
			if(choice==1)
			{
				if(verPtr[i]==NULL)
				{
					verPtr[i]=newNode(j);
					lastNode=verPtr[i];
				}
				else
				{
					lastNode->next=newNode(j);
					lastNode=lastNode->next;
				}
			}
			j++;
		}
		j=0;
	}
}
void findVertexCover()
{
	int u=0;
	node *edge=NULL;
	for(u=0;u<6;u++)
	{
		if(visited[u]==FALSE)
		{
			edge=verPtr[u];
			//go to first edge which is not visited
			while(edge && visited[edge->data]==TRUE) 
				edge=edge->next;
			//if there exist such edge make it visited
			if(edge)
			{
				visited[u]=TRUE;
				visited[edge->data]=TRUE;	
			}	
		}
	}
	printf("The vertex cover for given graph is:: ");
	for(u=0;u<MAX;u++)
	{
		if(visited[u]==TRUE)
			printf("%d ",u);
	}
}
