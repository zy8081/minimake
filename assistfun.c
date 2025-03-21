#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pretreatment.h"
#include "parser.h"
#include "graph.h"

void judge_parameters(int argc)
{
    if (argc==1)
    {
        printf("less parameter!\n");
        exit(0);
    }
    if (argc==3)
    {
        printf("too many parameters!\n");
        exit(0);
    }
}

void judge_help(char *str,char *argv[])
{
    int i;
    for (i=0;i<2;i++)
    {
        str[i]=argv[1][i];
    }
    str[i]='\0';
    if (strcmp(str,"--")==0)
    {
        if (strcmp(argv[1]+2,"help")==0)
        {
            printf("Usage --help\n");
            printf("format:./minimake <targeted file name>\n");
            exit(0);
        }
        else
        {
            printf("Command not defined!\n");
            exit(0);
        }
        
    }
}

void make_command(char *command,char *argv[],struct arraydata *p,int num)
{
    int j=0,i=0;
    for (i=0;i<num;i++)
    {
        if(strcmp(argv[1],p[i].target)==0)
        {
            j++;
            break;
        }
    }
    if (j==0)
    {
        printf("%s not found",argv[1]);
        exit(0);
    }
    sprintf(command,"gcc -o %s",p[i].target);
    for (j=0;j<p[i].count;j++)
    {
        strcat(command," ");
        strcat(command,p[i].dependence[j]);
    }
}

char **create_vertex_name(graph *grap)
{
    char **name=(char **)malloc(sizeof(char *)*grap->vertex_num);
    for (int i=0;i<grap->vertex_num;i++)
    {
        name[i]=(char *)malloc(sizeof(33));
    }
    return name;
}
    