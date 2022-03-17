#include <stdio.h>
#include <stdlib.h>

#define MAX 500

int a[MAX]={},stack[MAX]={},tail,size,group;
void push(int elem);
void pop();
int top();

void judge()
{
    int i=1,j=1,flag=1;
    tail=0;   //初始栈为空
    for(i=1,j=1;i<=size;i++)
    {
    	if(a[i]==j) j++;
    	else if(tail>0&&top()==a[i]) pop();
    	else if(j<=size)
    	{
    		while(a[i]!=j&&j<=size)
    			push(j++);
    		if(a[i]==j) j++;
		}
		else break;
	}
    if(tail==0) printf("Yes\n");
    else printf("No\n");

    return;
}

void push(int elem){
    stack[++tail]=elem;
    return;
}

void pop(){
    tail--;
    return;
}

int top(){
    return stack[tail];
}

int main()
{
    int i,j,end=0,fois=0;
    while(1)
    {
        scanf("%d %d",&size,&group);
        if(group==0&&size==0) return 0;
        else fois++;
        if(fois>1) printf("\n");
        for(i=1;i<=group;i++)   // m组数据
        {
            for(j=1;j<=size;j++)  // 得到序列
                scanf("%d",&a[j]);
            judge();
        }  
    }
}


//    while(i<=size)
//    {
//    	if(a[i]==j)
//    	{
//    		i++;
//    		j++;
//		}
//		else 
//		{
//			if(tail>0&&top()==a[i]) 
//			{
//				pop();
//				i++;
//			}
//			else if(j<=size)
//				push(j++);
//			else break;
//		}
//	}