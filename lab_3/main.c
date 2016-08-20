#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
	int wt;
	int nb;
	struct node *next;
};

int time=0;

typedef struct node node;

void insert_in_graph(node *head,int y,int w)
{
	node *a=(node *)malloc(sizeof(node));
	a->wt=w;
	a->nb=y;
	node *temp=head->next;
	head->next=a;
	a->next=temp;
}

void display_graph(node graph[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		node *head=(&graph[i])->next;
		while(head!=NULL)
		{
			printf("%d %d %d\n",i,head->nb,head->wt);
			head=head->next;
		}
	}
}

void print_cycle(int parent[],int start,int end)
{
	int i=start;
	while(true)
	{
		printf("%d ",i);
		if(i==end)
		{
			printf("\n");
			return;
		}
		i=parent[i];
	}

}
void dfs(node graph[],int n,int source,bool visited[],int entry[],int exit[],int colour[],int parent[])
{
	colour[source]=1;
	visited[source]=true;
	//printf("%d ",source);
	entry[source]=time++;
	node *head=(&graph[source])->next;
	while(head!=NULL)
	{
		if(!visited[head->nb])
		{
			parent[head->nb]=source;
			dfs(graph,n,head->nb,visited,entry,exit,colour,parent);
		}
		if(visited[head->nb] && colour[head->nb]==1)
		{
			;//print_cycle(parent,source,head->nb);
		}
		head=head->next;
	}
	exit[source]=time++;
	colour[source]=2;
}


void bfs(node graph[],int n,int source,bool visited[],int entry[],int exit[],int colour[],int parent[])
{
	int queue[100];
	int ctr=-1,rear=-1,top;
	rear++; ctr++;
	queue[ctr]=source;
	while(ctr<=rear)
	{
		top=queue[ctr];
		ctr++;
		if(!visited[top])
		{
			visited[top]=true;
			printf("%d ",top);
			node *head=(&graph[top])->next;
			while(head!=NULL)
			{
				if(!visited[head->nb])
				{
					rear++;
					queue[rear]=head->nb;

				}

				head=head->next;
			}
		}
	}
}

void reverse_graph(node graph[],node rev_graph[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		node *head=(&graph[i])->next;
		while(head!=NULL)
		{
			int tmp=head->nb;
			int w=head->wt;
			node *temp=malloc(sizeof(node));
			temp->nb=i;
			temp->wt=w;
			node *p=(&rev_graph[tmp])->next;
			(&rev_graph[tmp])->next=temp;
			temp->next=p;
			head=head->next;
		}
	}
	//display_graph(rev_graph,n);
}
void connected_comp(node graph[],int n,bool visited[],int entry[],int exit[],int colour[],int parent[])
{
	int i;
	for(i=0;i<n;i++)
		if(!visited[i])
			dfs(graph,n,i,visited,entry,exit,colour,parent);
	printf("\n");
	node rev_graph[n];
	for(i=0;i<n;i++)
	{
		rev_graph[i].nb=-1;
		rev_graph[i].wt=-1;
		rev_graph[i].next=NULL;
	}
	reverse_graph(graph,rev_graph,n);
	for(i=0;i<n;i++)
		visited[i]=false;
	time=0;
	while(1)
	{
		int sink_time=INT_MIN,sink=-1;
		for(i=0;i<n;i++)
		{
			if(exit[i]>sink_time && !visited[i])
			{
				sink_time=exit[i];
				sink=i;
			}

		}
		if(sink==-1)
			break;
		dfs(rev_graph,n,sink,visited,entry,exit,colour,parent);
		printf("\n");
	}
}
void floyd_warshall(node graph[],int n)
{
    int i,j,k;
    int **a=malloc(sizeof(int *)*n);
    for(i=0;i<n;i++)
        a[i]=malloc(sizeof(int )*n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(i==j)
                a[i][j]=0;
            else
                a[i][j]=100000;
        }
    for(i=0;i<n;i++)
    {
        node *head=(&graph[i])->next;
        while(head!=NULL)
        {
            a[i][head->nb]=head->wt;
            head=head->next;
        }
    }

    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(a[i][k]+a[k][j]<a[i][j])
                    a[i][j]=a[i][k]+a[k][j];
            }
        }
    }
}
int main()
{
	int x,y,w,n,i;
	FILE *fp;
	fp=fopen("input.txt","r");
	if(!fp)
		return 0;
	fscanf(fp,"%d\n",&n);
	node graph[n];

	for(i=0;i<n;i++)
	{
		graph[i].wt=-1;
		graph[i].nb=-1;
		graph[i].next=NULL;
	}

	while(fscanf(fp,"%d %d %d\n",&x,&y,&w)!=EOF)
	{
		insert_in_graph(&graph[x],y,w);
	}

	int entry[n],exit[n],colour[n],parent[n];
	bool visited[n];
	for(i=0;i<n;i++)
	{
		visited[i]=false;
		colour[i]=0;
		parent[i]=i;
	}
	return 0;

}
