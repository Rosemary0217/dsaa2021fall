#include <stdio.h>
#include <stdlib.h>

#define MAX 100
typedef struct entry data;

struct entry{
    int key;
    int id;
};
data records[MAX];
int size;

// sort the array according to keys' value in an ascending order
int compare(const void*a, const void* b)
{
    struct entry m=*(struct entry*)a;
    struct entry n=*(struct entry*)b;
    return m.key-n.key;
}

void output()
{
    for(int i=0;i<size;i++)
        printf("(%d %d)",records[i].key,records[i].id);
    printf("\n");
    return;
}

void BinarySearch(int head,int tail,int target)
{
    if(head==tail)
    {
        if(records[head].key==target) printf("(%d %d)\n",records[head].key,records[head].id);
        else printf("error\n");
        return;
    }
    int midpos=(head+tail)/2;
    int median=records[midpos].key;
    if(median==target) printf("(%d %d)\n",records[midpos].key,records[midpos].id);
    else if(median>target) BinarySearch(head,midpos-1,target);
    else BinarySearch(midpos+1,tail,target);
    return;
}

int main()
{
    int i,target;
    scanf("%d",&size);
    for(i=0;i<size;i++)
    {
        scanf("%d",&records[i].key);
        scanf("%d",&records[i].id);
    }
    scanf("%d",&target);
    qsort(records,size,sizeof(struct entry),compare);
    output();
    BinarySearch(0,size-1,target);

    return 0;
}