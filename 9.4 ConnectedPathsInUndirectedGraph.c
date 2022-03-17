#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 10

typedef struct vertexNode Vertex;

struct vertexNode{
    int vertex,vis,num_of_edges,edges[MAX_NUM];
};

Vertex vertice[MAX_NUM];

void InitGraph(int size)
{
    for(int i=0;i<size;i++)
    {
        vertice[i].num_of_edges=0;
        vertice[i].vis=0;
    }
    return;
}

void AddArc(int vex1,int vex2)
{
    vertice[vex1].edges[vertice[vex1].num_of_edges++]=vex2;
    vertice[vex2].edges[vertice[vex2].num_of_edges++]=vex1;
    return;
}

int cmp(const void *a,const void *b)
{
    return *(int*)a-*(int*)b;
}

void Sort(int size)
{
    for(int i=0;i<size;i++)
        qsort(vertice[i].edges,vertice[i].num_of_edges,sizeof(int),cmp);
    return;
}

void bfs(int vex)
{
    int i,arr[10]={},count=0;
    for(i=0;i<vertice[vex].num_of_edges;i++)
    {
        if(!vertice[vertice[vex].edges[i]].vis)
        {
            vertice[vertice[vex].edges[i]].vis=1;
            printf("-%d",vertice[vex].edges[i]);
            arr[count++]=vertice[vex].edges[i];
        }
    }
    for(i=0;i<count;i++)
        bfs(arr[i]);
    return;
}

void Search(int size)
{
    for(int i=0;i<size;i++)
    {
        if(!vertice[i].vis)
        {
            vertice[i].vis=1;
            printf("%d",i);
            bfs(i);
            printf("\n");
        }
    }
    return;
}

int main()
{
    int n,a,b;
    scanf("%d",&n);
    InitGraph(n);
    while(1)
    {
        scanf("%d",&a);
        if(a==-1) break;
        scanf("%d",&b);
        //建图
        AddArc(a,b);
    }
    Sort(n);
    Search(n);

    return 0;
}