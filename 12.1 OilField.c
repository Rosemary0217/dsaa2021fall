#include <stdio.h>
#include <stdlib.h>

int well_y[2000010];

int Partition(int left,int right)
{
    int i,j,pivot,tmp=0;
    pivot=well_y[left];
    i=left;
    for(j=left+1;j<=right;j++)
    {
        if(well_y[j]<=pivot)
        {
            i++;
            tmp=well_y[i];
            well_y[i]=well_y[j];
            well_y[j]=tmp;
        }
    }
    tmp=well_y[i];
    well_y[i]=well_y[left];
    well_y[left]=tmp;
    return i;
}

int select(int left,int right,int k)
{
    int r,rank;
    if(left==right) 
        return well_y[left];
    r=Partition(left,right);
    rank=r-left+1;
    if(rank==k)
        return well_y[r];
    else if(k<rank)
        return select(left,r-1,k);
    else return select(r+1,right,k-rank);
}

int main()
{
    int x,y,i=0,ans;
    while(scanf("%d,%d",&x,&y)!=EOF)
        well_y[++i]=y; 
    if(i%2==0) ans=select(1,i,i/2);
    else ans=select(1,i,(i+1)/2);
    printf("%d\n",ans);
}