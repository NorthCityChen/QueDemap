/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-01 19:38:40
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "about.h"

typedef struct node
{
    char name[100];
    // char uuid[100];
    char acct[100];
    char pwd[100];
    int pwr;
    int money;
    struct node *next;
}link_list;

int login();    //登录
int req();      //查询路径
void regist();         //用户注册
void ulist();          //输出用户列表
void del_member();     //删除用户信息
void color(int x);     //控制字体颜色
void warn();           //输出警告信息
void logout();
link_list* init();     //�?件初始化


char usr[100];
int PERMISSION=0;


link_list *init()
{
    link_list* head=(link_list*)malloc(sizeof(link_list));
    link_list* tail=head;
    FILE *fp=fopen(".\\dat\\dat.txt","r");
    if (fp==NULL)
    {
        printf("\"dat.txt \"Not Found! Please Create One!\n");
        return NULL;
    }
    char name[100],acct[100],pwd[100];
    int pwr;
    while (fscanf(fp,"%s%s%s%d\n",name,acct,pwd,&pwr)!=-1)
    {
        link_list* node=(link_list*)malloc(sizeof(link_list));
        strcpy(node->name,name);
        strcpy(node->acct,acct);
        strcpy(node->pwd,pwd);
        node->pwr=pwr;
        tail->next=node;
        tail=node;
    }
    tail->next=NULL;
    fclose(fp);
    return head;
}
void regist()
{
    char name[100],acct[100],pwd[100];
    int pwr;
    printf("Please enter your name:");
    while (scanf("%s",name)!=-1)
    {
        int permission=1;
        if (strcmp(name,"end")==0) break;
        printf("Please enter your accont:");
        scanf("%s",acct);
        printf("Please enter your password:");
        scanf("%s",pwd);
        printf("Please enter your pwr:");
        scanf("%d",&pwr);
        // scanf("%s%s%d",acct,pwd,&pwr);
        FILE *fp=fopen(".\\dat\\dat.txt","a");
        if (fp==NULL)
        {
            color(RED);
            printf("An err occured!!!\nNow exiting...\n");
            color(WHITE);
            return;
        }
        link_list *head=init();
        while (head->next!=NULL)
        {
            head=head->next;
            if (strcmp(head->acct,acct)==0)
            {
                color(RED);
                printf("The account has been registered!\n");
                color(WHITE);
                printf("Please enter your name:");
                permission=0;
            }
        }
        if (permission==1)
        {
            //允许注册
            fprintf(fp,"%s %s %s %d\n",name,acct,pwd,pwr);
            fclose(fp);
            color(GREEN);
            printf("Creat accont succeed!\n");
            printf("Enter \"end\" to finish registing\n");
            color(WHITE);
            printf("Please enter your name:");
        }
    }
    return;
}
int login()
{
    //登录
    char act[100],pwd[100];

    link_list *head=init();
    if (head==NULL)
    {
        color(BLUE);
        printf("No user exist,please sign up first!\n");
        color(WHITE);
        regist();
        head=init();
    }
    
    printf("Account:");
    scanf("%s",act);
    printf("Password:");
    scanf("%s",pwd);

    
    while (head->next!=NULL)
    {
        head=head->next;
        if (strcmp(head->acct,act)==0&&strcmp(head->pwd,pwd)==0&&head->pwr==2)
        {
            printf("Welcome, administrator!\n");
            strcpy(usr,head->name);
            return 2;
            // admin permissions
        }
        if (strcmp(head->acct,act)==0&&strcmp(head->pwd,pwd)==0&&head->pwr!=2)
        {
            printf("Welcome, %s!\n",head->name);
            strcpy(usr,head->name);
            return 1;
            // user permissions
        }
    }
    printf("Oops, you have entered the wrong infomation!\n");
    return 0;
}

void ulist()
{
    //输出用户列表
    link_list *head=init();
    printf(" -------------------------------\n");
    while (head->next!=NULL)
    {
        head=head->next;
        printf("|%-15s|%-15s|\n|%-15s|%-15s|\n|%-15s|%-15d|\n","Name",head->name,"Account",head->acct,"Permission",head->pwr);
        printf(" -------------------------------\n");
    }
    return;
}

void del_member()
{
    //删除用户
    char acct[100],choice[5];
    link_list* head=init();
    ulist();
    printf("Please enter the account you want to delet:\n");
    scanf("%s",acct);
    color(BLUE);
    printf("This action will delete %s,you sure?(Y/n):\n",acct);
    color(WHITE);
    scanf("%s",choice);
    if (strcmp(choice,"Y")==0)
    {
        FILE *tmp,*fp;
        fp=fopen(".\\dat\\dat.txt","r");
        tmp=fopen(".\\dat\\cache.txt","a");
        if (fp==NULL||tmp==NULL) 
        {
            color(RED);
            printf("There was an error opening the file\n");
            color(WHITE);
            return ;
        }
        link_list *p,*pre;
        pre=head;
        p=head->next;
        int fg1=0;
        while (p)
        {
            if(strcmp(p->acct,acct)==0)
            {
                pre->next=p->next;
                free(p);
                p=pre->next;
                fg1=1;
            }
            else
            {
                pre=p;
                p=p->next;
            }
        }
        while (head->next!=NULL)
        {
            head=head->next;
            fprintf(tmp,"%s %s %s %d\n",head->name,head->acct,head->pwd,head->pwr);
        }
        fclose(tmp);
        fclose(fp);
        remove(".\\dat\\dat.txt");
        rename(".\\dat\\cache.txt",".\\dat\\dat.txt");
        if (fg1==1)
        {
            color(GREEN);
            printf("successfully delete\n");
            color(WHITE);
        }
        else
        {
            color(RED);
            printf("%s does not exist!\n",acct);
            color(WHITE);
        }
    }
    else
    {
        printf("Cancelled\n");
    }
    return ;
}

void logout()
{
    //登出
    PERMISSION=0;
    color(GREEN);
    printf("%s has logged out.\n",usr);
    color(WHITE);
    memset(usr,0,sizeof(usr));
    return ;
}