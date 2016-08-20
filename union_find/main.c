#include <stdio.h>
#include <stdlib.h>

int find(int parent[],int x)
{
    int p=x;
    while(x!=parent[x])
        x=parent[x];
    parent[p]=x;
    return x;
}
void union_(int parent[],int x,int y)
{
    int p1=find(parent,x);
    int p2=find(parent,y);
    parent[p1]=p2;
}
void initialize(int parent[],int n)
{
    int i;
    for(i=0;i<n;i++)
        parent[i]=i;
}
void display(int parent[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",parent[i]);

    printf("\n");
}
int main()
{
    int n,i,x,y;
    FILE *fp=fopen("input.txt","r");
    if(!fp)
        return 0;
    fscanf(fp,"%d",&n);
    int parent[n];
    initialize(parent,n);
    while(fscanf(fp,"%d %d",&x,&y)!=EOF)
        union_(parent,x,y);

    display(parent,n);
}
