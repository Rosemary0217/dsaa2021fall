/* array implement
   linked list is way too expensive */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct arc Edge;
typedef struct vertex vertex;

struct arc{
    int to,weight;
};

struct vertex{
    int id,indegree,outdegree;
    int earliestCompletion,latestCompletion;
    char vexName[10];
    Edge edges[100];
};

vertex graph[MAX];
//紫砂了，队列排序一晚上，最后发现用栈:)
int topOrder[MAX]={},stack[MAX]={},top=0,counter=0,path[MAX]={};

//从大到小排序,出栈时就是从小到大
int cmp(const void *a,const void *b){
    return *(int*)b-*(int*)a;
}

void InitGraph(int size)
{
    for(int i=0;i<size;i++)
    {
        graph[i].indegree=0;
        graph[i].outdegree=0;
        graph[i].earliestCompletion=0;
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

void AddNewEdge(int from,int to,int weight)
{
    int pos=graph[from].outdegree++;
    graph[from].edges[pos].to=to;
    graph[from].edges[pos].weight=weight;
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
        AddNewEdge(from,to,weight);
    }
    return;
}

void topSort(int total)
{
    int i,k=0,m,cur,curVex;
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
        for(i=0;i<graph[curVex].outdegree;i++)
        {
            cur=graph[curVex].edges[i].to;
            if(--graph[cur].indegree==0) 
                stack[top++]=cur;
            //对当前节点的每一个下一点，算出EC
            if(graph[cur].earliestCompletion<graph[curVex].earliestCompletion+graph[curVex].edges[i].weight)
                graph[cur].earliestCompletion=graph[curVex].earliestCompletion+graph[curVex].edges[i].weight; 
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
    int curNode=path[depth-1],i;
    //到终点，得到关键路径
    if(curNode==end)
    {
        for(i=0;i<depth-1;i++)
            printf("%s-",graph[path[i]].vexName);
        printf("%s\n",graph[path[depth-1]].vexName);
        return;
    }

    for(i=0;i<graph[curNode].outdegree;i++)
    {
        int to=graph[curNode].edges[i].to;
        if(graph[curNode].earliestCompletion+graph[curNode].edges[i].weight<graph[to].earliestCompletion)
            continue;
        if(graph[to].earliestCompletion==graph[to].latestCompletion)
        {
            path[depth++]=to;
            DFS(depth,end);
            depth--;
        }
    }
    return;
}

void findKeyPath(int size)
{
    int i,cur,destination=0;
    //为每个节点计算LC
    for(i=size-2;i>=0;i--)
    {
        cur=topOrder[i];
        for(int j=0;j<graph[cur].outdegree;j++)
        {
            destination=graph[cur].edges[j].to;
            if(graph[cur].latestCompletion>graph[destination].latestCompletion-graph[cur].edges[j].weight)
                graph[cur].latestCompletion=graph[destination].latestCompletion-graph[cur].edges[j].weight;
        }
    }
    path[0]=topOrder[0];
    DFS(1,topOrder[size-1]);
    return;
}

int main()
{
    int num_of_vertex,num_of_edges;
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