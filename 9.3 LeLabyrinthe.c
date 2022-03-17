#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101

typedef struct fieldNode field;
typedef struct coordinate coor;

//1 for wall, 0 for path
struct fieldNode{
    int vis;
    int isWall;
};

struct coordinate{
    int x;
    int y;
};

field labyrinthe[MAX_SIZE][MAX_SIZE];
int size,surroundings[4][2]={0,-1,0,1,-1,0,1,0},min=1224; //上下左右
coor path[MAX_SIZE]={},tmp[MAX_SIZE]={};

void noSolution()
{
    printf("There is no solution!\n");
    return;
}

void dfs(int row,int col,int step)
{
    //recursion base
    if(row==size&&col==size)
    {          
        //取等号：右优先于下
        if(min>=step)
        {
            min=step;
            for(int i=0;i<step;i++)
            {
                path[i].x=tmp[i].x;
                path[i].y=tmp[i].y;
            }
        }
        return;
    }
    int x,y,i,j;
    for(i=0;i<4;i++)
    {
        x=row+surroundings[i][0];
        y=col+surroundings[i][1];
        if(1<=x&&x<=size&&y>=1&&y<=size&&labyrinthe[x][y].isWall==0&&labyrinthe[x][y].vis==0)
        {
            labyrinthe[x][y].vis=1;
            tmp[step].x=x;
            tmp[step].y=y;
            dfs(x,y,step+1);
            labyrinthe[x][y].vis=0;
        }
    }
    return;
}

void printPath()
{
    printf("<1,1> ");
    for(int i=0;i<min;i++)
        printf("<%d,%d> ",path[i].x,path[i].y);
    printf("\n");
    return;
}

int main()
{
    int rowSize,colSize,i,j;
    scanf("%d %d",&rowSize,&colSize);
    size=rowSize;

    //get the maze
    for(i=1;i<=rowSize;i++)
        for(j=1;j<=colSize;j++)
        {
            scanf("%d",&labyrinthe[i][j].isWall);
            labyrinthe[i][j].vis=0;
        }
            
    //出口被堵
    if(labyrinthe[1][1].isWall==1||labyrinthe[size][size].isWall==1)
    {
        noSolution();
        return 0;
    }
    dfs(1,1,0);
    if(min==1224) noSolution();
    else printPath();

    return 0;
}