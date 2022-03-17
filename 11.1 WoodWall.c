#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

typedef struct{
    long long int height;
    int id,previousHigherBoardNum;
}woodenBoard; 

woodenBoard board[MAX],stack[MAX],tmp;
long long int ans;
int top;

long long int max(long long int a,long long int b){
    return a>b?a:b;
}

void push(woodenBoard a){
    stack[++top]=a;
}

woodenBoard pop(){
    return stack[top--];
}

woodenBoard Top(){
    return stack[top];
}

int isEmpty(){
    return top==0;
}

int main()
{
    int i,n;
    while(1)
    {
        scanf("%d",&n);
        if(n==0) return 0;
        top=0;
        ans=0;
        for(i=1;i<=n;i++)
        {
            scanf("%d",&board[i].height);
            board[i].id=i;
            board[i].previousHigherBoardNum=0;
            if(isEmpty()||Top().height<=board[i].height)
                push(board[i]); 
            else 
            {
                //单调递减栈，利用了大小关系的传递性
                while(!isEmpty()&&Top().height>board[i].height)
                {
                    tmp=pop();
                    //更新这块板子之前，新栈顶元素之后有几块连续的板子比这块高（新栈顶一定不比旧栈顶高）
                    board[i].previousHigherBoardNum+=(tmp.previousHigherBoardNum+1);
                    //比较： 当前的答案更还是用旧栈顶的7木板作为最低板最好
                    ans=max(ans,(i-tmp.id+tmp.previousHigherBoardNum)*tmp.height);
                }
                push(board[i]);
            }           
        }
        while(!isEmpty())
        {
            tmp=pop();
            ans=max(ans,(n-tmp.id+1+tmp.previousHigherBoardNum)*tmp.height);
        }
        printf("%lld\n",ans);
    }
}