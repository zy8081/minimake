#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pretreatment.h"
#include "parser.h"
#include "assistfun.h"
#include "graph.h"
int find_fisrt_command(char *argv[],struct arraydata *p,int num);
int main(int argc,char *argv[])
{
    int i,j;
    FILE *file;
    char str[100];
    char command[200];
    data *result;
    int errorflag=0;
    int line=0;
    struct arraydata *p;
    int num;
    //判断参数数量是否正确
    judge_parameters(argc);
    //判断是否help
    judge_help(str,argv);
    //makefile 预处理
    result=pretreatment(1);
    //静态语法检查if (result==NULL)
    p=create_targetdata(result,&num);
    check_target(p,num);
    //check_dependence(p, num);

    // for (i=0;i<1;i++)
    // {
    //     printf("%s\n",result[0].linestr);
    // }
    // for (i=0;i<num;i++)
    // {
    //     printf("%s",p[i].dependence[0]);
    // }

    graph grap;
    
    int comline=find_fisrt_command(argv,p,num);
    init_graph(&grap,p,num,comline);
    cal_in(&grap);
    print_graph_matrix(&grap);

    char **name=(char **)malloc(sizeof(char *)*grap.vertex_num);
    for (int i=0;i<grap.vertex_num;i++)
    {
        name[i]=(char *)malloc(sizeof(33));
    }

    printf("debug:%d\n",p[1].newline);
    printf("debug:%d\n",p[2].newline);
    printf("debug:%s\n",result[3].linestr);

    vernode *np=create_nodelist(&grap);
    tuopu_sort(&grap,np,name);
    
    for (int i=0;i<grap.vertex_num;i++)
    {
        printf("%s ",name[i]);
    }

    run_command(name,grap.vertex_num,p,num,result);
    return 0;


    make_command(command,argv,p,num);
    // j=0;
    // for (i=0;i<num;i++)
    // {
    //     if(strcmp(argv[1],p[i].target)==0)
    //     {
    //         j++;
    //         break;
    //     }
    // }
    // if (j==0)
    // {
    //     printf("%s not found",argv[1]);
    //     return 1;
    // }
    // sprintf(command,"gcc -o %s",p[i].target);
    // for (j=0;j<p[i].count;j++)
    // {
    //     strcat(command," ");
    //     strcat(command,p[i].dependence[j]);
    // }
    //printf("\ndebug:%s\n",p->target);
    //printf("\ndebug:%s\n",(p+1)->target);

    printf("%s",command);
    int a=system(command);

    if(a!=0)
    {
        perror("system");
        return 1;
    }



    free_result(result);
    return 0;
}



int find_fisrt_command(char *argv[],struct arraydata *p,int num)
{
    int i=0;
    for (i=0;i<num;i++)
    {
        if(strcmp(argv[1],p[i].target)==0)
        {
            
            break;
        }
    }
    return i+1;
}