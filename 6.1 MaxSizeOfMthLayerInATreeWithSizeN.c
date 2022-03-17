/* IDEA: build a tree of size m+1 with m layers first(the original tree sort of looks like a linked list), 
then start to add subtrees of growing size no larger than m-1(or there'll be one more layer). If the 
remaining nodes can supply, then add and increase the size(as long as it is legal). When doing the insertion,
if:
(1) We've reached the ceiling,it means the right(left) half part is full, minus 1 from the size, continue to
add subtree to the left half part.
(2) We're running out of nodes, then add 1 node and minus 1 from the size of the tree we tried to add and 
continue going.
(3) We have exactly the same amount of nodes left as #nodes of the subtree we want to add, then just add and
return.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ans,SizeOfNewSubtree,m,down,max;

void count(int RemainingNodes)
{
    if(RemainingNodes==0||SizeOfNewSubtree>m) return;
    int NumOfSubtreeNodes=pow(2,SizeOfNewSubtree)-1;
    if(RemainingNodes>NumOfSubtreeNodes)
    {
        if(!down) SizeOfNewSubtree++;
        ans+=(NumOfSubtreeNodes+1)/2;
        if(ans==max) return;
        count(RemainingNodes-NumOfSubtreeNodes);
    }
    else if(RemainingNodes==NumOfSubtreeNodes)
    {
        ans+=(NumOfSubtreeNodes+1)/2;
        return;
    }
    else 
    {
        down=1;
        SizeOfNewSubtree--;
        count(RemainingNodes-1);
    }
    return;
}

int main()
{
    int N,n;
    scanf("%d",&N);
    while(N--)
    {
        scanf("%d %d",&n,&m);
        if(n<m+1)   // if cannot even reach level m
        {
            printf("0\n");
            continue;
        }
        else if(n==m+1)
        {
            printf("1\n");
            continue;
        }
        ans=1;
        SizeOfNewSubtree=1;
        down=0;
        max=pow(2,m);
        count(n-m-1);
        printf("%d\n",ans); 
    }
    return 0;
}