#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 500
#define FAIL 20011224

char str[MAX_LEN];
char precedence[9][9]={  
    {'>','>','<','<','<','>','>','<','<'},  
    {'>','>','<','<','<','>','>','<','<'}, 
    {'>','>','>','>','<','>','>','<','>'},  //相同两个运算符若处在前后两不同位置,其优先性也随之变化  
    {'>','>','>','>','<','>','>','<','>'},   
    {'<','<','<','<','<','=','N','<','<'},    
    {'>','>','>','>','N','>','>','>','>'},    
    {'<','<','<','<','<','N','=','<','<'},    
    {'>','>','>','>','<','>','>','<','>'},  
    {'>','>','>','>','<','>','>','<','>'}     
};
char oprt[9]={'+','-','*','/','(',')','#','^','%'};  

void push_operator(char ch);

char compare(char a,char b)
{
    int ca,cb;
    for(int k=0;k<9;k++)
    {
        if(a==oprt[k]) ca=k;
        if(b==oprt[k]) cb=k;
    }
    return precedence[ca][cb];
}

struct Operands{
    int stack[MAX_LEN];
    int tail;
};

struct Operators{
    char stack[MAX_LEN];
    int tail;
};

struct Operands operand;
struct Operators operator;

void MakeEmpty()
{
    operand.tail=-1;
    operator.tail=-1;
    memset(operator.stack,'\0',sizeof(operator.stack));
    memset(operand.stack,0,sizeof(operand.stack));
    push_operator('#');
    return;
}

void push_operand(int x){
    operand.stack[++operand.tail]=x;
}

void push_operator(char op){
    operator.stack[++operator.tail]=op;
}

int pop_operand(){     // delete the operand on top and return it (for the convenience of reading data)
    return operand.stack[operand.tail--];
}

void pop_operator(){   // delete the operator on top
    operator.tail--;
}

char top_operator(){   // see the operator on top
    return operator.stack[operator.tail];
}

int IsOperatorStackEmpty(){
    return operator.tail==0;
}

int IsOperandStackEmpty(){
    return operand.tail==0;
}

int IsAnOperator(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='%'||ch=='^') return 1;
    else return 0;
}

int IsANum(char ch)
{
    if(ch<='9'&&ch>='0') return 1;
    else return 0;
}

// int operate(int a,int b,char ch)
// {
//     switch(ch)
//     {
//         case '+':   return a+b; break;
//         case '-':   return a-b; break;
//         case '/':
//                     if(b==0)
//                     {
//                         printf("Divide 0.\n");
//                         return FAIL;
//                     }
//                     else return a/b;
//                     break;
//         case '*':   return a*b; break;
//         case '%':   return a%b; break;
//         case '^':   if(b>=0) return pow(a,b);
//                     else 
//                     {
//                         printf("error.\n");
//                         return FAIL;
//                     }
//                     break;
//     }
// }

int operate(int a,int b,char ch)
{
    if(ch=='+') return a+b;
    else if(ch=='-') return a-b; 
    else if(ch=='/')
    {
        if(b==0)
        {
            printf("Divide 0.\n");
            return FAIL;
        }
        else return a/b;
    }
    else if(ch=='*') return a*b; 
    else if(ch=='%') return a%b; 
    else if(ch=='^') 
    {
        if(b>=0) return pow(a,b);
        else 
        {
            printf("error.\n");
            return FAIL;
        }             
    }
}

int main()
{
    int n,i,j,count,num_of_continuous_operator;
    int len,ans,vis=0;
    int illegal,type=2,sign_of_ans=1,sign_of_operand=1;
    //type=0 stands for last input character being a number, type=1 for left parenthesis, o.w. type=2 

    scanf("%d",&n);
    while(n--)
    {
        MakeEmpty();
        vis=0;
        // gets(str);
        // getchar();
        scanf("%s",str);
        len=strlen(str);
        strcat(str,"#");
        illegal=0;
        j=0;
        int flag=0;
        if(len==1||len==2)
        {
            printf("error.\n");
            continue;
        }
        for(i=0;i<len-2;i++)   // 3 continuous operators->illegal input
        {
            if(IsAnOperator(str[i]))  
                if(IsAnOperator(str[i+1])&&IsAnOperator(str[i+2]))
                {
                    printf("error.\n");
                    illegal=1;
                    break;
                }
        }
        if(illegal) continue;
        else    // if the input seems legal
        {
            while(str[j]!='#'||top_operator()!='#')
            {
                if(str[j]>='0'&&str[j]<='9')
                {
                    if(flag)     //如果前面一位也是数字
                    {
                        push_operand(pop_operand()*10+str[j]-'0');
                        j++;
                        type=0;
                        //continue;
                    }
                    else
                    {
                        push_operand(str[j]-'0');
                        flag=1;
                        j++;
                        type=0;
                        //continue;
                    }
                }
                else
                {
                    flag=0;
                    if(sign_of_ans==-1)
                    {
                        operand.stack[0]*=-1;    //pourquoi对第一个operand乘-1：
                        sign_of_ans=1;
                    }
                    if(type==1&&IsAnOperator(str[j]))
                    {
                        printf("error.\n");
                        vis=1;
                        break;
                    }
                    if(str[j]=='(')
                    {
                        if(str[j+1]=='-'&&IsANum(str[j+2])) 
                        {
                            type=0;     //后面有一个负数
                            push_operator('(');
                            j+=2;
                            sign_of_ans=-1;
                            continue;
                        }
                        else type=1;   //单独的左括号
                    }
                    else type=2;    //其他运算符
                    if(operator.tail==-1)
                    {
                        printf("error.\n");
                        vis=1;
                        break;
                    }
                    char top=top_operator(),cmp;
                    cmp=compare(top,str[j]);
                    // pop_operator();
                    if(cmp=='N')
                    {
                        printf("error.\n");
                        vis=1;
                        break;
                    }
                    else if(cmp=='<')
                    {
                        if(j==0&&str[j]=='-')
                        {
                            sign_of_ans=-1;
                            j++;
                            // operator.tail++;
                            continue;
                        }
                        // push_operator(top);
                        push_operator(str[j]);
                        j++;
                        continue;
                    }
                    else if(cmp=='=')
                    {
                        pop_operator();
                        j++;
                        continue;
                    }
                    else if(cmp=='>')
                    {
                        if(str[j]=='-')
                        {
                            if(str[j-1]=='('||IsAnOperator(str[j-1]))
                            {
                                j++;
                                sign_of_operand=-1;
                                continue;
                            }
                        }
                        operand.stack[operand.tail]*=sign_of_operand;
                        if(sign_of_operand==-1) sign_of_operand=1;
                        int b=pop_operand();
                        int a=pop_operand();
                        ans=operate(a,b,top_operator());
                        pop_operator();
                        if(ans==FAIL)
                        {
                            break;
                        }
                        else push_operand(ans);
                        continue;
                    }
                    j++;
                }
            }   //遍历结束
            if(IsOperandStackEmpty()&&IsOperatorStackEmpty()&&vis==0)
            {
                if(sign_of_ans==-1)
                {
                    printf("%d\n",-pop_operand());
                    sign_of_ans=1;
                }
                else printf("%d\n",pop_operand());
            }
            else
            {
                if(ans!=FAIL&&vis==0)
                    printf("error.\n");
            }
        } 
    }
    return 0;
}

// ps. the negative numbers should be input directly without having paranthese around!!!