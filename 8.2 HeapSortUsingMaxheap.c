#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int size,MaxHeap[MAX];

void PercolateDown(int cur)
{
    int LeftChild,RightChild,tmp,max;
    while(cur*2<=size)
    {        
        LeftChild=2*cur;
        RightChild=2*cur+1;
        if(RightChild<=size) 
            max=MaxHeap[LeftChild]>=MaxHeap[RightChild]?LeftChild:RightChild;
        else 
            max=LeftChild;
        if(MaxHeap[cur]>=MaxHeap[max]) break;
        else
        {
            tmp=MaxHeap[cur];
            MaxHeap[cur]=MaxHeap[max];
            MaxHeap[max]=tmp;
        }
        cur=max;
    }
    return;
}

void Heapsort()
{
    for(int i=size/2;i>0;i--)
        PercolateDown(i);
    for(int tmp=1;tmp<=size;tmp++)
        printf("%d ",MaxHeap[tmp]);
    printf("\n");
    return;
}

void DeleteMax()
{
    int i,cur=1,LastElem=MaxHeap[size--],LeftChild,RightChild,maxchild;
    for(i=1;i*2<=size;i=maxchild)
    {
        LeftChild=2*i,RightChild=2*i+1;
        if(RightChild<=size) maxchild=MaxHeap[LeftChild]>=MaxHeap[RightChild]?LeftChild:RightChild;
        else maxchild=LeftChild;
        if(LastElem<MaxHeap[maxchild]) MaxHeap[i]=MaxHeap[maxchild];
        else break; 
    }
    MaxHeap[i]=LastElem;

    for(int tmp=1;tmp<=size;tmp++)
        printf("%d ",MaxHeap[tmp]);
    printf("\n");
    return;
}

int main()
{
    int i;
    scanf("%d",&size);
    for(i=1;i<=size;i++)
        scanf("%d",&MaxHeap[i]);
    Heapsort();
    DeleteMax();
    DeleteMax();
    return 0;
}