#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 2000005

typedef struct{
    long long int time;
    char type;
}timenode;

timenode node[MAX_NUM];

int compare(const void*a, const void* b)
{
    timenode m=*(timenode*)a;
    timenode n=*(timenode*)b;
    if(m.time!=n.time) return m.time-n.time;
    else return m.type-n.type;
}

int main()
{
    int n,i,tmp=0,count=0;
    scanf("%d",&n);
    node[0].time=-1;
    node[0].type='a';
    for(i=1;i<=n;i++)
    {
        scanf("%lld %lld",&node[2*i-1].time,&node[2*i].time);
        node[2*i-1].type='s';
        node[2*i].type='e';
    }
    //数目不要搞错了
    qsort(node,2*n+1,sizeof(timenode),compare);
    for(i=1;i<=2*n;i++)
    {
        if(node[i].type=='e')
            tmp--;
        else tmp++;
        count=tmp>count?tmp:count;
    }
    printf("%d\n",count);

    return 0;
}