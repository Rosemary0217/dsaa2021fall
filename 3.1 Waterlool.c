#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100001
#define MAX_HEIGHT 1000001

struct puddle{
    int id;
    int height;
    int width;
    struct puddle *last;
    struct puddle *next;
};

long long time[MAX_NUM]={0};

// works:
struct puddle * ConstructHead()
{
    struct puddle *ptr;
    ptr=(struct puddle*)malloc(sizeof(struct puddle));
    ptr->height=MAX_HEIGHT;
    ptr->width=0;
    ptr->next=NULL;
    ptr->last=NULL;
    return ptr;
}

//fails:
// void ConstructHead(struct puddle **tmp)
// {
//     printf("1:%p\n",tmp);
//     struct puddle *ptr;
//     ptr=(struct puddle*)malloc(sizeof(struct puddle));
//     ptr->height=MAX_HEIGHT;
//     ptr->width=0;
//     ptr->next=NULL;
//     ptr->last=NULL;
//     *tmp=ptr;
//     printf("2:%p\n",tmp);
//     return;
// }

//works:
// void ConstructHead(struct puddle *ptr)
// {
//     ptr->height=MAX_HEIGHT;
//     ptr->width=0;
//     ptr->next=NULL;
//     ptr->last=NULL;
//     return;
// }

void DoublyLinkLists(struct puddle *TmpCell,struct puddle *Ptr)
{
    TmpCell->next=Ptr->next;  // this node connects to the next
    Ptr->next=TmpCell;   // its previous node reconnects to it
    TmpCell->last=Ptr;   // this node connects to the previous one
    TmpCell->next->last=TmpCell;    // its next node connects to it
    return; 
}

void Delete(struct puddle *ptr)
{
    struct puddle *tmp;
    tmp=ptr;
    ptr->last->next=ptr->next;
    ptr->next->last=ptr->last;
    free(tmp);
    return;
}

void Out(long long a[],int len)
{
    for(int i=0;i<len;i++)
        printf("%lld\n",a[i]);
    return;
}

int main()
{
    int n,i;
    struct puddle *Left,*Right,*Ptr,*cur;
    Left=ConstructHead();
    Right=ConstructHead();
    // Left=(struct puddle*)malloc(sizeof(struct puddle));
    // Right=(struct puddle*)malloc(sizeof(struct puddle));
    // ConstructHead(&Left);
    // printf("3:%p\n",Left);
    // ConstructHead(&Right);
    Left->next=Right;   // Segmentation fault???
    Right->last=Left;
    Ptr=Left;
    cur=Left;
    int w,h;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        struct puddle *TmpCell;
        TmpCell=(struct puddle*)malloc(sizeof(struct puddle));
        TmpCell->id=i;
        scanf("%d %d",&w,&h);
        TmpCell->height=h;
        TmpCell->width=w;
        DoublyLinkLists(TmpCell,Ptr);
        Ptr=TmpCell;   //ptr moves to the current node

        if(cur->height>h) cur=TmpCell;    // start from the deepest puddle
    }

    long long total=0;
    struct puddle *tmp;
    while(cur->next->height!=cur->last->height)   // when there is more than 1 puddle left unfilled
    {
        time[cur->id]=total+cur->width;
        tmp=cur;
        // first calculate the time needed to fill this current puddle:
        if(cur->last->height>cur->next->height)
        {
            total+=cur->width*(cur->next->height-cur->height);
            cur->next->width+=cur->width;
            cur=cur->next;
            while(cur->next->height<cur->height)   // find the next puddle with smallest depth
                cur=cur->next;
        }
        else 
        {
            total+=cur->width*(cur->last->height-cur->height);
            cur->last->width+=cur->width;
            cur=cur->last;
            while(cur->last->height<cur->height)
                cur=cur->last;
        }       
        Delete(tmp);
        // second go to the next lowest plane
        if(cur->height<cur->last->height&&cur->height<cur->next->height) continue; //已在极小值处，水流不过去了
        else if(cur->last->height<cur->next->height)   // 向矮的一侧填充
            while(cur->last->height<cur->height)
                cur=cur->last;
        else if(cur->next->height<cur->last->height)
            while(cur->next->height<cur->height)
                cur=cur->next;
    }
    time[cur->id]=total+cur->width;  // dont forget the last one
    Out(time,n);

    return 0;
}