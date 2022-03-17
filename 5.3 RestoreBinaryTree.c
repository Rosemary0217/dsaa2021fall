#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct BinaryTree *Tree;

struct BinaryTree{
    char ch;
    Tree LeftChild;
    Tree RightChild;
};

char in[MAX_LEN],post[MAX_LEN];
Tree treequeue[MAX_LEN/2];
int head=0,tail=0;

// void initailizequeue()
// {
//     for(int i=0;i<MAX_LEN/2;i++)
//         treequeue[i]=NULL;
//     return;
// }

int position(char elem,char *in,int len)
{
    for(int i=0;i<len;i++)
        if(*(in+i)==elem) return i;
}

Tree ConstructTree (char *inhead,char *posthead,int len)
{
    if(len<=0) return NULL;  //树非空
    Tree T=(Tree)malloc(sizeof(struct BinaryTree));
    T->ch=posthead[len-1];
    T->LeftChild=NULL;
    T->RightChild=NULL;
    int pos=position(posthead[len-1],inhead,len);

    //cut the strings into 2 halves
    if(pos>0)     
        T->LeftChild=ConstructTree(inhead,posthead,pos);   //in中前pos个都<=root元素
        //pos作为len传进去，保证了下次递归调用时post只看第len个
    if(pos<len-1)
        T->RightChild=ConstructTree(inhead+pos+1,posthead+pos,len-pos-1);

    return T;
}

void push(Tree treenode)
{
    treequeue[++tail]=treenode;
}

Tree TopThenPop()
{
    return treequeue[++head];
}

int IsEmpty()
{
    return tail==head;
}

void LayerByLayer(Tree root)   //implement with a queue
{
    //initailizequeue();
    Tree TmpCell;
    push(root);
    while(!IsEmpty())
    {
        TmpCell=TopThenPop();
        printf("%c",TmpCell->ch);
        if(TmpCell->LeftChild) push(TmpCell->LeftChild);
        if(TmpCell->RightChild) push(TmpCell->RightChild);
    }
    printf("\n");
    return;
}

int main()
{
    scanf("%s",in);
    scanf("%s",post);
    LayerByLayer(ConstructTree(in,post,strlen(in)));
    
    // Tree Root;
    // Root=ConstructTree(in,post,strlen(in));

    // LayerByLayer(Root);
    return 0;
}