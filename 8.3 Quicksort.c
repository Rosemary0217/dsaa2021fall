#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CUTOFF 5
#define MAX 100
#define MAX1 20

int a[MAX],size=0,sizee=0,medians[MAX1]={0};

void swapinarray(int m,int n)
{
    int tmp=a[m];
    a[m]=a[n];
    a[n]=tmp;
    return;
}

void InsertionSort(int arr[],int len)
{
    int j,pass,tmp;
    for(pass=1;pass<=len-1;pass++)
    {
        tmp=arr[pass];
        for(j=pass;j>0&&arr[j-1]>tmp;j--)
            arr[j]=arr[j-1];
        arr[j]=tmp;
    }
    return;
}

int Median3(int left,int right)
{
    //sort the 3 numbers
    int mid=(left+right)/2;
    if(a[left]>a[mid]) swapinarray(left,mid);
    if(a[left]>a[right]) swapinarray(left,right);
    if(a[mid]>a[right]) swapinarray(mid,right);

    medians[sizee++]=a[mid];
    //swap with the 2nd elem from right!!
    swapinarray(mid,right-1);
    return a[right-1];
}

void QuickSort(int left,int right)
{
    int i,j,pivot;
    if(left+CUTOFF<=right)
    {
        pivot=Median3(left,right);
        i=left;
        j=right-1;
        while(1)
        {
            while(a[++i]<pivot) {}
            while(a[--j]>pivot) {}
            if(i<j) swapinarray(i,j);
            else break;
        }
        //put the pivot back
        swapinarray(i,right-1);
        QuickSort(left,i-1);
        QuickSort(i+1,right);
    }
    else InsertionSort(a+left,right-left+1);

    return;
}

int main()
{
    char tmp[MAX];
    int i;
    while(1)
    {
        memset(tmp,'0',sizeof(tmp));
        scanf("%s",tmp);
        if(strcmp(tmp,"#")==0) break;
        else a[size++]=atoi(tmp); 
    }

    QuickSort(0,size-1);
    printf("After Sorting:\n");
    for(i=0;i<size;i++)
        printf("%d ",a[i]);
    printf("\n");

    printf("Median3 Value:\n");
    if(sizee==0) printf("none\n");
    else
    {
        for(i=0;i<sizee;i++)
            printf("%d ",medians[i]);
        printf("\n");
    }
    
    return 0;
}