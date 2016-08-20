#include <stdio.h>
#include <stdlib.h>

struct point
{
    int x;
    int y;
};
struct point p0;

typedef struct point point;

int distSq(point p1, point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(point p, point q, point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2)
{
   point *p1 = (point *)vp1;
   point *p2 = (point *)vp2;

   // Find orientation
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

point *convex_hull(point p[],int n)
{
    qsort(&p[1],n-1,sizeof(point),compare);
    point *hull=malloc(sizeof(point)*(n+1));
    int cnt=2,i;

    int m = 1; // Initialize size of modified array
   for (i=1; i<n; i++)
   {
       // Keep removing i while angle of i and i+1 is same
       // with respect to p0
       while (i < n-1 && orientation(p0, p[i],p[i+1]) == 0)
          i++;

       p[m] = p[i];
       m++;  // Update size of modified array
   }
   if(m<=3)
    {
        for(i=0;i<m;i++)
            {
                hull[i]=p[i];
            }
            hull[i].x=-1;
    return hull;
    }

    hull[0]=p[0];
    hull[1]=p[1];
    hull[2]=p[2];
    for (i = 3; i < m; i++)
    {
      while (orientation(hull[cnt-1], hull[cnt], p[i]) != 2)
         cnt--;
    cnt++;
    hull[cnt]=p[i];
    }
    cnt++;
 /*  for(i=0;i<cnt;i++)
    printf("%d %d\n",hull[i].x,hull[i].y);*/
    hull[cnt].x=-1;
   return hull;
}
int main()
{
    int n,i=0,j,a,b;
    FILE *fp;
    fp=fopen("input.txt","r");
    point p[100];
    while(fscanf(fp,"%d %d\n",&a,&b)!=EOF)
    {
        p[i].x=a;
        p[i].y=b;
        i++;
    }
    n=i--;
    int ymin=p[0].y,min=0;
    for(i=0;i<n;i++)
    {
        if(p[i].y<ymin)
        {
            ymin=p[i].y;
            min=i;
        }
        if(p[i].y==ymin && p[i].x<p[min].x)
            min=i;
    }
    p0=p[min];
    point ptemp=p[0];
    p[0]=p[min];
    p[min]=ptemp;
    point *hull=convex_hull(p,n);

    /*i=0;
    while(1)
    {
        if(hull[i].x==-1)
            break;
        printf("%d %d\n",hull[i].x,hull[i].y);
        i++;
    }
    */
    return 0;
}
