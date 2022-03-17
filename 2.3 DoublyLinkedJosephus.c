#include <stdio.h>
#include <stdlib.h>

struct  node{
    int num;
    struct node *last;
    struct node *next;
};

int main()
{
    int n,k,m,i,j;
    scanf("%d,%d,%d",&n,&k,&m);
    if(n==0||m==0||k==0)
    {
        printf("n,m,k must bigger than 0.\n");
        return 0;
    }
    if(k>n)
    {
        printf("k should not bigger than n.\n");
        return 0;
    }
    int remain=n,out1,out2;
    struct node *head,*p,*q,*tmp;
    p=(struct node*)malloc(sizeof(struct node));
    head=p;
    p->num=1;
    for(i=2;i<=n;i++)    // linking forwards and form a circuit
    {
        q=(struct node*)malloc(sizeof(struct node));
        q->num=i;
        p->next=q;
        p=q;
        q->next=head;
    }
    q=head;
    p=q->next;
    for(i=1;i<=n;i++)    // linking backwards( also a circuit )
    {
        p->last=q;
        p=p->next;
        q=q->next;
    }
    struct node *ptr1,*ptr2,*tmp_last,*tmp_next;
    for(i=1;i<=k-1;i++)    // moving the pointer to the k-th person
        q=q->next;
    ptr1=q,ptr2=q;
    while(remain>0)
    { 
        for(i=1;i<m;i++)    // count to m 
        {
            ptr1=ptr1->next;
            ptr2=ptr2->last;
        }
        if(ptr1==ptr2)
        {
            printf("%d,",ptr1->num);
            remain--;
            tmp_next=ptr1->next;    // store the 2 addresses ptr1&2 will be next.
            tmp_last=ptr1->last;
            ptr2->next->last=tmp_last;
            ptr1->last->next=tmp_next;
            // free(ptr1);
            // free(ptr2);
            ptr1=tmp_next;
            ptr2=tmp_last;
        }
        else
        {
            printf("%d-%d,",ptr1->num,ptr2->num);
            remain-=2;
            tmp_last=ptr2->last;
            tmp_last->next=ptr2->next;
            ptr2->next->last=tmp_last;
            tmp_next=ptr1->next;
            tmp_next->last=ptr1->last;
            ptr1->last->next=tmp_next;
            // free(ptr1);      segmentation fault???
            // free(ptr2);
            ptr1=tmp_next;
            ptr2=tmp_last;
        }
    }
    printf("\n");

    return 0;
} 