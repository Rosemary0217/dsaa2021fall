#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct AVLtree *Tree;
typedef char DATATYPE;

struct AVLtree{
    DATATYPE elem;
    Tree LeftChild;
    Tree RightChild;
    int height;
};

Tree Root;

int GetHeight(Tree node)     
// prevent the segmentation fault which might appear if the node we wanna directly get height is null
{
    if(node==NULL) return -1; 
    else return node->height;
}

int max(int a,int b){
    return a>b?a:b;
}

// 4 kinds of rotations:
Tree SingleRotateWithLeft(Tree node)
{
    Tree TmpCell=node->LeftChild;
    node->LeftChild=TmpCell->RightChild;
    TmpCell->RightChild=node;
    node->height=max(GetHeight(node->LeftChild),GetHeight(node->RightChild))+1;
    TmpCell->height=max(GetHeight(TmpCell->LeftChild),node->height)+1;

    return TmpCell;
}

Tree SingleRotateWithRight(Tree node)
{
    Tree TmpCell=node->RightChild;
    node->RightChild=TmpCell->LeftChild;
    TmpCell->LeftChild=node;
    node->height=max(GetHeight(node->LeftChild),GetHeight(node->RightChild))+1;
    TmpCell->height=max(GetHeight(TmpCell->RightChild),node->height)+1;

    return TmpCell;
}

Tree DoubleRotateWithLeft(Tree node)
{
    node->LeftChild=SingleRotateWithRight(node->LeftChild);
    return SingleRotateWithLeft(node);
}

Tree DoubleRotateWithRight(Tree node)
{
    node->RightChild=SingleRotateWithLeft(node->RightChild);
    return SingleRotateWithRight(node);
}

Tree Insert(Tree tree,char c)   
{
    if(tree==NULL)
    {
        tree=(Tree)malloc(sizeof(struct AVLtree));
        tree->elem=c;
        tree->LeftChild=NULL;
        tree->RightChild=NULL;
        tree->height=0;
    }
    else 
    {
        if(c<tree->elem) 
        {
            tree->LeftChild=Insert(tree->LeftChild,c);
            if(GetHeight(tree->LeftChild)-GetHeight(tree->RightChild)==2)
                if(c<tree->LeftChild->elem)
                    tree=SingleRotateWithLeft(tree);
                else 
                    tree=DoubleRotateWithLeft(tree);
        }
        else 
        {
            tree->RightChild=Insert(tree->RightChild,c);
            if(GetHeight(tree->RightChild)-GetHeight(tree->LeftChild)==2)
                if(c>tree->RightChild->elem)
                    tree=SingleRotateWithRight(tree);
                else 
                    tree=DoubleRotateWithRight(tree);
        }
        tree->height=max(GetHeight(tree->LeftChild),GetHeight(tree->RightChild))+1;
    }
    return tree;
}

// 3 traversing orders:
void preorder(Tree tree)
{
    if(tree)
    {
        printf("%c",tree->elem);
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
        printf("%c",T->elem);
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
        printf("%c",T->elem);
    }
    return;
}

//output after 90-degree rotation
void Output(Tree node,int depth)
{
    if (node->RightChild)
        Output(node->RightChild,depth+1);
    for (int i=0;i<depth;i++)
        printf("    ");
    printf("%c\n", node->elem);
    if (node->LeftChild)
        Output(node->LeftChild,depth+1);

    return;
}

int main()
{
    char c;
    while(1)
    {
        c=getchar();
        if(c=='\n') break;
        else Root=Insert(Root,c);
    }

    printf("Preorder: ");
    preorder(Root);
    printf("\n");

    printf("Inorder: ");
    inorder(Root);
    printf("\n");

    printf("Postorder: ");
    postorder(Root);
    printf("\n");

    printf("Tree:\n");
    Output(Root,0);

    return 0;
}