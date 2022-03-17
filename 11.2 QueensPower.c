//Backtracking algorithm: place M queens on a NxN chessboard without any contradiction
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 13

int n,m,count=0,queen[MAX],dominance[MAX][MAX];

void mark(int row,int col)   //标出每个皇后的势力范围
{
    int i,j;
    for(i=1;i<=n;i++)
    {
        dominance[row][i]=1;
        dominance[i][col]=1;
    }
    for(i=row,j=col;i>=1&&j>=1;i--,j--)
        dominance[i][j]=1;
    for(i=row,j=col;i<=n&&j<=n;i++,j++)
        dominance[i][j]=1;
    for(i=row,j=col;i<=n&&j>=1;i++,j--)
        dominance[i][j]=1;
    for(i=row,j=col;i>=1&&j<=n;i--,j++)
        dominance[i][j]=1;
    return;
}

int dominate(int last_row)
{
    memset(dominance,0,sizeof(dominance));
    for(int i=1;i<last_row;i++)
        if(queen[i]!=-1)
            mark(i,queen[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(dominance[i][j]==0)
                return 0;
    return 1;
}

void dfs(int row,int remainder)
{
    if(remainder==0&&dominate(row))   //每次到leaf都要先check一遍
    {
        count++;
        return;
    }
    int i,j,flag;
    for(i=1;i<=n;i++)  //放的话，尝试每一个可能的col index
    {
        flag=1;
        for(j=1;j<row;j++)   //遍历之前已经放过的row-1行
        {
            if(queen[j]!=-1)  //如果第j行有放
            {
                if(queen[j]==i||queen[j]-i==j-row||queen[j]-i==row-j)
                {
                    flag=0;    //放在这一列会冲突
                    break;
                }
            }
        }
        if(flag&&n>=row+remainder-1)    //不冲突：这一行放然后继续搜索
        {
            queen[row]=i;
            dfs(row+1,remainder-1);   //下一行继续
            queen[row]=-1;
        }
    }
    if(n>=row+remainder)    //这行不放
        dfs(row+1,remainder);      
    return;
}

int main()
{
    scanf("%d %d",&n,&m);
    memset(queen,-1,sizeof(queen));
    dfs(1,m);
    printf("%d\n",count);
    return 0;
}