#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100005

typedef struct{
    double x,y;
}toyCoordinate;

toyCoordinate toy[MAX],tmp[MAX];

int xcmp(const void*a, const void* b)
{
    toyCoordinate* m=(toyCoordinate*)a;
    toyCoordinate* n=(toyCoordinate*)b;
    if(m->x<n->x) return -1;
    else if(m->x==n->x) return 0;
    else return 1;
}

int ycmp(const void* a, const void* b)
{
    toyCoordinate* m=(toyCoordinate*)a;
    toyCoordinate* n=(toyCoordinate*)b;
    if(m->y<n->y) return -1;
    else if(m->y==n->y) return 0;
    else return 1;
}

double distance(toyCoordinate toy1,toyCoordinate toy2)
{
    return sqrt(pow(toy1.x-toy2.x,2)+pow(toy1.y-toy2.y,2));
}

double min(double x,double y)
{
    return x<y?x:y;
}

double find(int left,int right)
{
    if(left==right-1)
        return distance(toy[left],toy[right]);
    else if(left==right-2)
        return min(distance(toy[left],toy[left+1]),min(distance(toy[left+1],toy[right]),distance(toy[left],toy[right])));
    else
    {
        double mindist;
        int mid=(left+right)/2;
        double leftmin=find(left,mid),rightmin=find(mid+1,right);
        mindist=min(leftmin,rightmin);
        int i,count=0,j,k;
        for(i=left;i<=right;i++)
            if(fabs(toy[i].x-toy[mid].x)<mindist)
            {
                tmp[count].x=toy[i].x;
                tmp[count++].y=toy[i].y;
            }
        qsort(tmp,count,sizeof(toyCoordinate),ycmp);
        for(j=0;j<count;j++)
            for(k=j+1;k<count;k++)
            {
                if(tmp[k].y-tmp[j].y>=mindist)
                    break;
                mindist=min(mindist,distance(tmp[j],tmp[k]));
            }
        return mindist;
    }
}

int main()
{
    int num,i,t;
    while(1)
    {
        scanf("%d",&num);
        if(num==0) return 0;
        for(i=0;i<num;i++)
            scanf("%lf %lf",&toy[i].x,&toy[i].y);
        qsort(toy,i,sizeof(toyCoordinate),xcmp);
        printf("%.2lf\n",find(0,num-1)/2);
    }
}