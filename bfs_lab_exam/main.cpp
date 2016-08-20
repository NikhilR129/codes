#include <iostream>
using namespace std;

int dfs(int x,int y,int n,char **a,bool **visited)
{
    visited[x][y]=true;
    cout<<a[x][y]<<" ";
    if(y+1<n && x+1 <n)
    {
        if(a[x+1][y+1]==a[x][y]+1)
            dfs(x+1,y+1,n,a,visited);
    }
    else if(y+1<n)
    {
        if(a[x][y+1]==a[x][y]+1)
            dfs(x,y+1,n,a,visited);
    }
     else if(x+1<n)
    {
        if(a[x+1][y]==a[x][y]+1)
            dfs(x+1,y,n,a,visited);
    }

}
using namespace std;

int main()
{
   int n,i,j,starti,startj;
   cin>>n;
   char **a=new char *[n];
   for(i=0;i<n;i++)
    a[i]=new char(3);
   bool **visited=new bool *[n];
   for(i=0;i<n;i++)
    visited[i]=new bool(3);
   for(i=0;i<n;i++)
   {
       for(j=0;j<n;j++)
       {
           cin>>a[i][j];
           visited[i][j]=false;
       }
   }
   int max=dfs(0,0,n,a,visited);

}
