#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
void dfs(int **graph,int source,bool visited[],int n,int count)
{
    int i,j;
    visited[source]=true;
    printf("%d ",source);
   for(i=0;i<n;i++)
        if(!visited[i] && graph[source][i]==1)
            dfs(graph,i,visited,n,count);


   /* for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",*(graph+i*n+j));
        printf("\n");
    }*/
}
int main()
{
    FILE *fp;
    int t,n,i=0,j=0,x;
    fp=fopen("input.txt","r");
    if(!fp)
        return 0;
    fscanf(fp,"%d",&t);
   // printf("%d",t);
    int mat[t][t];
    for(i=0;i<t;i++)
    {
        {
        for(j=0;j<t;j++)
            fscanf(fp,"%d",&mat[i][j]);
        }
        //fscanf(fp,"\n");
    }
    /*for(i=0;i<t;i++)
    {
        for(j=0;j<t;j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }*/
    n=t*t;
    int **graph;
    graph=malloc(sizeof(int*)*n);
    for(i=0;i<n;i++)
        graph[i]=malloc(sizeof(int)*n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            int i1=i/t;
            int i2=i%t;
            int i3=j/t;
            int i4=j%t;
            if(i==j && mat[i1][i2]==1)
            {
                graph[i][j]=1;
                continue;
            }
            //printf("%d %d %d %d\n",i1,i2,i3,i4);
            if(((abs(i1-i3) + abs(i2-i4)==1) || (abs(i1-i3)==1 && abs(i2-i4)==1)) && (mat[i1][i2]==1 && mat[i3][i4]==1))
                graph[i][j]=1;
            else
                graph[i][j]=0;

        }
    }
   /* for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",graph[i][j]);
        printf("\n");
    }*/
    bool visited[n];
    for(i=0;i<n;i++)
        visited[i]=false;
    for(i=0;i<n;i++)
        if(!visited[i] && graph[i][i])
            {
                dfs(graph,i,visited,n,0);
                printf("\n");
            }
     return 0;
}
