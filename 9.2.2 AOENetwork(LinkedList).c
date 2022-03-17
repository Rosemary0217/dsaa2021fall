/* linked list implement 
   TLE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct arc *Edge,*arcPtr;
typedef struct vertex vertex;

struct vertex{
    int id,indegree,outdegree;
    int earliestCompletion,latestCompletion;
    char vexName[10];
    Edge firstEdge;
};

struct arc{
    int to,weight;
    Edge nextEdge;
};

vertex graph[MAX];
arcPtr curArc[MAX]={NULL};
//紫砂了,原来用栈:)
int topOrder[MAX]={},stack[MAX]={},top=0,counter=0,path[MAX]={};

//从大到小排序,出栈时就是从小到大
int cmp(const void *a,const void *b){
    return *(int*)b-*(int*)a;
}

void InitGraph(int size)
{
    for(int i=0;i<size;i++)
    {
        //memset(graph[i].vexName,'\0',sizeof(graph[i].vexName));
        graph[i].indegree=0;
        graph[i].outdegree=0;
        graph[i].earliestCompletion=0;
        //graph[i].latestCompletion=1000;
    }
    graph[0].earliestCompletion=0;
    return;
}

void getVertice(int num_of_vertex)
{
    int i,j;
    char ch;
    for(i=0;i<num_of_vertex;i++)
    {
        j=0;
        while(1)
        {
            scanf("%c",&ch);
            if(ch==','||ch=='\n') break;
            else graph[i].vexName[j++]=ch;
        }
        graph[i].vexName[j]='\0';
    }
    return;
}

//增加新边（公用代码）
Edge CreateNewEdge(int to,int weight)
{
    Edge newEdge=(Edge)malloc(sizeof(struct arc));
    newEdge->nextEdge=NULL;
    newEdge->to=to;
    newEdge->weight=weight;
    return newEdge;
}

//第一条边
void AddFirstEdge(int from,int to,int weight)
{
    arcPtr new=CreateNewEdge(to,weight);
    graph[from].firstEdge=new;
    curArc[from]=new;
    return;
}

//非第一条边
void AddNextEdge(int from,int to,int weight)
{
    arcPtr new=CreateNewEdge(to,weight);
    curArc[from]->nextEdge=new;
    curArc[from]=new;
    return;
}

void getEdges(int num_of_edges)
{
    int i=0,j=0,from,to,weight,count=0,ptr[3]={0};
    for(i=0;i<num_of_edges;i++)
    {
        if(i<num_of_edges-1) scanf("<%d,%d,%d>,",&from,&to,&weight);
        else scanf("<%d,%d,%d>",&from,&to,&weight);
        graph[to].indegree++;
        //建图
        if(graph[from].outdegree==0) AddFirstEdge(from,to,weight);
        else AddNextEdge(from,to,weight);
        graph[from].outdegree++;
    }
    return;
}

void topSort(int total)
{
    int i,k=0,m,curVex;
    arcPtr ptr;
    //入度为0的点入栈
    for(i=0;i<total;i++)
    {
        if(graph[i].indegree==0) 
            stack[top++]=i;
    }

    while(top>0)
    {
        curVex=stack[--top];
        topOrder[counter++]=curVex;
        ptr=graph[curVex].firstEdge;
        while(ptr!=NULL)
        {
            if(--graph[ptr->to].indegree==0)
                stack[top++]=ptr->to;
            //对当前节点的每一个下一点，算出EC
            if(graph[ptr->to].earliestCompletion<graph[curVex].earliestCompletion+ptr->weight)
                graph[ptr->to].earliestCompletion=graph[curVex].earliestCompletion+ptr->weight; 
            ptr=ptr->nextEdge;
        }
        qsort(stack,top,sizeof(int),cmp);
    }
    return;
}

void printTopSortResult(int size)
{
    for(int i=0;i<size-1;i++)
    {
        printf("%s-",graph[topOrder[i]].vexName);
        graph[i].latestCompletion=graph[size-1].earliestCompletion;
    }
    //forgot to assign value...
    graph[size-1].latestCompletion=graph[size-1].earliestCompletion;
    printf("%s\n",graph[topOrder[size-1]].vexName);
    return;
}

void DFS(int depth,int end)
{
    int curNode=path[depth-1],i=0;
    //到终点，得到关键路径
    if(curNode==end)
    {
        for(i=0;i<depth-1;i++)
            printf("%s-",graph[path[i]].vexName);
        printf("%s\n",graph[path[depth-1]].vexName);
        return;
    }
    arcPtr ptr=graph[curNode].firstEdge;
    while(ptr!=NULL)
    {
        if(graph[curNode].earliestCompletion+ptr->weight<graph[ptr->to].earliestCompletion)
            continue;
        if(graph[ptr->to].earliestCompletion==graph[ptr->to].latestCompletion)
        {
            path[depth++]=ptr->to;
            DFS(depth,end);
            depth--;
        }
        ptr=ptr->nextEdge;
    }
    return;
}

void findKeyPath(int size)
{
    int i,cur,destination=0;
    arcPtr ptr;
    //为每个节点计算LC
    for(i=size-2;i>=0;i--)
    {
        cur=topOrder[i];
        ptr=graph[cur].firstEdge;
        while(ptr!=NULL)
        {
            destination=ptr->to;
            if(graph[cur].latestCompletion>graph[destination].latestCompletion-ptr->weight)
                graph[cur].latestCompletion=graph[destination].latestCompletion-ptr->weight;
            ptr=ptr->nextEdge;
        }
    }
    path[0]=topOrder[0];
    DFS(1,topOrder[size-1]);
    return;
}

int main()
{
    int num_of_vertex,num_of_edges,i,j;
    scanf("%d,%d\n",&num_of_vertex,&num_of_edges);
    InitGraph(num_of_vertex);
    //得到图
    getVertice(num_of_vertex);
    getEdges(num_of_edges);

    topSort(num_of_vertex);

    if(counter<num_of_vertex)
    {
        printf("NO TOPOLOGICAL PATH\n");
        return 0;
    }
    printTopSortResult(num_of_vertex);

    findKeyPath(num_of_vertex);

    return 0;
}