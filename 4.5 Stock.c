#include <stdio.h>
#include <stdlib.h>

typedef struct stock stock;

struct stock{
    int orderid;
    int stockid;
    float price;
    int quantity;
    char buy_or_sell;
    stock *next;
};

stock *buyhead,*sellhead;
int func,price,stockid,quantity;
char ch;

void InitializeBuyQueue()
{
    buyhead=malloc(sizeof(stock));
    buyhead->orderid=0;
    buyhead->stockid=-1;
    buyhead->price=10000;
    buyhead->quantity=-1;
    buyhead->next=NULL;
    return;
}

void InitializeSellQueue()
{
    sellhead=malloc(sizeof(stock));
    sellhead->orderid=0;
    sellhead->stockid=-1;
    sellhead->price=-1;
    sellhead->quantity=-1;
    sellhead->next=NULL;
    return;
}

void ConstructNewNode(stock *ptr,int order)
{
    ptr->stockid=stockid;
    ptr->price=price;
    ptr->quantity=quantity;
    ptr->buy_or_sell=ch;
    ptr->orderid=order;
    return;
}

void PushBuyOrder(stock *ptr)
{
    int flag=0;
    stock *tmp;
    tmp=buyhead;
    while(tmp->next!=NULL)
    {
        if(tmp->next->price<ptr->price)   //买队列中价格高的在前
        {
            ptr->next=tmp->next;
            tmp->next=ptr;
            flag=1;
            break;
        }   
        tmp=tmp->next;
    }
    if(!flag) 
    {
        tmp->next=ptr;
        ptr->next=NULL;
    }

    return;
}

void PushSellOrder(stock *ptr)
{
    int flag=0;
    stock *tmp;
    tmp=sellhead;
    while(tmp->next!=NULL)
    {
        if(tmp->next->price>ptr->price)      //卖队列中价格低的在前
        {
            ptr->next=tmp->next;
            tmp->next=ptr;
            flag=1;
            break;
        }   
        tmp=tmp->next;
    }
    if(!flag) 
    {
        tmp->next=ptr;
        ptr->next=NULL;
    }

    return;
}

void DeleteSellOrder(stock *ptr)
{
    stock *tmp;
    tmp=sellhead;
    while(tmp->next!=NULL)
    {
        if(tmp->next->orderid==ptr->orderid) break;
        else tmp=tmp->next; 
    }
    tmp->next=ptr->next;
    //free(tmp);   别乱free...
    return;
}

void DeleteBuyOrder(stock *ptr)
{
    stock *tmp;
    tmp=buyhead;
    while(tmp->next!=NULL)
    {
        if(tmp->next->orderid==ptr->orderid) break;
        else tmp=tmp->next;
    }   
    tmp->next=ptr->next;
    //free(tmp);
    return;
}

void SearchBuyOrders(int id)
{
    stock *ptr;
    ptr=buyhead;
    while(ptr->next!=NULL)
    {
        ptr=ptr->next;
        if(ptr->stockid==id) 
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",ptr->orderid,ptr->stockid,ptr->price,ptr->quantity,ptr->buy_or_sell);
    }
    return;
}

void SearchSellOrders(int id)
{
    stock *ptr;
    ptr=sellhead;
    while(ptr->next!=NULL)
    {
        ptr=ptr->next;
        if(ptr->stockid==id) 
            printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",ptr->orderid,ptr->stockid,ptr->price,ptr->quantity,ptr->buy_or_sell);
    }
    return;
}

int main()
{
    int num_of_order=0,dealquantity;
    float dealprice;
    stock *tmp,*tmp1;
    InitializeBuyQueue();
    InitializeSellQueue();
    while(1)
    {
        scanf("%d",&func);
        if(func==0) return 0;
        else if(func==1)
        {
            scanf("%d %d %d %c",&stockid,&price,&quantity,&ch);
            stock *p;
            p=malloc(sizeof(stock));
            ConstructNewNode(p,++num_of_order);
            printf("orderid: %04d\n",p->orderid);
            if(ch=='b')
            {
                tmp=sellhead;
                while(tmp->next!=NULL)
                {
                    tmp=tmp->next;
                    if(tmp->stockid==p->stockid)   //找到了这只股票
                    {
                        if(p->price>=tmp->price)  // deal
                        {
                            dealquantity=p->quantity<tmp->quantity?p->quantity:tmp->quantity;
                            dealprice=(p->price+tmp->price)/2;
                            p->quantity-=dealquantity;
                            tmp->quantity-=dealquantity;
                            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",dealprice,dealquantity,p->orderid,tmp->orderid);
                            if(tmp->quantity==0) 
                            {
                                tmp1=tmp;
                                DeleteSellOrder(tmp1);
                            }    
                            if(p->quantity==0) break;  // 如果能完美达成，终止循环
                        }
                    }
                }
                if(p->quantity==0) free(p);
                else PushBuyOrder(p);   //不能完美达成，放到买队列中
            }
            else if(ch=='s')
            {
                tmp=buyhead;
                while(tmp->next!=NULL)
                {
                    tmp=tmp->next;
                    if(tmp->stockid==p->stockid)   //找到了这只股票
                    {
                        if(p->price<=tmp->price)  // deal
                        {
                            dealquantity=p->quantity<tmp->quantity?p->quantity:tmp->quantity;
                            dealprice=(p->price+tmp->price)/2;
                            p->quantity-=dealquantity;
                            tmp->quantity-=dealquantity;
                            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",dealprice,dealquantity,p->orderid,tmp->orderid);  //忘记改文字顺序了...
                            if(tmp->quantity==0) 
                            {
                                tmp1=tmp;
                                DeleteBuyOrder(tmp1);
                            }  
                            if(p->quantity==0) break;  //这笔订单卖完了  
                        }
                    }
                }
                if(p->quantity==0) free(p);
                else PushSellOrder(p);   //没卖完，放入待出售队列
            }

        }
        else if(func==2)   //如果是要查询
        {
            scanf("%d",&stockid);
            printf("buy orders:\n");
            SearchBuyOrders(stockid);
            printf("sell orders:\n");
            SearchSellOrders(stockid);

        }
        else if(func==3)   //如果要撤销委托
        {
            int orderid;
            scanf("%d",&orderid);
            int flag=0;
            stock *tmp2;
            tmp2=buyhead;
            while(tmp2->next!=NULL)
            {
                tmp2=tmp2->next;
                if(tmp2->orderid==orderid) 
                {
                    flag=1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",tmp2->orderid,tmp2->stockid,tmp2->price,tmp2->quantity,tmp2->buy_or_sell);
                    DeleteBuyOrder(tmp2);
                    break;
                }
            }
            tmp2=sellhead;
            while(tmp2->next!=NULL)
            {
                tmp2=tmp2->next;
                if(tmp2->orderid==orderid) 
                {
                    flag=1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",tmp2->orderid,tmp2->stockid,tmp2->price,tmp2->quantity,tmp2->buy_or_sell);
                    DeleteSellOrder(tmp2);
                    break;
                }
            }
            if(!flag) printf("not found\n");
        }
    }
    return 0;
}