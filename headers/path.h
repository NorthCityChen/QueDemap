/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-01 22:48:35
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 

#include "about.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <io.h>

typedef int VertexType;   //顶点是字符型
typedef double EdgeType;   //边是整型
typedef struct    //图的邻接矩阵存储结构
{  
    VertexType vexs[9];  //顶点向量  
    EdgeType edges[9][9];     //邻接矩阵  
    int vexnum,arcnum;    //图中当前的顶点数和边数  
}MGraph;  


int find_way(); //查找最短路径
void makeinput_by_hand();
void makeinput();
int cnt_city_number();
void CreateGraph(MGraph *G);
void ShortestPath_Floyd(MGraph G,double P[9][9],double D[9][9]);

double len(double x,double y,double x1,double y1)
{
    return sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
}

int cnt_city_number()
{
    FILE *fp;
    
    line_number=0;
    char name[100];
    int x,y,index2=0;

    city_number=0;
    fp=fopen(".\\dat\\loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return 0;
    }
    int cnt=1;
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        city_number++;
    }
    return city_number;
}


void makeinput()
{
    FILE *fp;
    // city_number=0;
    line_number=0;
    char name[100];
    int x,y,index2=0;
    memset(map,0,sizeof(map));
    memset(vis_y,0,sizeof(vis_y));
    fp=fopen(".\\dat\\loc.txt","r");
    if (fp==NULL)
    {
        printf("An error occurred suddendly!\n");
        return;
    }
    int cnt=1;
    while (fscanf(fp,"%s%d%d\n",name,&x,&y)!=-1)
    {
        map[x][y]=cnt++;
        MX=x>MX?x:MX;
        MY=y>MY?y:MY;
        city_number++;
        vis_y[y]++;
        index2++;
    }
    fclose(fp);
    if (access(".\\dat\\path.txt",0)==0)
        remove(".\\dat\\path.txt");
    FILE *fp2=fopen(".\\dat\\path.txt","a");
    for (int i=1;i<=MY;i++)
    {
        int move=1;
        for (int j=1;j<=MX;j++)
        {
            int flag=0,flag1=0,flag3=0;
            for (int k=1;k<=MX;k++)
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
                if (move>MY)
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
    char str[]="Auto generated\n";
    cprint(str,GREEN);
    return;
}

void CreateGraph(MGraph *G)  
{   
    int i,j,k;  
    int ch1,ch2;
    double weight;  
    // makeinput();
    if (access(".\\dat\\path.txt",0)!=0)
    {
        char str[]="Path.txt not exist,creat one automatically?(Y/n)\n";
        cprint(str,BLUE);
        char choice[5];
        scanf("%s",choice);
        if (strcmp(choice,"Y")==0)
        {
            makeinput();
        }
        else
        {
            makeinput_by_hand();
        }
    }
    

    G->vexnum=cnt_city_number();
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
 
        FILE *fp=fopen(".\\dat\\path.txt","r");
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
    printf("From(Index):");
    scanf("%d",&bg);
    printf("To(Index):");
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

void show_path()
{
    FILE *fp=fopen(".\\dat\\path.txt","r");
    int x,y;
    double zx;
    printf(" -------------------------------------------\n");
    while (fscanf(fp,"%d%d%lf\n",&x,&y,&zx)!=-1)
    {
        printf("|%-19s -> %-19s|\n",loc_lst[x-1].name,loc_lst[y-1].name);
    }
    printf(" -------------------------------------------\n");
    fclose(fp);
    return ;
}
void makeinput_by_hand()
{
    int bg,ed;
    show();
    show_path();
    do
    {
        printf("Plese input begin:");
        scanf("%d",&bg);
        if (bg==-1)
        {
            char str[]="All added\n";
            cprint(str,BLUE);
            break;
        }

        printf("Plese input end:");
        scanf("%d",&ed);
        if (ed==-1)
        {
            char str[]="All added\n";
            cprint(str,GREEN);
            break;
        }

        FILE *fp=fopen(".\\dat\\path.txt","a");
        fprintf(fp,"%d %d %lf",bg,ed,len(loc_lst[bg].x,loc_lst[bg].y,loc_lst[ed].x,loc_lst[ed].y));
        char str[]="Path added!\n";
        cprint(str,GREEN);
        fclose(fp);
        
    }while (1);
}

void del_path()
{
    //删除城市
    char name[100],choice[5];
    int bg,ed;
    int x,y;
    if (dir_city()==0)
    {
        return ;
    }
    show_path();
    color(BLUE);
    printf("Please enter the path you want to delet(Index):\n");
    // scanf("%s",target);
    printf("Begin(index):");
    scanf("%d",&bg);
    printf("End(index):");
    scanf("%d",&ed);
    printf("This action will delet %s->%s forever,continue?(Y/n):\n",loc_lst[bg].name,loc_lst[ed].name);
    scanf("%s",choice);
    color(WHITE);
    if (strcmp(choice,"Y")==0)
    {
        FILE *fp,*tmp;
        fp=fopen(".\\dat\\path.txt","r");
        tmp=fopen(".\\dat\\cache2.txt","a");
        if (fp==NULL||tmp==NULL)
        {
            color(RED);
            printf("\"Path.txt\" does not exist!\n");
            color(WHITE);
            return ;
        }
        int fg1=0;
        double zxc;
        while (fscanf(fp,"%d%d%lf\n",&x,&y,&zxc)!=-1)
        {
            if (!(x==bg&&y==ed))
            {
                fprintf(tmp,"%d %d %lf\n",x,y,zxc);
            }
            else
            {
                fg1=1;
            }
            
        }
        fclose(fp);
        fclose(tmp);
        remove(".\\dat\\path.txt");
        rename(".\\dat\\cache2.txt",".\\dat\\path.txt");
        if (fg1==1) color(GREEN),printf("successfully delete\n");
        else color(RED),printf("path does not exist\n");
        color(WHITE);
    }
        
    else
    {
        printf("Cancelled\n");
    }
    init_map();
    return;
}