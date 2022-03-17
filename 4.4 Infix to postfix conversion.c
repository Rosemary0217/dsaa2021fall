// refernce: page74-76 of Data Structure and Algorithm Analysis in C by Mark Allen Weiss
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

char stack[MAX_LEN];
int tail;

void MakeEmpty(){
    tail=0;
}

void push(char ch){
    stack[++tail]=ch;
}

void pop(){
    tail--;
}

char top(){
    return stack[tail];
}

int IsEmpty(){
	if(tail==0) return 1;
    else return 0;
}

void PrintOperator(){
    printf("%c",stack[tail--]);
}

int main()
{
    int i,j,n;
    char ch;
    scanf("%d\n",&n);
    for(i=0;i<n;i++)
    {
        MakeEmpty();
        while((ch=getchar())&&ch!='#')    
        {
            if(ch>='a'&&ch<='z'||ch>='A'&&ch<='Z')    // if ch is an operand, output it
                printf("%c",ch);
            else if(ch=='(')   // if we encounter the left parenthesis, since it has the highest priority, push it into the stack
                push(ch);
            else if(ch==')')  
            {
                while(top()!='(')
                    PrintOperator();
                pop();   // do not output the left parenthesis, just delete it
            }
            else if(IsEmpty()) push(ch);
            else if(ch=='^')
            {
                while(!IsEmpty()&&top()!='*'&&top()!='/'&&top()!='+'&&top()!='-')
                {
                	if(top()=='('||top()=='^') break;    // continuous exponential operations have different precedence!!!
                	else PrintOperator();
				}
                push(ch);
            }
            else if(ch=='*'||ch=='/')
            {
                while(!IsEmpty()&&top()!='+'&&top()!='-')
                {
                	if(top()=='(') break;
                	else PrintOperator();
				}
                push(ch);
            }
            else
            {
                while(!IsEmpty())
                {
                	if(top()=='(') break;
                	else PrintOperator();
				}
                push(ch);
            }
        }
        getchar();    // exclude '\n' from the input
        while(!IsEmpty())
            PrintOperator();
        printf("\n");
    }

    return 0;
}

