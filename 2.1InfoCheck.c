#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

struct node {
	int num;
    char name[15];
	struct node *next;
};

struct node *head;

struct node* ConstructHeadNode()
{
    head=(struct node *)malloc(sizeof(struct node));
	head->num=-1;
    return head;
}

int main()
{
    int i,m,tmp;
    scanf("%d",&m);
    struct node *p,*q,*head1,*head2;
    head1=ConstructHeadNode();
    head1->next=NULL;
    q=(struct node*)malloc(sizeof(struct node));
    for(i=0;i<m;i++)      // construct List 1
    {
        p=(struct node *)malloc(sizeof(struct node));
        scanf("%d",&tmp);
        gets(p->name);
        p->num=tmp;
        p->next=NULL;
        if(head1->next==NULL)
            head1->next=p;   // 在表头后插入第一个数据节点
        else
            q->next=p;  // 存下当前节点的首地址，后续在它后面插入新节点
        q=p;
    }
    int n;
    head2=ConstructHeadNode();
    head2->next=NULL;
    scanf("%d",&n);
    if(n==0) 
    {
        printf("the LIST2 is NULL.\n");
        return 0;
    }
    for(i=0;i<n;i++)    // construct List 2
    {
        p=(struct node *)malloc(sizeof(struct node));
        scanf("%d",&tmp);
        gets(p->name);
        p->num=tmp;
        p->next=NULL;
        if(head2->next==NULL)
            head2->next=p;   // 在表头后插入第一个数据节点
        else
            q->next=p;  // 存下当前节点的首地址，后续在它后面插入新节点
        q=p;
    }
    struct node *tmp1,*tmp2;
    tmp2=head2->next;
    int flag,all_in=1;
    while(tmp2!=NULL)
    {
        flag=0;
        tmp1=head1->next;
        while(tmp1!=NULL)
        {
            if(strcmp(tmp1->name,tmp2->name)==0&&tmp1->num==tmp2->num)
            {
                flag=1;
                break;
            }    
			tmp1=tmp1->next;   
        }
        if(!flag)
		{
        	printf("%8d%s is not in LIST1.\n",tmp2->num,tmp2->name);
        	all_in=0;
		}
        tmp2=tmp2->next;
    }
    if(all_in) printf("the records of LIST2 are all in the LIST1.\n");

    return 0;
}
