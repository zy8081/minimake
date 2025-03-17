#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#define MAX_SIZE 100

typedef struct
{
    vertextype vertex[MAX_SIZE];
    int matrix[MAX_SIZE][MAX_SIZE];
    int vertex_num;
    int edge_num;
}graph;


typedef struct vertextype
{
    char name[33];
    int in;
    int out;
}vertextype;



void calculate_all_dep(struct arraydata *p,int totalnum,int comline)
{
    int count=0;
    char str[33];
    int check[totalnum];
    for (int i=0;i<totalnum;i++)
    {
        check[i]=0;
    }
    check[comline-1]=1;
    for (int i=0;i<p[comline-1].count;i++)
    {
        p[comline-1].dependence[i];
    }
    
}



void init_graph(graph *grap,struct arraydata *p,int totalnum,int comline)
{
    char str[33];
    int matrixnum=0;
    int x,y;
    
    grap->vertex_num=1;
    strcpy(grap->vertex[grap->vertex_num-1].name,p[comline-1].target);
    grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
    for (int i=1;i<p[comline-1].count;i++)
    {
        grap->matrix[grap->vertex_num-1][i]=1;
    }
    

    for (int i=0;i<p[comline-1].count;i++)
    {
        /*target和dependence依赖关系检查
        如果已经依赖，则跳过循环，不进行递归查找
        */
        y=get_name_to_num(grap,p[comline-1].target);
        x=get_name_to_num(grap,p[comline-1].dependence[i]);
        if(grap->matrix[x][y]==1)
        {
            continue;
        }

        /*
        如果有一点从未并创建，就创建 并赋值依赖关系
        */
        if (x==-1 ||y==-1)
        {
            grap->vertex_num++;
            strcpy(grap->vertex[grap->vertex_num-1].name,p[comline-1].dependence[i]);
            grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
            grap->matrix[x][y]=1;
        }
        /*
        如果已经点已经创建但未经依赖关系，则创建依赖关系
        */
        if (x>=0 || y>=0)
        {
            grap->matrix[x][y]=1;
        }
        
        dep_to_target(grap,p,totalnum,p[comline-1].dependence[i]);
    }


}

//这里的target实际上指的是上次传入的dep，需要提前
int dep_to_target(graph *grap,struct arraydata *p,int totalnum,char *target)
{
    char str[33];
    int i;
    int flag=0;
    int x,y;
    //换行链接指定目标
    for (i=0;i<totalnum;i++)
    {
        if (strcmp(p[i].target,target)==0)
        {
            break;
        }
    }
    //没找到就停止递归：理想退出
    if (i==totalnum)
    {
        return 0;
    }



    strcpy(str,p[i].target);
    grap->vertex_num++;
    for (int j=0;j<p[i].count;j++)
    {
        /*target和dependence依赖关系检查
        如果已经依赖，则跳过循环，不进行递归查找
        */
        y=get_name_to_num(grap,p[i].target);
        x=get_name_to_num(grap,p[i].dependence[i]);
        if(grap->matrix[x][y]==1)
        {
            continue;
        }

        /*
        如果有一点从未并创建，就创建 并赋值依赖关系
        */
        if (x==-1 ||y==-1)
        {
            grap->vertex_num++;
            strcpy(grap->vertex[grap->vertex_num-1].name,p[i].dependence[i]);
            grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
            grap->matrix[x][y]=1;
        }
        /*
        如果已经点已经创建但未经依赖关系，则创建依赖关系
        */
        if (x>=0 || y>=0)
        {
            grap->matrix[x][y]=1;
        }
        find_dep(grap,p,totalnum,target);
    }
}


//根据顶点的名字 查找他对应的数字索引
int get_name_to_num(graph *grap,char *name)
{
    for (int i=0;i<grap->vertex_num;i++)
    {
        if (strcmp(grap->vertex[i].name,name)==0)
        {
            return i;
        }
    }
    return -1;
}