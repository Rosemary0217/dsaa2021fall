#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1500

int edge[MAX][MAX]={},dp[MAX][2]={},vis[MAX]={0};

int min(int a,int b)
{
    return a<b?a:b;
}

void dfs(int root)
{
    vis[root]=1;
    int i=0;
    while(edge[root][i]!=-1)
    {
        if(!vis[edge[root][i]])
        {
            dfs(edge[root][i]);
            //这个节点设置了士兵，但是注意不能在这里加1，否则有几个edge就加了几次，会重复
            dp[root][0]+=min(dp[edge[root][i]][0],dp[edge[root][i]][1]);  
            //这个节点不设置士兵，必须它的每个子节点都设置才能看到 
            dp[root][1]+=dp[edge[root][i]][0];   
        }
        i++;
    }
    dp[root][0]++;
    return;
}

int main()
{
    int m,node,num,i,n,num_of_nodes,root=0;
    while(scanf("%d",&num_of_nodes)!=EOF)
    {
        memset(edge,0,sizeof(edge));
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        for(int j=0;j<num_of_nodes;j++)
        {
            scanf("%d:(%d)",&node,&num);
            for(i=0;i<num;i++)
            {
                scanf("%d",&n);
                edge[node][i]=n;
            }
            edge[node][num]=-1;
            if(j==0) root=node;
        }
        dfs(root);
        printf("%d\n",min(dp[root][0],dp[root][1]));
    }
    return 0;
}