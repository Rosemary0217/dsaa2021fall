//无向图的BFS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 200

typedef struct arcNode *Arc,*arcptr;
typedef struct vertexNode Vertex;

struct arcNode{
    int otherVertex;
    Arc nextArc;
};

struct vertexNode{
    char vertex;
    int id;
    int vis;
    Arc firstArc;
};

Vertex vertice[MAX_NUM];
int queue[MAX_NUM]={-1},rear=0,front=1;

void AddFirstArc(int vex1,int vex2)
{
    Arc tmp=(Arc)malloc(sizeof(struct arcNode));
    tmp->nextArc=NULL;
    tmp->otherVertex=vex2;
    vertice[vex1].firstArc=tmp;
    return;
}

void AddNextArc(int vex1,int vex2)
{
    Arc tmp=(Arc)malloc(sizeof(struct arcNode));
    tmp->otherVertex=vex2;
    //从头插入新的arc
    tmp->nextArc=vertice[vex1].firstArc;
    vertice[vex1].firstArc=tmp;
    return;
}

void printList(int size)
{
    printf("the ALGraph is\n");
    arcptr ptr;
    for(int i=0;i<size;i++)
    {
        printf("%c",vertice[i].vertex);
        ptr=vertice[i].firstArc;
        while(ptr!=NULL)
        {
            printf(" %d",ptr->otherVertex);
            ptr=ptr->nextArc;
        }
        printf("\n");
    }
    return;
}

void Enqueue(int elem)
{
    queue[++rear]=elem;
    return;
}

void Dequeue()
{
    front++;
    return;
}

int top()
{
    return queue[front];
}

int IsEmpty()
{
    return front==rear+1;
}

/*坑:(1)输入的顶点不一定按照字母表顺序，因此不能'a'+top()输出，而应该专门存ch 
     (2)有可能有点无边*/
void BFS(int size)
{
    printf("the Breadth-First-Seacrh list:");
    arcptr ptr;
    for(int i=0;i<size;i++)
    {
        if(!vertice[i].vis)
        {
            Enqueue(vertice[i].id);
            vertice[i].vis=1;
            while(!IsEmpty())
            {
                printf("%c",vertice[top()].vertex);
                ptr=vertice[top()].firstArc;
                Dequeue();
                while(ptr!=NULL)
                {
                    if(!vertice[ptr->otherVertex].vis)
                    {
                        vertice[ptr->otherVertex].vis=1;
                        Enqueue(ptr->otherVertex);
                    }
                    ptr=ptr->nextArc;
                }
            }
        }
    }
    
    printf("\n");
    return;
}

int main()
{
    int i,a,b;
    char ch;
    for(i=0;i<MAX_NUM;i++)
    {
        scanf("%c",&ch);
        getchar();
        if(ch=='*') break;
        else
        {
            vertice[i].id=i;
            vertice[i].vertex=ch;
            vertice[i].vis=0;
            vertice[i].firstArc=NULL;
        }
    }
    while(1)
    {
        scanf("%d,%d",&a,&b);
        if(a==-1&&b==-1) break;
        else
        {
            if(vertice[a].firstArc==NULL)
                AddFirstArc(a,b);
            else AddNextArc(a,b);
            if(vertice[b].firstArc==NULL)
                AddFirstArc(b,a);
            else AddNextArc(b,a);
        }
    }
    printList(i);
    BFS(i);

    return 0;
}