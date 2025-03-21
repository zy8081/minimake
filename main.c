#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include "pretreatment.h"
#include "parser.h"

#include "graph.h"
#include "assistfun.h"
int main(int argc,char *argv[])
{
    int num;
    char str[100];
    char command[200];
    data *result;
    int line=0;
    struct arraydata *p;
    //判断参数数量是否正确
    judge_parameters(argc);
    //判断是否help
    judge_help(str,argv);
    //makefile 预处理
    result=pretreatment(1);
    //静态语法检查if (result==NULL)
    p=create_targetdata(result,&num);
    check_target(p,num);
    graph grap;
    
    int comline=find_fisrt_command(argv,p,num);
    init_graph(&grap,p,num,comline);
    cal_in(&grap);
    print_graph_matrix(&grap);

    char **name=create_vertex_name(&grap);
    vernode *np=create_nodelist(&grap);
    check_dependence(np,&grap);
    tuopu_sort(&grap,np,name);
    run_command(name,grap.vertex_num,p,num,result);

    free_result(result);
    free(p);
    free_name(name,&grap);
    free_vernode(np,&grap);
    return 0;
}



