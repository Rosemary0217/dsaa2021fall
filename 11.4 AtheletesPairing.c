#include <stdio.h>
#include <stdlib.h>

#define MAX 13

int P[MAX][MAX],Q[MAX][MAX],PQ[MAX][MAX]={0},n,ans=-1,tmp=0,pair[MAX]={0},max[MAX]={0};

void dfs(int depth)
{
    int j;
    if(depth==n)
    {
        ans=ans>tmp?ans:tmp;
        return;
    }
    /* pruning gives us much higher efficiency(TLE->0.02sec).
       Here we are using the 'max' array w 've calculated before, to check if current selection
       cannot provide an answer better than current best answer, then we do not need to continue.*/
    else if(tmp+max[n-1]-max[depth-1]<ans) 
        return;
    for(j=0;j<n;j++)
    {
        if(!pair[j])
        {
            pair[j]=1;
            tmp+=PQ[depth][j];
            dfs(depth+1);
            pair[j]=0;
            tmp-=PQ[depth][j];
        }
    }
    return;
}


int main()
{
    int i,j;
    scanf("%d",&n);
    //男配女
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&P[i][j]);
    //女配男
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            scanf("%d",&Q[i][j]);
            PQ[j][i]=Q[i][j]*P[j][i];
        }
    //一开始还以为是乘法次数过多，结果单加这个0.997->0.998
    //贪心：对每个男运动员选取最佳拍档（可能重复选择）
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            max[i]=max[i]>PQ[i][j]?max[i]:PQ[i][j];
        if(i>0)
            max[i]+=max[i-1];
    }
    dfs(0);
    printf("%d\n",ans);
}