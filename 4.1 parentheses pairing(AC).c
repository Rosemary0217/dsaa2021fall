#include <stdio.h>
#include <stdlib.h>

char stack[10000]={},tail=0;

void push(char ch){
    stack[++tail]=ch;
    return;
}

char top(){
    return stack[tail];
}

void pop(){
    tail--;
    return;
}

int main()
{
    char ch;
    while(1)
    {
        ch=getchar();
        if(ch=='\n') break;
        switch(ch)
        {
            case('('):
                push(ch);
                break;
            case(')'):
                if(top()!='(')
                {
                    printf("Match false!\n");
                    return 0;
                }
                else pop(); 
                break;
            case('['):
                push(ch);
                break;
            case(']'):
                if(top()!='[')
                {
                    printf("Match false!\n");
                    return 0;
                } 
                else pop(); 
                break;
            default: break;
        }
    }
    if(tail==0) printf("Match succeed!\n");
    else printf("Match false!\n");

    return 0;
}