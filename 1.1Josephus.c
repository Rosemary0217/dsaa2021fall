#include<stdio.h>/*约瑟夫问题*/
#include<stdlib.h> 
struct node {
	int no;
	struct node * next;
};

struct node * head;

void ConstructHeadNode()
{
    head = (struct node *)malloc(sizeof(struct node));
	head->no   = -1;
	head->next = head;  
}

int main( )
{	
    int i, k, n, m;  
    struct node * p, * q;
    scanf("%d,%d,%d",&n,&k,&m);
    if(k>n) printf("k should not bigger than n.\n");
    else if(n<1||k<1||m<1) printf("n,m,k must bigger than 0.\n");
    else
    {
        ConstructHeadNode();
        for ( i=n; i>0; i-- )                        // 生成循环链表
        {	
            p = (struct node *)malloc(sizeof(struct node));
            p->no = i;  
            p->next = head->next; 
            head->next = p;
        }
        while ( p->next != head )               
            p = p->next;
        p->next = head->next;   // p指向最后一个节点
        for ( i = 0 ; i < k-1 ; i++)
            p = p->next;        //从第k个节点开始
        int count = n;
        while(count)
        {
            for ( i = 0 ; i < m-1; i++ )
                p = p->next;
            count--;
            q = p->next;                // p的下一个结点是要出列的结点
            p->next = q->next;          // 循环链表跳过要出列的结点
            if(count>0&&(n-count)%10!=0) 
                printf("%d ", q->no);
            else if(count==0||(n-count)%10==0) 
                printf("%d\n",q->no); 
            free(q);                              // 释放 q 结点
        }	                      
    }
	
    return 0;
}