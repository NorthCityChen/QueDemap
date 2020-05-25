/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-25 16:21:10
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
// #include "login.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "about.h"
#include <io.h>

#define INFINITY2 65535

struct node2
{
    char name[100];
    int x;int y;
}loc_lst[100];

typedef int VertexType;   //顶点是字符型
typedef double EdgeType;   //边是整型
typedef struct    //图的邻接矩阵存储结构
{  
    VertexType vexs[9];  //顶点向量  
    EdgeType edges[9][9];     //邻接矩阵  
    int vexnum,arcnum;    //图中当前的顶点数和边数  
}MGraph;  

int add();      //添加数据
void show();    //展示所有的目的地
int init_map(); //初始化地图
void del();     //删除数据
void sort();    //对数据进行排序并保存
int find_way(); //查找最短路径
int dir_city(); //输出城市列表
void CreateGraph(MGraph *G);
void ShortestPath_Floyd(MGraph G,double P[9][9],double D[9][9]);

 
int mx;     //地图最大边际x
int my;     //地图最大边际y
int map[100][100];
int city_number=0;
int line_number=0;
int vis_y[100];
char city_name[100][50];

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

int init_map()
{
    FILE *fp;
    city_number=0;
    line_number=0;
    char name[100];
    int x,y,index2=0;
    memset(map,0,sizeof(map));
    memset(vis_y,0,sizeof(vis_y));
    fp=fopen("loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return 0;
    }
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        map[x][y]=1;
        strcpy(city_name[index2],name);
        strcpy(loc_lst[index2].name,name);
        loc_lst[index2].x=x;
        loc_lst[index2].y=y;
        mx=x>mx?x:mx;
        my=y>my?y:my;
        city_number++;
        vis_y[y]++;
        index2++;
    }
    fclose(fp);
    int bef=-1;
    for (int i=1;i<=my+1;i++)
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
    FILE *fp=fopen("loc.txt","w");
    for (int i=0;i<city_number;i++)
    {
        fprintf(fp,"%s %d %d\n",loc_lst[i].name,loc_lst[i].x,loc_lst[i].y);
    }
    fclose(fp);
    return ;
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
            map[i][j]?(color(RED),printf("%3s  ","X"),color(WHITE),1):printf("%3s  ","O");
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
    fp=fopen("loc.txt","r");
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

void del()
{
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
        fp=fopen("loc.txt","r");
        tmp=fopen("cache2.txt","a");
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
        remove("loc.txt");
        rename("cache2.txt","loc.txt");
        if (fg1==1) color(GREEN),printf("successfully delete\n");
        else color(RED),printf("%s does not exist\n",target);
        color(WHITE);
    }
        
    else
    {
        printf("Cancelled\n");
    }
    init_map();
    return;
}

double len(double x,double y,double x1,double y1)
{
    return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
}
void makeinput()
{
    FILE *fp;
    city_number=0;
    line_number=0;
    char name[100];
    int x,y,index2=0;
    memset(map,0,sizeof(map));
    memset(vis_y,0,sizeof(vis_y));
    fp=fopen("loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return;
    }
    int cnt=1;
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        map[x][y]=cnt++;
        mx=x>mx?x:mx;
        my=y>my?y:my;
        city_number++;
        vis_y[y]++;
        index2++;
    }
    fclose(fp);
    if (access("cache.txt",0)==0)
        remove("cache.txt");
    FILE *fp2=fopen("cache.txt","a");
    for (int i=1;i<=my;i++)
    {
        int move=1;
        for (int j=1;j<=mx;j++)
        {
            int flag=0,flag1=0,flag3=0;
            for (int k=1;k<=mx;k++)
            {
                if (map[j][i]&&map[k][i+move])
                {
                    fprintf(fp2,"%d %d %lf\n",map[j][i],map[k][i+move],len(j,i,k,i+move));
                    flag=1;
                }
                if (map[j][i])
                {
                    flag1=1;
                }
                if (map[k][i+move])
                {
                    flag3=1;
                }
            }
            if (flag==0)
            {
                move++;
                if (move>my)
                {
                    break;
                }
                if (flag1)
                {
                    j--;
                }
                // j--;
                if (flag3)
                {
                    move=1;
                }
                // printf("j:%d\n",move);
            }
        }
    }
    fclose(fp2);
    return;
}

void CreateGraph(MGraph *G)  
{   
    int i,j,k;  
    int ch1,ch2;
    double weight;  
    makeinput();
    G->vexnum=city_number;
    G->arcnum=init_map(); 
 
    for(i=0;i<G->vexnum;i++)  
    {  
        G->vexs[i]=i+1;
    }  
    for(i=0;i<G->vexnum;i++)  
        for(j=0;j<G->vexnum;j++)  
        	if(i==j)
        		G->edges[i][j]=0;
        	else
           	 	G->edges[i][j]=INFINITY2;  
 
        FILE *fp=fopen("cache.txt","r");
        if (fp==NULL) 
        {
            char str[]="Err\n";
            cprint(str,RED);
            return ;
        }
        for(k=0;k<G->arcnum;k++)  
        {  
 
            fscanf(fp,"%d%d%lf\n",&ch1,&ch2,&weight);

            for(i=0;ch1!=G->vexs[i];i++);  
            for(j=0;ch2!=G->vexs[j];j++);  
	
            G->edges[i][j]=weight; 
			G->edges[j][i]=weight;  
        } 
        fclose(fp);
	
}  
 
void ShortestPath_Floyd(MGraph G,double P[9][9],double D[9][9])
{
	int v,w,k;
	for(v=0;v<G.vexnum;v++)//初始化D和P 
	{
		for(w=0;w<G.vexnum;w++)
		{
			D[v][w]=G.edges[v][w];
			P[v][w]=w;
		}
	}
	
	for(k=0;k<G.vexnum;k++)
	{
		for(v=0;v<G.vexnum;v++)
		{
			for(w=0;w<G.vexnum;w++)
			{
				if(D[v][w]>(D[v][k]+D[k][w]))
				{
                    //如果经过下标为k顶点路径比原两点间路径更短，将当前两点间权值设为更小的一个 
                    D[v][w]=D[v][k]+D[k][w];
                    P[v][w]=P[v][k];
				}
				
			}
		}
	}
}
int find_way()  
{  
    MGraph G;  
    CreateGraph(&G);
    int i,j;
    int v,w;
    double k;
    double P[9][9];
    double D[9][9];
    // printf("%lf\n",P);
    // printf("%lf\n",D);
    ShortestPath_Floyd(G,P,D);
    show();
    int bg,ed;
    printf("-------------------------------------\n");
    // printf("Please input the city you want to go:");
    printf("From:");
    scanf("%d",&bg);
    printf("To:");
    scanf("%d",&ed);
    int fg2=0;
    if (bg>ed)
    {
        int tmp=bg;
        bg=ed;
        ed=tmp;
        fg2=1;
    }
    if (bg-1>=G.vexnum) bg=G.vexnum;
    if (bg<=0) bg=1;
    if (ed-1>=G.vexnum) ed=G.vexnum;
    if (ed<=0) ed=1;

    char str1[40],str2[40],str3[40];
    printf("From %d -> %d\n",bg,ed);
    printf("Weight: %.3lf\n",D[bg-1][ed-1]);
    printf("Path:%s",loc_lst[bg-1].name);
    k=P[bg-1][ed-1];
    while (k!=ed-1)
    {
        printf("->%s",loc_lst[(int)k].name);
        k=P[(int)k][ed-1];
    }
    printf("->%s\n",loc_lst[ed-1].name);
    return 0;
} 