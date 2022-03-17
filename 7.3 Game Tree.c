#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 200
#define MAX 10
#define LIMIT 10000
typedef struct TreeNode *PtrToNode,*Tree;
char str[MAX_LEN]={'\0'};
int depth=-1,tail=-1,flag=0,vis[10]={0},predepth=-1,illegal;
PtrToNode Root,Tmp,cur,parent[10]={NULL},lastnode[10]={NULL},last;

struct TreeNode{
    char data;
    int depth;
    int height;
    int win;
    PtrToNode FirstChild;
    PtrToNode NextSibling;
};

PtrToNode CreateNode(char ch,int dep)
{
    PtrToNode node=(PtrToNode)malloc(sizeof(struct TreeNode));
    node->data=ch;
    node->depth=dep;
    node->FirstChild=NULL;
    node->NextSibling=NULL;
    node->win=0;
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

void CreateLCRSTree()
{
    char ch;
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
            depth--;
        else
        {
            printf("%c\n",ch);
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
}

void Deal(Tree T)
{
    if(T==NULL) return;
    else
    {
        if(T->FirstChild==NULL) T->win=1;  //Must-win
        Deal(T->FirstChild);
        Deal(T->NextSibling);
        if(T->FirstChild)
        {
            PtrToNode p=T->FirstChild;
            int flag=1;
            while(p)
            {
                if(p->win==1)  
                {
                    flag=0;
                    break;
                }
                p=p->NextSibling;
            }
            if(flag) T->win=1;
        }
    }
    return;
}

int GetHeight(Tree T)
{
    if(T==NULL) return 0;
    else
    {
        int tmp=GetHeight(T->FirstChild),temp;
        if(tmp)
        {
            T=T->FirstChild;
            while(T)
            {
                temp=GetHeight(T->NextSibling);
                if(temp>tmp) tmp=temp;
                T=T->NextSibling;
            }
        }
        return tmp+1;
    }
}

Tree playeraction(Tree T)
{
    char move;
    int flag=0;
    illegal=1;
    printf("player:\n");
    scanf("%c",&move);
    getchar();
    PtrToNode p=T;
    if(p->FirstChild)
    {
        p=p->FirstChild;
        while(p)
        {
            if(p->data==move)
            {
                flag=1;
                break;
            } 
            p=p->NextSibling;
        }
    }
    if(flag) 
    {
        illegal=0;
        return p;
    }
    else 
    {
        printf("illegal move.\n");
        return T;
    }
}

Tree computeraction(Tree T)
{
    if(T->FirstChild==NULL) return T;
    int hmin=LIMIT,hmax=0;
    PtrToNode p1,p2,p=T->FirstChild;
    while(p)
    {
        p->height=GetHeight(p);
        if(p->win&&p->height<hmin)   
        {
            hmin=p->height;
            p1=p;
        }
        else if(p->height>hmax)   //没有必胜点
        {
            hmax=p->height;
            p2=p;
        }
        p=p->NextSibling;
    }
    if(hmin!=LIMIT) 
    {
        printf("computer: %c\n", p1->data);
        return p1;
    }
    else 
    {
        printf("computer: %c\n", p2->data);
        return p2;
    }
}

int main()
{
    int choice;
    char move;
    PtrToNode p1,p2; //p1 stands for the node player begins, p2 for computer
    
    //create tree first
    scanf("%s",str);
    CreateLCRSTree();
    Deal(Root);
    
    //game loop
    while(1)  
    {
        printf("Who play first(0: computer; 1: player )?\n");
        scanf("%d",&choice);
        getchar();
        //player plays first
        if(choice==1)
        {
            p1=Root;
            while(1)
            {
                illegal=1;
                while(illegal)
                    p2=playeraction(p1);
                if(p2->FirstChild==NULL) 
                {
                    printf("Congratulate, you win.\n");
                    break;
                }
                p1=computeraction(p2);
                if(p1->FirstChild==NULL)
                {
                    printf("Sorry, you lost.\n");
                    break;
                }
            } 
        }
        //computer plays first
        else
        {
            p2=Root;
            while(1)
            {
                illegal=1;
                p1=computeraction(p2);
                if(p1->FirstChild==NULL)
                {
                    printf("Sorry, you lost.\n");
                    break;
                }
                while(illegal)
                    p2=playeraction(p1);
                if(p2->FirstChild==NULL) 
                {
                    printf("Congratulate, you win.\n");
                    break;
                }
            }
        }//end of a round
        printf("Continue(y/n)?\n");
        if(getchar()=='n') break;
        else if(getchar()=='y') continue;
    }
    return 0;
}