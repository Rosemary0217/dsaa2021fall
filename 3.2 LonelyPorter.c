#include <stdio.h>
#include <stdlib.h>

#define MAX 101

typedef struct platform{
    int id;
    int num_of_goods;
    int B_destination[MAX];
    struct platform *last;
    struct platform *next;
}PLATFORM;

int lorry[MAX]={0},ans=0;
int set,num_of_platform,storage_of_B,quantity;

// void Initialization(PLATFORM *ptr)
// {
//     for(int i=0;i<MAX;i++)
//         ptr->B_[i]=0;
//     ptr->last=ptr;
//     ptr->next=ptr;
//     return;
// }

void Delete(PLATFORM *ptr)
{
    PLATFORM *tmp;
    tmp=ptr;
    ptr->last->next=ptr->next;
    ptr->next->last=ptr->last;
    free(tmp);
    return;
}

void load(int lorry[],int tail,PLATFORM *ptr,int num)
{
    int i=0;
    while(1)
    {
        if(tail==quantity-1||num==0)
            return;
        lorry[++tail]=ptr->B_destination[i++];
        num--;
        ans++;
    }
    return;
}

int main()
{
    int i,j,k,q,tmp;
    scanf("%d",&set);
    PLATFORM *p,*cur,*head;
    // Initialization(p);
    head=p;
    for(i=0;i<set;i++)
    {
        ans=0;
        memset(lorry,0,sizeof(lorry));
        scanf("%d %d %d",&num_of_platform,&quantity,&storage_of_B);
        for(j=0;j<num_of_platform;j++)
        {
            cur=(PLATFORM*)malloc(sizeof(PLATFORM));  // 每次给站点申请一个新的节点
            cur->id=j+1;
            scanf("%d",&cur->num_of_goods);
            for(k=0;k<cur->num_of_goods;k++)
                scanf("%d",&cur->B_destination[k]);
            // 链接所有站点->segmentation fault
            cur->next=head;        
            p->next->last=cur;
            p->next=cur;
            cur->last=p;
            p=cur;
        }
        p=head;
        while(p->last!=p->next)  // traverse the link
        {
            PLATFORM *tmp;
            tmp=p;
            int tail=p->num_of_goods-1,num=p->num_of_goods;
            while(num<storage_of_B&&tail>=0)
            {
                if(lorry[tail]==p->id)  // if the B_ is this platform move to A
                {
                    tail--;
                    ans++;
                }
                else    // move the tail to plat B
                {
                    p->B_destination[num++]=lorry[tail--];
                    ans++;
                    num++;
                }
            }
            load(lorry,tail,p,num);   //装货
            p=p->next;
            Delete(tmp);
            ans+=2;
        }
    }
    printf("%d\n",ans);
    return 0;
}

// int N,Q,S,time,numt;
// int unload(int b[100],int track[100],int num,int j);
// int  load(int b[100],int track[100],int num);
 
// void main()
// {	
//  int i,j,k,set,B[100][100],track[100],num[100],sum; 	
// 	scanf("%d",&set);
// 	for(i=0;i<set;i++)
// 	{	scanf("%d%d%d",&N,&S,&Q);
// 		for(j=0;j<N;j++) 
// 		{	scanf("%d",&num[j]);
// 			for(k=0;k<num[j];k++) 
// 				scanf("%d",&B[j][k]);
// 		}
// 		time=0;
// 		for(j=0;j<N;j++)   // traverse every platform
// 		{	
//          num[j]=unload(B[j],track,num[j],j);  //num[j]:#goods on B
// 			sum=0;
// 			for(k=0;k<N;k++)
// 			{	sum+=num[k];
// 				if(sum!=0)
// 					break;
// 			}
// 			sum+=numt;
// 			if(sum==0)
// 			{	printf("%d\n",time);
// 				break;
// 			}
// 			else
// 				{	if(j==N-1)
// 						j=-1;
// 					time+=2;
// 					continue;
// 				}
// 		}
// 	}
// }
 
// int unload(int b[100],int track[100],int num,int j)
// {	while(1)
// 	{	if(numt!=0)   // number of goods on truck is greater than 0
// 		{	if(track[numt-1]==j+1)   // if the good belongs to here
// 			{	numt--;
// 				time++;
// 			}
// 			else
// 			{	if(num==Q)   // if there is no space on plat B
// 				{	num=load(b,track,num);
// 					return num;	
// 				}
// 				else   // move to B
// 				{	b[num++]=track[--numt];
// 					time++;
// 				}
// 			}
// 		}
// 		else  //truck is empty and start to load
// 		{	num=load(b,track,num);
// 			return num;
// 		}
// 	}
// }
 
// int  load(int b[100],int track[100],int num)
// {	for(;;)
// 	{
// 		if(numt==S||num==0)  //满了或空了
// 			return num;
// 		else
// 		{	track[numt++]=b[0];
// 			num=move(b,num);
// 			time++;
// 		}
// 	}
// }
//
// int move(int b[100],int num)  //从头拿走
// {	int k;
// 	for(k=1;k<num;k++)
// 		b[k-1]=b[k];
// 	num--;
// 	return num;
// }