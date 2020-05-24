/*
 * @Author: Mr.Sen
 * @LastEditTime: 2020-05-24 20:05:22
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
 */ 
// #include<bits/stdc++.h>
// #include <stdio.h> 
// #include <math.h>
// #include "datactl.h"
                                             
#define INFINITY2 65535
 
typedef int VertexType;   //顶点是字符型
typedef double EdgeType;   //边是整型
typedef struct    //图的邻接矩阵存储结构
{  
 
    VertexType vexs[9];  //顶点向量  
 
    EdgeType edges[9][9];     //邻接矩阵  
 
    int vexnum,arcnum;    //图中当前的顶点数和边数  
 
}MGraph;  
 
/* 邻接矩阵的建立*/ 

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
    FILE *fp2=fopen("cache.txt","a");
    for (int i=1;i<=my;i++)
    {
        // printf("!!!");
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
    // printf("Please input the loc and line number:\n");  
 
    // scanf("%d%d",&(G->vexnum),&(G->arcnum));
    G->vexnum=city_number;
    G->arcnum=init_map();
    printf("%d\n",city_number);
 
    // printf("Please input the node name\n");  
 
    for(i=0;i<G->vexnum;i++)  
    {  
    //    scanf("%d",&(G->vexs[i]));
        G->vexs[i]=i+1;
    }  
    for(i=0;i<G->vexnum;i++)  
        for(j=0;j<G->vexnum;j++)  
        	if(i==j)
        		G->edges[i][j]=0;
        	else
           	 	G->edges[i][j]=INFINITY2;  
 
        // printf("Please input each line's node name\n");
        FILE *fp=fopen("cache.txt","r");
        for(k=0;k<G->arcnum;k++)  
        {  
           // getchar();
            printf("%d:",k+1);  
            fscanf(fp,"%d%d%lf\n",&ch1,&ch2,&weight);
            printf("%d %d %lf\n",ch1,ch2,weight);
            for(i=0;ch1!=G->vexs[i];i++);  
            for(j=0;ch2!=G->vexs[j];j++);  
			printf("%d value:",k+1); 
            // scanf("%lf",&weight);	
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
				{//如果经过下标为k顶点路径比原两点间路径更短，将当前两点间权值设为更小的一个 
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
    // printf("edgesnum:%d\n",G.arcnum);
    // printf("vexesnum:%d\n",G.vexnum);
    // for(i=0;i<9;i++)
    // {
    // 	for(j=0;j<9;j++)
    // 		printf("%d ",G.edges[i][j]);
    // 	printf("\n");
	// }
    int v,w;
    double k;
    double P[9][9];
    double D[9][9];
    printf("%lf\n",P);
    printf("%lf\n",D);
    ShortestPath_Floyd(G,P,D);
    int bg,ed;
    printf("Pleaese:");
    scanf("%d%d",&bg,&ed);
    for(v=0;v<G.vexnum;v++)//显示路径 
    {
        for(w=v+1;w<G.vexnum;w++)
        {
            if (v==bg&&w==ed)
            {
                printf("v%d-v%d weight:%lf ",v,w,D[v][w]);
                k=P[v][w];
                printf("path:%d",v);
                while(k!=w)
                {
                    printf("->%d",(int)k);
                    k=P[(int)k][w];
                }
                printf("->%d\n",w);
            }
            
        }
    }
    return 0;
} 