#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "pretreatment.h"
struct arraydata* create_targetdata(char **result,int *num)
{
    struct arraydata *p=(struct arraydata *)malloc(sizeof(struct arraydata)*5);
    char str[30]={'\0'};
    int len;
    int i,j,k;
    int line=1;
    int count=0;
    int a=0;
    if (p == NULL) 
    {
        printf("内存分配失败\n");
        return NULL;
    }
    
    *num=0;
    while(1)
    {
        
        memset(str,0,sizeof(str));
        line=find_target(result,line);
        printf("line:%d\n",line);
        if (line==-1)
        {
            break;
        }
        

        (p+count)->line=line;
        
        len=strlen(result[line-1]);
        for (i=0;i<len;i++)
        {
            if (result[line-1][i]==':')
            {
                break;
            }
        }
        k=0;
        for (j=i-1;j>=0;j--)
        {
            if (result[line-1][j]==' '&&k==0)
            {
                continue;
            }
            if (result[line-1][j]==' '&&k!=0)
            {
                break;
            }  
            str[j]=result[line-1][j];
            k++;
        }
        strcpy((p+count)->target,str+j+1);
        
        (p+count)->count=0;
        j=i+1;
        i=0;
        while(result[line-1][j]!='\n')
        {
            k=0;

            for (;;j++)
            {
                if (result[line-1][j]==' '&&k==0)
                {
                    continue;
                }
                if (result[line-1][j]==' '&&k!=0)
                {
                    break;
                }
                if (result[line-1][j]=='\n')
                {
                    break;
                }
                str[k]=result[line-1][j];
                k++;
            }
            str[k]='\0';
            strcpy((p+count)->dependence[i],str);
            i++;
            (p+count)->count++;
        }
        count++;
        (*num)++;
        printf("num:%d\n",*num);
        a++;
        printf("a:%d\n",a);
        printf("%s\n",result[line-1]);
        printf("count:%d\n",count);
        line++;
    }
    

    
    return p;
}


int find_target(char **result,int startline)
{
    while(have_maohao(result,startline-1)!=1)
    {
        if (is_lastline(result,startline-1))
        {
            return -1;
        }
        startline++;
    }
    return startline;
}

int check_target(struct arraydata *p,int num)
{
    for (int i=0;i<num-1;i++)
    {
        for (int j=i+1;j<num;j++)
        {
            if(strcmp((p+i)->target,(p+j)->target)==0)
            {
                printf("\nLine%d:Duplicate target definition '%s'\n",(p+j)->line,(p+j)->target);
                exit(0);
            }
        }
    }
    return 0;
}
