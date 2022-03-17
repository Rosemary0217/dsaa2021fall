#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct tree *Tree;

struct tree{
    char ch;
    Tree LeftChild;
    Tree RightChild;
};

char str[MAX];
Tree Root;
int num_of_leaves=0;

Tree ConstructNode(char ch)
{
    Tree node;
    node=malloc(sizeof(struct tree));
    node->LeftChild=NULL;
    node->RightChild=NULL;
    node->ch=ch;
    return node;
}

// Tree Insert(Tree tree,char ch)   //不是完全二叉树...
// {
//     if(tree==NULL)
//     {
//         Tree tmp=(Tree)malloc(sizeof(struct Tree));
//         tmp->ch=ch;
//         tmp->LeftChild=NULL;
//         tmp->RightChild=NULL;
//         tree=tmp;
//     }
//     else 
//     {
//         if(ch<tree->ch) tree->LeftChild=Insert(tree->LeftChild,ch);
//         else tree->RightChild=Insert(tree->RightChild,ch);
//     }
//     return tree;
// }

void CreateTree(Tree T,int root_index)  //传进来的是按照从1开始编号(树上的)
{
    int lc_index=2*root_index,rc_index=2*root_index+1;
    char lchild=str[lc_index-1],rchild=str[rc_index-1];  //本来左儿子下标是父节点2倍，但由于字符串从0开始要减一
    if(lchild=='#'||lchild=='\0') T->LeftChild=NULL;
    else 
    {
        T->LeftChild=ConstructNode(lchild);
        CreateTree(T->LeftChild,lc_index);
    }
    if(rchild=='#'||rchild=='\0') T->RightChild=NULL;
    else 
    {
        T->RightChild=ConstructNode(rchild);
        CreateTree(T->RightChild,rc_index);
    }
    if(T->LeftChild==NULL&&T->RightChild==NULL) //边建树边数叶子
        num_of_leaves++;
    return;
}

void outputTree(Tree tree,int depth)
{
    if(tree)
    {
        for(int i=0;i<depth;i++)
            printf("    ");
        printf("%c\n",tree->ch);
        outputTree(tree->LeftChild,depth+1);
        outputTree(tree->RightChild,depth+1);
    }
    return;
}

void preorder(Tree tree)
{
    if(tree)
    {
        printf("%c",tree->ch);
        preorder(tree->LeftChild);
        preorder(tree->RightChild);
    }
    return;
}

void inorder(Tree T)
{
    if(T)
    {
        inorder(T->LeftChild);
        printf("%c",T->ch);
        inorder(T->RightChild);
    }
    return;
}

void postorder(Tree T)
{
    if(T)
    {
        postorder(T->LeftChild);
        postorder(T->RightChild);
        printf("%c",T->ch);
    }
    return;
}

void swap(Tree T)
{
    Tree TmpCell;
    if(T)
    {
        TmpCell=T->LeftChild;
        T->LeftChild=T->RightChild;
        T->RightChild=TmpCell;
        swap(T->LeftChild);
        swap(T->RightChild);
    }
    return;
}

int main()
{
    gets(str);
    Root=ConstructNode(str[0]);
    CreateTree(Root,1);

    printf("BiTree\n");
    outputTree(Root,0);

    printf("pre_sequence  : ");
    preorder(Root);
    printf("\n");

    printf("in_sequence   : ");
    inorder(Root);
    printf("\n");

    printf("post_sequence : ");
    postorder(Root);
    printf("\n");

    printf("Number of leaf: %d\n",num_of_leaves);


    swap(Root);

    printf("BiTree swapped\n"); 
    outputTree(Root,0);

    printf("pre_sequence  : ");
    preorder(Root);
    printf("\n");

    printf("in_sequence   : ");
    inorder(Root);
    printf("\n");

    printf("post_sequence : ");
    postorder(Root);
    printf("\n");
    
    return 0;
}
