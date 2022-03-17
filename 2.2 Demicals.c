/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int data;
    struct node * next;
} NODE;

void output( NODE * );
void change( int, int, NODE * );

void change(int numerator, int denominator,NODE *head)
{
    int remainder,count=1,demical,mod;
    numerator*=10;     // divide in mathematical way
    demical=numerator/denominator;
    numerator-=demical*denominator;
    NODE *ptr;
    ptr=(NODE*)malloc(sizeof(NODE));
    ptr->next=head->next;
    head->next=ptr;
    ptr->data=demical;
    mod=numerator%denominator;
    while(count<50)
    {
        if(mod==0) return;
        struct node *q;
        q=(struct node*)malloc(sizeof(struct node));
        numerator*=10;
        demical=numerator/denominator;
        q->data=demical;
        numerator-=demical*denominator; 
        mod=numerator%denominator;
        count++;
        q->next=ptr->next;
        ptr->next=q;
        ptr=q;
    }

    return;
}

void output( NODE * head )  
{   int k=0;  
  
    printf("0.");  
    while ( head->next != NULL && k<50 )  
    {   printf("%d", head->next->data );  
        head = head->next;  
        k ++;  
    }  
    printf("\n");  
}  

int main()
{   int n, m;
	NODE * head;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc( sizeof(NODE) );
	head->next = NULL;
	head->data = -1;
	change( n, m, head );
	output( head );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */