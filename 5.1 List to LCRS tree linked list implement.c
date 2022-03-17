#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // can be adjusted according to the problem

typedef struct TreeNode *PtrToNode;

struct TreeNode{
    char data;
    int depth;
    int vis;
    PtrToNode FirstChild;
    PtrToNode NextSibling;
};

PtrToNode Root;
int count[MAX];

PtrToNode CreateNode(char ch,int dep)
{
    PtrToNode node=(PtrToNode)malloc(sizeof(struct TreeNode));
    node->data=ch;
    node->depth=dep;
    node->FirstChild=NULL;
    node->NextSibling=NULL;
    node->vis=0;
    return node;
}

void InsertAsChild(PtrToNode parent,PtrToNode new)
{
    parent->FirstChild=new;
    return;
}

void InsertAsSibling(PtrToNode LastSibling,PtrToNode new)
{
    LastSibling->NextSibling=new;
    return;
}

// void Output(PtrToNode p)
// {
//     if(p!=NULL)
//     {
//         if(!p->vis)
//         {
//             for(int i=0;i<p->depth;i++)
//                 printf("    ");    // tab before printing out each layer
//             printf("%c\n",p->data);
//             p->vis=1;
//         }
//         for(PtrToNode c=p->FirstChild;c!=NULL;c=c->FirstChild)
//             Output(c);
//         Output(p->NextSibling);
//     }
//     return; 
// }

//better output method!!!
void Output(PtrToNode p,int depth)
{
    if(p!=NULL)
    {
        for(int i=0;i<depth;i++)
            printf("    ");    // tab before printing out each layer
        printf("%c\n",p->data);
        for(PtrToNode c=p->FirstChild;c!=NULL;c=c->NextSibling) //!!!!!!!!!
            Output(c,depth+1);   // sort of like layer by layer
    }
    return; 
}

void CountDegree(PtrToNode T)
{
    int degree=0;
    if(T!=NULL)
    {
        for(PtrToNode tmp=T->FirstChild;tmp;tmp=tmp->NextSibling)
            degree++;
        count[degree]++;
        CountDegree(T->NextSibling);
        CountDegree(T->FirstChild);
    }
    return;
}

void PrintDegree()
{
    int i,flag=0;
    for(i=MAX-1;i>=0;i--)
        if(count[i]>0) 
        {
            printf("Degree of tree: %d\n",i);
            flag=i;
            break;
        }
    if(i==-1) 
    {
        printf("Degree of tree: 0\n");
    }
    for(int i=0;i<=flag;i++)
        printf("Number of nodes of degree %d: %d\n",i,count[i]);
    return;
}

int main()
{
    char str[MAX],ch;
    int depth=-1,tail=-1,flag=0,vis[10]={0},predepth=-1;
    PtrToNode Tmp,cur,parent[10]={NULL},lastnode[10]={NULL},last;
    memset(count,0,sizeof(count));
    gets(str);
    for(int i=0;str[i]!='\0';i++)
    {
        ch=str[i];
        if(ch==','||ch==' ') continue;
        else if(ch=='(')
        {
            depth++;
            if(depth>0&&depth>predepth) 
                flag=1;  // we are on a new layer and the indicator is marked as true
        }
        else if(ch==')')
        {
            depth--;
        }
        else
        {
            cur=CreateNode(ch,depth);
            if(depth==0)
                Root=cur;
            else 
            {
                if(flag==1)
                {
                    InsertAsChild(lastnode[depth-1],cur);
                    flag=0;
                }
                else if(flag==0) 
                    InsertAsSibling(lastnode[depth],cur);
            }   
            lastnode[depth]=cur; 
            predepth=depth;    // record the current depth and compare with others
        }
    }

    // Output(Root);
    Output(Root,0);
    CountDegree(Root);
    PrintDegree();
    return 0;

}

