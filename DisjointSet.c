#include<stdio.h>
#include<stdlib.h>

struct edge{
	int u;
	int v;
};

struct graph{
	int V; //number of vertices
	int E; //number of total edges
	struct edge *edgeList;
};

struct subset{
	int parent;
	int rank;
};

struct graph *createGraph(int vertices,int edges)
{
	struct graph *myGraph=(struct graph *)malloc(sizeof(struct graph));
	myGraph->E=edges;
	myGraph->V=vertices;
	myGraph->edgeList=(struct edge *)malloc(edges * sizeof(struct edge));
	return myGraph;
}


struct graph *addEdges(struct graph *myGraph,int edges)
{
	int i,u,v;
	for(i=0;i<edges;i++)
	{
		printf("Enter the edge u ----> v :: ");
		scanf("%d %d",&u,&v);
		( myGraph -> edgeList[i] ) . u = u;
		( myGraph -> edgeList[i] ) . v = v;		
	}
	return myGraph;
}

int find(struct subset sets[],int x)
{
	if(sets[x].parent != x)
		sets[x].parent = find(sets,sets[x].parent);
	return sets[x].parent;
}

void Union(struct subset set[],int x,int y)
{
	int xRoot=find(set,x);
	int yRoot=find(set,y);
	
	if(set[xRoot].rank < set[yRoot].rank)
		set[xRoot].parent=yRoot;
	else if(set[xRoot].rank > set[yRoot].rank)
		set[yRoot].parent=xRoot;
	else
	{
		set[yRoot].parent = xRoot; 
        set[xRoot].rank++;
	}
	
}
int isCyclePresent(struct graph *myGraph)
{
	int i;
	int v=myGraph->V;
	int e=myGraph->E;
	
	struct subset *sets=(struct subset *)malloc( v * sizeof(struct subset));
	
	for(i=0;i<v;++i)
	{
		sets[i].parent=i;
		sets[i].rank=0;
	}
	for(i=0;i<e;i++)
	{
		int x=find(sets,myGraph->edgeList[i].u);
		int y=find(sets,myGraph->edgeList[i].v);
		printf("x [%d] y [%d]\n",x,y);
		if(x==y)
			return 1;
		Union(sets,x,y);
	}
	return 0;
}
int main()
{
	int vertices;
	int edges;
	struct graph *myGraph=NULL;
	
	printf("Enter the number of vertices :: ");
	scanf("%d",&vertices);
	printf("Enter the number of edges :: ");
	scanf("%d",&edges);
	
	//creating graph
	myGraph=createGraph(vertices,edges);
	
	//adding edges
	myGraph=addEdges(myGraph,edges);
	
	if(isCyclePresent(myGraph))
		printf("Cycle is present");
	else
		printf("No Cycle");
	
	return 0;
}

