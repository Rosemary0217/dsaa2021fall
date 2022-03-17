#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[210];

int count()
{
    int counter=0,in=0,out=0;
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='+') 
        {
            counter++;
            in=in>counter?in:counter;
        }
        else 
        {
            counter--;
            out=out<counter?out:counter;
        }
    }
    return in-out;
}

int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        memset(str,'\0',sizeof(str));
        scanf("%s",str);
        printf("%d\n",count());
    }
    return 0;
}