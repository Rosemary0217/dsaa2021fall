#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 105

typedef struct Polynomial{
    int coefficient[MAX_DEGREE];
    // Polynomial *next;
}Polynomial;

void Initialize(Polynomial *Poly)
{
    for(int i=0;i<MAX_DEGREE;i++)
        Poly->coefficient[i]=0;
    return;
}

void AddPolynomial2(Polynomial *Poly1,Polynomial *Poly2,Polynomial *Sum,int max)
{
    Initialize(Sum);
    for(int i=0;i<=max;i++)
        Sum->coefficient[i]=Poly1->coefficient[i]+Poly2->coefficient[i];
    return;
}

// void AddPolynomial3(Polynomial *Poly1,Polynomial *Poly2,Polynomial *Poly3,Polynomial *Sum,int max)
// {
//     Initialize(Sum);
//     for(int i=0;i<=max;i++)
//         Sum->coefficient[i]=Poly1->coefficient[i]+Poly2->coefficient[i]+Poly3->coefficient[i];
//     return;
// }

void AddPolynomial3(Polynomial *Poly3,Polynomial *Sum,int max)
{
    for(int i=0;i<=max;i++)
        Sum->coefficient[i]+=Poly3->coefficient[i];
    return;
}

void Output(Polynomial *ans,int max)
{
    int count=0;
    for(int i=0;i<=max;i++)
        if(ans->coefficient[i]!=0) 
            count++;
    if(count==0) 
    {
        printf("<0,0>\n");
        return;
    }
     for(int i=0;i<=max;i++)
        if(ans->coefficient[i]!=0)
        {
            printf("<%d,%d>",ans->coefficient[i],i);
            count--;
            if(count) printf(",");
            else 
            {
                printf("\n");
                return;
            }
        }    
}

int main()
{
    int i,j,n,tmp,a,b,max=0;
    Polynomial *Poly1,*Poly2,*Poly3,*Sum,*TmpCell;
    // Poly1=(Polynomial*)malloc(sizeof(Polynomial));
    // Poly2=(Polynomial*)malloc(sizeof(Polynomial));
    // Poly3=(Polynomial*)malloc(sizeof(Polynomial));
    Sum=(Polynomial*)malloc(sizeof(Polynomial));
    scanf("%d",&i);
    if(i==0) return 0;
    for(i=0;i<3;i++)
    {
        TmpCell=(Polynomial*)malloc(sizeof(Polynomial));
        Initialize(TmpCell);
        scanf("%d",&n);
        for(j=1;j<=n;j++)
        {
            scanf("%d %d",&a,&b);
            TmpCell->coefficient[b]=a;
            if(max<b) max=b;
        }
        if(i==0) Poly1=TmpCell;
        else if(i==1) Poly2=TmpCell;
        else Poly3=TmpCell;
        Output(TmpCell,max);
    }
    AddPolynomial2(Poly1,Poly2,Sum,max);
    Output(Sum,max);
    AddPolynomial3(Poly3,Sum,max);
    Output(Sum,max);

    return 0;
}