#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pretreatment.h"
#include "parser.h"


//提取目标行：目标行上限：20     单个目标行依赖上限：10
//将所有目标行存储在p指向的数组里，num是目标行数
/*p的结构样例
p[0]:target1  dep1  dep2  count=2  line=1
p[1]:target2  dep3  dep4  dep5 count=3 line=4
*/
struct arraydata* create_targetdata(data *result,int *num)
{
    struct arraydata *p=(struct arraydata *)malloc(sizeof(struct arraydata)*20);
    char str[30]={'\0'};
    int len;
    int i,j,k;
    int line=1;
    int count=0;
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
        //printf("line:%d\n",line);
        if (line==-1)
        {
            break;
        }
        
        (p+count)->oldline=result[line-1].line;
        (p+count)->newline=line;
        (p+count)->runflag=0;
        len=strlen(result[line-1].linestr);


        for (i=0;i<len;i++)
        {
            if (result[line-1].linestr[i]==':')
            {
                break;
            }
        }

        
        k=0;
        for (j=i-1;j>=0;j--)
        {
            if (result[line-1].linestr[j]==' '&&k==0)
            {
                continue;
            }
            if (result[line-1].linestr[j]==' '&&k!=0)
            {
                break;
            }  
            str[j]=result[line-1].linestr[j];
            k++;
        }

        
        strcpy((p+count)->target,str+j+1);
        
        (p+count)->count=0;
        j=i+1;
        i=0;
        
        while(result[line-1].linestr[j]!='\n'&& result[line-1].linestr[j]!='\0')
        {
            k=0;

            for (;;j++)
            {
                if (result[line-1].linestr[j]==' '&&k==0)
                {
                    continue;
                }
                if (result[line-1].linestr[j]==' '&&k!=0)
                {
                    break;
                }
                if (result[line-1].linestr[j]=='\n')
                {
                    break;
                }
                if (result[line-1].linestr[j]=='\0')
                {
                    break;
                }
                str[k]=result[line-1].linestr[j];
                k++;
            }
            str[k]='\0';
            strcpy((p+count)->dependence[i],str);
            i++;
            (p+count)->count++;
        }
        count++;
        (*num)++;
        //printf("num:%d\n",*num);
        //printf("count:%d\n",count);
        line++;
    }
    

    
    return p;
}


int find_target(data *result,int startline)
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
                printf("\nLine%d:Duplicate target definition '%s'\n",(p+j)->oldline,(p+j)->target);
                exit(0);
            }
        }
    }
    return 0;
}
