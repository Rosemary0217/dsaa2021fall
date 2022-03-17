#include <stdio.h>
#include <stdlib.h>

#define MAX 101

int capacity,num,weight[MAX]={0},load=0,maxload=0,seq[MAX]={0},curSeq[MAX]={0},cs[MAX]={0};

void dfs(int depth)
{
    int i;
    if(load>capacity) return;
    else if(depth==num+1)
    {
        for(i=1;i<=num;i++)
            seq[i]=curSeq[i];
        maxload=load;
    }
    else
    {
        if(load+weight[depth]<=capacity)
        {
            curSeq[depth]=1;
            load+=weight[depth];
            //tmp+=pow(2,num-depth);
            dfs(depth+1);
            load-=weight[depth];
            //tmp-=pow(2,num-depth);
        }
        if(load+cs[num]-cs[depth]>maxload)
        {
            curSeq[depth]=0;
            dfs(depth+1);
        }
    }
    return;
}

int main()
{
    int i;
    scanf("%d %d",&capacity,&num);
    for(i=1;i<=num;i++)
    {
        scanf("%d",&weight[i]);
        cs[i]=cs[i-1]+weight[i];   //calculate the cummulative sum of wieght
    }
    dfs(1);
    printf("%d\n",maxload);
    for(i=1;i<=num;i++)
        if(seq[i]!=0)
            printf("%d ",i);
    printf("\n");
    return 0;
}