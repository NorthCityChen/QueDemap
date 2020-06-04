/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-04 20:01:14
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
// #include "login.h"
#include "about.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <io.h>

#define INFINITY2 65535

struct node2
{
    char name[100];
    int x;int y;
}loc_lst[100];


int add();      //添加数据
void show();    //展示所有的目的地
int init_map(); //初始化地图
void del();     //删除数据
void sort();    //对数据进行排序并保存
int dir_city(); //输出城市列表
void check_path();

 
int MX;     //地图最大边际x
int MY;     //地图最大边际y
int map[100][100];
int city_number=0;
int line_number=0;
int vis_y[100];
char city_name[100][50];

int add()
{
    //添加城市信息
    char name[100];
    int x,y,index=0;
    printf("Pleae enter the name:");
    while (scanf("%s",name)!=-1&&strcmp(name,"end")!=0)
    {
        printf("Please enter the x-loc:");
        scanf("%d",&x);
        printf("Please enter the y-loc:");
        scanf("%d",&y);
        if (map[x][y])
        {
            color(RED);
            printf("%s already existed!!\n",name);
            color(WHITE);
            printf("Pleae enter the name:");
            continue;
        }
        map[x][y]=1;
        strcpy(loc_lst[index].name,name);
        loc_lst[index].x=x;
        loc_lst[index].y=y;
        FILE *fp=fopen(".\\dat\\loc.txt","a");
        fprintf(fp,"%s %d %d\n",name,x,y);
        fclose(fp);
        color(GREEN);
        printf("Data added successfully!\n");

        FILE *log=fopen(".\\dat\\log.txt","a");
        fprintf(log,"Added %s\n",name);
        fclose(log);

        color(WHITE);
        printf("Pleae enter the name:");
    }
    init_map();
    return 0;
}

void del()
{
    //删除城市
    char name[100],choice[5],target[100];
    int x,y;
    if (dir_city()==0)
    {
        return ;
    }
    color(BLUE);
    printf("Please enter the city you want to delet:\n");
    scanf("%s",target);
    printf("This action will delet %s forever,continue?(Y/n):\n",target);
    scanf("%s",choice);
    color(WHITE);
    if (strcmp(choice,"Y")==0)
    {
        FILE *fp,*tmp;
        fp=fopen(".\\dat\\loc.txt","r");
        tmp=fopen(".\\dat\\cache2.txt","a");
        if (fp==NULL||tmp==NULL)
        {
            color(RED);
            printf("\"loc.txt\" does not exist!\n");
            color(WHITE);
            return ;
        }
        int fg1=0;
        while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
        {
            if (strcmp(name,target))
            {
                fprintf(tmp,"%s %d %d\n",name,x,y);
            }
            else
            {
                fg1=1;
            }
            
        }
        fclose(fp);
        fclose(tmp);
        remove(".\\dat\\loc.txt");
        rename(".\\dat\\cache2.txt",".\\dat\\loc.txt");
        if (fg1==1) color(GREEN),printf("successfully delete\n");
        else color(RED),printf("%s does not exist\n",target);
        color(WHITE);
        check_path();
    }
        
    else
    {
        printf("Cancelled\n");
    }
    init_map();
    return;
}

int init_map()
{
    //初始化loc_lst
    // sort();
    FILE *fp;
    city_number=0;
    line_number=0;
    char name[100];
    int x,y,index2=0;
    memset(map,0,sizeof(map));
    memset(vis_y,0,sizeof(vis_y));
    fp=fopen(".\\dat\\loc.txt","r");
    if (fp==NULL)
    {
        // printf("An error occurred suddendly!\n");
        return 0;
    }
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        map[x][y]=1+index2;
        strcpy(city_name[index2],name);
        strcpy(loc_lst[index2].name,name);
        loc_lst[index2].x=x;
        loc_lst[index2].y=y;
        MX=x>MX?x:MX;
        MY=y>MY?y:MY;
        city_number++;
        vis_y[y]++;
        index2++;
    }
    fclose(fp);
    int bef=-1;
    for (int i=1;i<=MY+1;i++)
    {
        if (vis_y[i]&&bef!=-1)
        {
            line_number+=bef*vis_y[i];
            bef=vis_y[i];
        }
        if (vis_y[i]&&bef==-1)
        {
            bef=vis_y[i];
        }
    }
    sort();
    return line_number;
}

int cmp(struct node2 s1,struct node2 s2)
{
    if (s1.y!=s2.y) return s1.y>s2.y;
    if (s1.x!=s2.x) return s1.x>s2.x;
    return 0;
}

void sort()
{
    //整理loc.txt
    for (int i=0;i<city_number;i++)
    {
        int min=i;
        for (int j=i+1;j<city_number;j++)
        {
            if (cmp(loc_lst[i],loc_lst[j]))
            {
                struct node2 tmp=loc_lst[i];
                loc_lst[i]=loc_lst[j];
                loc_lst[j]=tmp;
            }
        }
    }
    FILE *fp=fopen(".\\dat\\loc.txt","w");
    for (int i=0;i<city_number;i++)
    {
        fprintf(fp,"%s %d %d\n",loc_lst[i].name,loc_lst[i].x,loc_lst[i].y);
    }
    fclose(fp);
    return ;
}


void show()
{
    //输出城市列表
    // init_map();
    color(BLUE);
    for (int i=1;i<=MX+2;i++)
    {
        printf("|%3d ",i-1);
    }
    printf("|\n");
    // for (int i=1;i<=MX+1;i++)
    // {
    //     printf("-----");
    // }
    // printf("-\n");
    color(WHITE);
    for (int i=1;i<=MY+1;i++)
    {
        color(BLUE);
        printf("|%3d |",i);
        color(WHITE);
        for (int j=1;j<=MX+1;j++)
        {
            map[j][i]?(color(RED),printf("%3s  ","X"),color(WHITE),1):printf("%3s  ","O");
        }
        printf("\n");
    }
    dir_city();
    return;
}


int dir_city()
{
    FILE *fp;
    char name[100];
    int x,y;
    fp=fopen(".\\dat\\loc.txt","r");
    if (fp==NULL)
    {
        // printf("An error occurred suddendly!\n");
        char str[]="No city information founded!!\n";
        cprint(str,RED);
        return 0;
    }
    color(BLUE);
    printf("\n -------------------------------------------\n");
    printf("|%-10s|%-10s|%-10s|%-10s|\n","Index","City","X-Loc","Y-Loc");
    printf(" -------------------------------------------\n");
    color(WHITE);
    int index=1;
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        printf("|%-10d|%-10s|%-10d|%-10d|\n",index,name,x,y);
        index++;
    }
    color(BLUE);
    printf(" -------------------------------------------\n");
    color(WHITE);
    fclose(fp);
    return 1;
}

void check_path()
{
    init_map();
    FILE *fp2=fopen(".\\dat\\path.txt","r");
    if (fp2==NULL) return;
    FILE *tmp=fopen(".\\dat\\cache.txt","w");
    int x,x1,y,y1;
    double fifi;
    // printf("!!!\n");
    while (fscanf(fp2,"%d%d%d%d%lf\n",&x,&y,&x1,&y1,&fifi)!=-1)
    {
        if (map[x][y]&&map[x1][y1])
        {
            fprintf(tmp,"%d %d %d %d %lf\n",x,y,x1,y1,fifi);
        }
    }
    // printf("!!!\n");
    fclose(fp2);
    fclose(tmp);
    remove(".\\dat\\path.txt");
    rename(".\\dat\\cache.txt",".\\dat\\path.txt");
    return;
}