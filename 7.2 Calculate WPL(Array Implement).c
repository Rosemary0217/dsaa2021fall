#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MAX_VALUE 1000

int num[MAX_LEN]={0},n;

int FindMin1()
{
    int index,min=MAX_VALUE;
    for(int i=1;i<=n;i++)
    {
        if(num[i]<min)
        {
            index=i;
            min=num[i];
        }
    }
    num[index]=MAX_VALUE;  // take out the mininum
    return min;
}

int FindMin2(int pre_min)
{
    int index,min=MAX_VALUE;
    for(int i=1;i<=n;i++)
    {
        if(num[i]<min)
        {
            index=i;
            min=num[i];
        }
    }
    num[index]=pre_min+min;  // take the mininum and replace it with sum
    return min;
}

int main()
{
    int i,min1,min2,wpl=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&num[i]);
    int left=n;
    while(left>=2)
    {
        min1=FindMin1();
        min2=FindMin2(min1);
        wpl+=(min1+min2);
        left--;
    }
    printf("WPL=%d\n",wpl);
    return 0;
}