#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100000
typedef struct BinaryTree *Tree;
char str[MAX_LEN];

struct BinaryTree{
    int vis;
    Tree LeftChild;
    Tree RightChild;
};

Tree ConstructNode()
{
    Tree node=(Tree)malloc(sizeof(struct BinaryTree));
    node->LeftChild=NULL;
    node->RightChild=NULL;
    node->vis=0;
    return node;
}

int main()
{
    int n,not=0,i,j;  // DON'T FORGET TO INITIALIZE!!!
    scanf("%d",&n);
    getchar();
    Tree ptr;
    Tree Root=ConstructNode();
    for(i=0;i<n;i++)
    {
        //memset(str,'\0',sizeof(str));
        scanf("%s",str);
        ptr=Root;
        for(j=0;str[j]!='\0';j++)
        {
            if(str[j]=='0')
            {
                if(ptr->LeftChild==NULL) // this path had not been traversed, it's new
                {
                    ptr->LeftChild=ConstructNode(); 
                    ptr=ptr->LeftChild;
                    if(str[j+1]=='\0') ptr->vis=1;   // the string terminates here
                }
                // the string has not terminated but this path already contains a string, or this string
                // is contained in a longer one
                else if(ptr->LeftChild->vis==1||str[j+1]=='\0')  
                {
                    not=1;
                    break;
                }
                else ptr=ptr->LeftChild;
            }   
            else
            {
                if(ptr->RightChild==NULL) // this path had not been traversed, it's new
                {
                    ptr->RightChild=ConstructNode(); 
                    ptr=ptr->RightChild;
                    if(str[j+1]=='\0') ptr->vis=1;   // the string terminates here
                }
                else if(ptr->RightChild->vis==1||str[j+1]=='\0')
                {
                    not=1;
                    break;
                }
                else ptr=ptr->RightChild;
            }
        }
        if(not)
        {
            printf("%s\n",str);
            break;
        }
    }
    if(!not) printf("YES\n");

    return 0;
}