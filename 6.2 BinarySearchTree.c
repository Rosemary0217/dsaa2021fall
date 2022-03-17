#include <stdio.h>
#include <stdlib.h>

typedef struct tree *Tree;

struct tree{
    int num;
    Tree LeftChild;
    Tree RightChild;
};

Tree Root;

int Search(Tree tree,int target)
{
    if(tree==NULL) return 0;
    if(target==tree->num) return 1;
    else if(target<tree->num) Search(tree->LeftChild,target);
    else Search(tree->RightChild,target);
}

Tree Insert(Tree tree,int datum)   
{
    if(tree==NULL)
    {
        Tree tmp=(Tree)malloc(sizeof(struct tree));
        tmp->num=datum;
        tmp->LeftChild=NULL;
        tmp->RightChild=NULL;
        tree=tmp;
    }
    else 
    {
        if(datum<tree->num) tree->LeftChild=Insert(tree->LeftChild,datum);
        else tree->RightChild=Insert(tree->RightChild,datum);
    }
    return tree;
}

void inorder1(Tree T,int degree)
{
    if(T)
    {
        inorder1(T->LeftChild,degree+1);
        for(int i=0;i<degree;i++)
            printf("    ");
        printf("%d\n",T->num);
        inorder1(T->RightChild,degree+1);
    }
    return;
}

void inorder2(Tree T)
{
    if(T)
    {
        inorder2(T->LeftChild);
        printf(" %d",T->num);
        inorder2(T->RightChild);
    }
    return;
}

int main()
{
    int num;
    while(1)
    {
        scanf("%d",&num);
        if(num==0) break;
        if(Search(Root,num)) continue;
        else Root=Insert(Root,num);
    }
    inorder1(Root,0);
    printf("\n");
    inorder2(Root);
    printf("\n");

    return 0;
}