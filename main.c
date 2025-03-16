#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pretreatment.h"
#include "parser.h"
int main(int argc,char *argv[])
{
    int i;
    FILE *file;
    char str[100];
    char command[200];
    char **result;
    int errorflag=0;
    int line=0;
    struct arraydata *p;
    int num;
    //判断参数数量是否正确
    // if (argc==1)
    // {
    //     printf("less parameter!\n");
    //     return 0;
    // }
    // if (argc==3)
    // {
    //     printf("too many parameters!\n");
    //     return 0;
    // }

    //判断是否help
    // for (i=0;i<2;i++)
    // {
    //     str[i]=argv[1][i];
    // }
    // str[i]='\0';

    // if (strcmp(str,"--")==0)
    // {
    //     if (strcmp(argv[1]+2,"help")==0)
    //     {
    //         printf("Usage --help\n");
    //         printf("format:./minimake <targeted file name>\n");
    //     }
    //     else
    //     {
    //         printf("Command not defined!\n");
    //         return 0;
    //     }
       
    // }

    //makefile 预处理
    result=pretreatment(1);
    if (result==NULL)
    {
        printf("makefile noy found!\n");
        return 0;
    }
    //debug printf
    printf("\ndebug:%s\n",result[1]);
    //

    //静态语法检查
    
    line=check_static_syntax(result);

    p=create_targetdata(result,&num);
    printf("\ndebug:%d\n",num);

    check_target(p,num);
    
    sprintf(command,"gcc %s -o %s",p->dependence[0],p->target);

    printf("\ndebug:%s\n",p->target);
    printf("\ndebug:%s\n",(p+1)->target);

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