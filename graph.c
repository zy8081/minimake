#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pretreatment.h"
#include "parser.h"
#include "graph.h"






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
    
    for (int i=0;i<MAX_SIZE;i++)
    {
        grap->vertex[i].in=0;
        for (int j=0;j<MAX_SIZE;j++)
        {
            grap->matrix[i][j]=0;
        }
    }
    grap->edge_num=0;
    grap->vertex_num=0;


    grap->vertex_num=1;
    strcpy(grap->vertex[grap->vertex_num-1].name,p[comline-1].target);
    grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
    // for (int i=1;i<p[comline-1].count;i++)
    // {
    //     grap->matrix[grap->vertex_num-1][i]=1;
    // }
    

    for (int i=0;i<p[comline-1].count;i++)
    {
        printf("count:%d\n",p[comline-1].count);
        
        /*
        如果有一点从未并创建，就创建 并赋值依赖关系
        */
        y=get_name_to_num(grap,p[comline-1].target);
        x=get_name_to_num(grap,p[comline-1].dependence[i]);
        if (x==-1 || y==-1)
        {
            grap->vertex_num++;
            strcpy(grap->vertex[grap->vertex_num-1].name,p[comline-1].dependence[i]);
            grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
            grap->matrix[grap->vertex_num-1][y]=1;
        }

        /*target和dependence依赖关系检查
        如果已经依赖，则跳过循环，不进行递归查找
        */
        else if(grap->matrix[x][y]==1)
        {
            printf("debug：%d %d\n",x,y);
            continue;
        }
        
        /*
        如果已经点已经创建但未经依赖关系，则创建依赖关系
        */
        else if (x>=0 && y>=0)
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

    for (int j=0;j<p[i].count;j++)
    {
        printf("count:%d\n",p[i].count);

         /*
        如果有一点从未并创建，就创建 并赋值依赖关系
        */
        y=get_name_to_num(grap,p[i].target);
        x=get_name_to_num(grap,p[i].dependence[j]);
        if (x==-1 ||y==-1)
        {
            grap->vertex_num++;
            strcpy(grap->vertex[grap->vertex_num-1].name,p[i].dependence[j]);
            grap->matrix[grap->vertex_num-1][grap->vertex_num-1]=0;
            grap->matrix[grap->vertex_num-1][y]=1;
        }

       
        /*target和dependence依赖关系检查
        如果已经依赖，则跳过循环，不进行递归查找
        */
        else if(grap->matrix[x][y]==1)
        {
            continue;
        }
        /*
        如果已经点已经创建但未经依赖关系，则创建依赖关系
        */
        else if (x>=0 || y>=0)
        {
            grap->matrix[x][y]=1;
        }
        dep_to_target(grap,p,totalnum,p[i].dependence[j]);
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


void print_graph_matrix(graph *grap)
{
    for (int i=0;i<grap->vertex_num;i++)
    {
        printf("%s ",grap->vertex[i].name);
    }
    printf("\n");
    for (int i=0;i<grap->vertex_num;i++)
    {
        printf("%d\t",grap->vertex[i].in);
    }
    printf("\n");
    for (int i=0;i<grap->vertex_num;i++)
    {
        for (int j=0;j<grap->vertex_num;j++)
        {
            printf("%d ",grap->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nvertex_num: %d\n",grap->vertex_num);
}

void cal_in(graph *grap)
{
    for (int i=0;i<grap->vertex_num;i++)
    {
        for (int j=0;j<grap->vertex_num;j++)
        {
            if (grap->matrix[j][i]==1)
            {
                grap->vertex[i].in++;
            }
        }
    }
}

vernode *create_nodelist(graph *grap)
{
    vernode *np=(vernode *)malloc(sizeof(vernode)*grap->vertex_num);
    for (int i=0;i<grap->vertex_num;i++)
    {
        np[i].in=grap->vertex[i].in;
        np[i].index=i;
        np[i].next=NULL;
    }

    
    for (int i=0;i<grap->vertex_num;i++)
    {
        vernode *npi=np+i;
        for (int j=0;j<grap->vertex_num;j++)
        {
            if (grap->matrix[i][j]==1)
            {
                node *p=(node *)malloc(sizeof(node));
                p->next=npi->next;
                p->index=j;
                npi->next=p;
            }
        }
    }
    return np;
}

void tuopu_sort(graph *grap,vernode *p,char **name)
{
    int num=grap->vertex_num;
    int check[num];
    for (int i=0;i<num;i++)
    {
        check[i]=0;
    }
    int j=0;
    while (1)
    {
        int flag=0;
        for (int i=0;i<num;i++)
        {
            if (p[i].in==0 && check[i]==0)
            {
                flag=1;
                //printf("%s ",grap->vertex[i].name);
                strcpy(name[j],grap->vertex[i].name);
                node *temp=(p+i)->next;
                while (temp!=NULL)
                {
                    p[temp->index].in--;
                    temp=temp->next;
                }
                check[i]=1;
                j++;
            }
        }
        if (flag==0)
        {
            if (j+1<grap->vertex_num)
            {
                printf("ERROR: There are dependence loop!\n");
                exit(0);
            }
            break;
        }
    }
}

void run_command(char **name,int namenum,struct arraydata *p,int arraynum,data *result)
{
    int x;
    for (int i=0;i<namenum;i++)
    {
        
        for (int j=0;j<arraynum;j++)
        {
            if (strcmp(name[i],p[j].target)==0 && p[j].runflag==0)
            {

                int temp=0;
                for (int k=0;k<p[j].count;k++)
                {
                    for (int l=0;l<i;l++)
                    {
                        if (strcmp(p[j].dependence[k],name[l])==0)
                        {
                            
                            temp++;
                            break;
                        }
                    }
                }
                if (temp==p[j].count)
                {
                    printf("\ndebug2: %s\n",result[p[j].newline-1].linestr);
                    p[j].runflag=1;
                    if (j<arraynum-1)
                    {
                        for (int k=p[j].newline;k<p[j+1].newline-1;k++)
                        {
                            system((result[k].linestr)+1);
                        }
                    }
                    else
                    {
                        x=p[j].newline;
                        while (!is_lastline(result,x-1))
                        {
                            if (!is_lastline(result,x))
                            {
                                system((result[x].linestr)+1);
                                x++;
                            }
                            else
                            {
                                break;
                            }
                        }
                        if (result[x].linestr[0]==9)
                        {
                            system((result[x].linestr)+1);
                        }
                        
                    }
                
                    
                }
            }
        }
    }
}