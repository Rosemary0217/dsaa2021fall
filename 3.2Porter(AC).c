#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

struct platform{
    int num_of_goods;
    int B_destination[MAX];
}platform[MAX];

int lorry[MAX]={0},ans=0,tail;
int set,num_of_platform,storage_of_B,storage_of_truck;

int unload(int num,int id)
{
    while(tail>0)
    {
        if(lorry[tail]==id)  // move to plat A
        {
            tail--;
            ans++;
        }
        else if(num<storage_of_B)    // move the tail to plat B
        {
            platform[id].B_destination[num++]=lorry[tail--];
            ans++;
        }
        else break;
    }
    return num;
}

int load(int num,int id)
{
    while(1)
    {
        if(tail==storage_of_truck||num==0)      //装满或B空
            break;
        lorry[++tail]=platform[id].B_destination[0];
        for(int m=0;m<num;m++)
            platform[id].B_destination[m]=platform[id].B_destination[m+1];
        num--;
        ans++;
    }
    return num;
}

int main()
{
    int i,j,k,q,tmp,remain;
    scanf("%d",&set);
    for(i=0;i<set;i++)
    {
        ans=0;
        tail=0;
        scanf("%d %d %d",&num_of_platform,&storage_of_truck,&storage_of_B);
        for(j=1;j<=num_of_platform;j++)
        {
            scanf("%d",&platform[j].num_of_goods);
            for(k=0;k<platform[j].num_of_goods;k++)
                scanf("%d",&platform[j].B_destination[k]);
        }
        for(j=1;j<=num_of_platform;j++)
        {
        	remain=0;
            platform[j].num_of_goods=unload(platform[j].num_of_goods,j);  //卸货
            platform[j].num_of_goods=load(platform[j].num_of_goods,j);   //装货
            remain+=tail;
            if(remain==0)
                for(k=1;k<=num_of_platform;k++)
                {
                    remain+=platform[k].num_of_goods;
                    if(remain) break;
                }
            if(remain==0) break;  //搬空了，结束
            else
            {
                ans+=2;
                if(j==num_of_platform) j=0;  //重新开始
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

// 1
// 5 2 3
// 3 4 5 2
// 2 1 3
// 0
// 3 3 5 1
// 1 4
