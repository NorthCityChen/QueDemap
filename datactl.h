/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-22 19:50:37
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
// #include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "about.h"

struct node2
{
    char name[100];
    int x;int y;
}loc_lst[100];

int add();      //添加数据
void show();        //展示所有的目的地
void init_map();    //初始化地图
void del();      //删除数据

int mx;     //地图最大边际x
int my;     //地图最大边际y
int map[100][100];

int add()
{
    char name[100];
    int x,y,index=0;
    printf("Pleae enter the name:");
    while (scanf("%s",name)!=-1&&strcmp(name,"end")!=0)
    {
        printf("Please enter the x-loc:");
        scanf("%d",&x);
        printf("Please enter the y-loc:");
        scanf("%d",&y);
        // loc_lst[index++].name=name;
        strcpy(loc_lst[index].name,name);
        loc_lst[index].x=x;
        loc_lst[index].y=y;
        FILE *fp=fopen("loc.txt","a");
        fprintf(fp,"%s %d %d\n",name,x,y);
        fclose(fp);
        color(GREEN);
        printf("Data added successfully!\n");
        color(WHITE);
        printf("Pleae enter the name:");
    }
    return 0;
}

void init_map()
{
    FILE *fp;
    char name[100];
    int x,y;
    memset(map,0,sizeof(map));
    fp=fopen("loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return;
    }
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        map[x][y]=1;
        mx=x>mx?x:mx;
        my=y>my?y:my;
    }
    fclose(fp);
    return;
}

void show()
{
    init_map();
    color(BLUE);
    for (int i=1;i<=my+2;i++)
    {
        printf("|%3d ",i-1);
    }
    printf("|\n");
    for (int i=1;i<=my+1;i++)
    {
        printf("-----");
    }
    printf("-\n");
    color(WHITE);
    for (int i=1;i<=mx+1;i++)
    {
        color(BLUE);
        printf("|%3d |",i);
        color(WHITE);
        for (int j=1;j<=my+1;j++)
        {
            // printf("%d ",map[i][j]);
            map[i][j]?(color(RED),printf("%3s  ","X"),color(WHITE),1):printf("%3s  ","O");
        }
        printf("\n");
    }
}
void dir_city()
{
    FILE *fp;
    char name[100];
    int x,y;
    fp=fopen("loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return;
    }
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        printf("%s %d %d\n",name,x,y);
    }
    fclose(fp);
    return;
}

void del()
{
    char name[100],choice[5],target[100];
    int x,y;
    dir_city();
    color(BLUE);
    printf("Please enter the city you want to delet:\n");
    scanf("%s",target);
    printf("This action will delet %s forever,continue?(Y/n):\n",target);
    scanf("%s",choice);
    color(WHITE);
    if (strcmp(choice,"Y")==0)
    {
        FILE *fp,*tmp;
        fp=fopen("loc.txt","r");
        tmp=fopen("cache.txt","a");
        if (fp==NULL||tmp==NULL)
        {
            color(RED);
            printf("An error occurred\n");
            color(WHITE);
        }
        while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
        {
            if (strcmp(name,target))
            {
                fprintf(tmp,"%s %d %d\n",name,x,y);
            }
        }
        fclose(fp);
        fclose(tmp);
        remove("loc.txt");
        rename("cache.txt","loc.txt");
        printf("successfully delete\n");
    }
    else
    {
        printf("Cancelled\n");
    }
    init_map();
    return;
}
