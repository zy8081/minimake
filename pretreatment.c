#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pretreatment.h"

//预处理：删除空行，删除行尾空格，删除注释
//并且将所有行存入data并返回
/*返回的 data 格式参考

target1:dep1 dep2\n\0
    gcc command\n\0
target2:dep3 dep4\n\0
    gcc command\0

*/
data* pretreatment(int flag)
{
    FILE *file1=fopen("./Makefile","r");
    FILE *file2;
    char str[200];
    char *p;
    int len,i,j;
    data *result;

    if (file1==NULL)
    {
        printf("Can not find Makefile!\n");
        exit(0);
    }

    result=(data *)malloc(MAX_LINE*sizeof(data));
    
    //调试模式
    
    if (flag==1)
    {
        i=0,j=0;
        file2=fopen("./Minimake_claered.mk","w");
        while(1)
        {
            while (1)
            {
                p=fgets(str,200,file1);
                j++;
                if (p==NULL)
                {
                    break;
                }
                if(!is_emptyline(str))
                {
                    clear_emptytail(str);
                    clear_markdown(str);
                    if (is_emptyline(str))
                    {
                        continue;
                    }
                    break;
                }
            }
            if (p==NULL)
            {
                break;
            }
            fputs(str,file2);
            printf("%s",str);
            result[i].line=j;
            strcpy(result[i].linestr,str);
            i++;
        }
        len=strlen(result[i-1].linestr);
        if (result[i-1].linestr[len-1]=='\n')
        {
            result[i-1].linestr[len-1]='\0';
        }
    }
    //非调试模式
    if (flag==0)
    {
        i=0,j=0;
        while(1)
        {
            while (1)
            {
                p=fgets(str,200,file1);
                j++;
                if (p==NULL)
                {
                    break;
                }
                if(!is_emptyline(str))
                {
                    clear_emptytail(str);
                    clear_markdown(str);
                    if (is_emptyline(str))
                    {
                        continue;
                    }
                    break;
                }
            }
            if (p==NULL)
            {
                break;
            }
            printf("%s",str);
            result[i].line=j;
            strcpy(result[i].linestr,str);
            i++;
        }
        len=strlen(result[i-1].linestr);
        if (result[i-1].linestr[len-1]=='\n')
        {
            result[i-1].linestr[len-1]='\0';
        }
    }
    
    fclose(file1);
    fclose(file2);
    return result;
}

int is_emptyline(char *str)
{
    int i,j=0;
    for (i=0;i<strlen(str);i++)
    {
        if (str[i]!=' ' && str[i]!='\t' &&str[i]!='\n')
        {
            j++;
        }
    }
    if (j==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void clear_emptytail(char *str)
{
    int len=strlen(str);
    if (str[len-1]=='\n')
    {
        while(str[len-2]==' ')
        {
            str[len-1]='\0';
            str[len-2]='\n';
            len--;
        }
    }
    else
    {
        while(str[len-1]==' ')
        {
            str[len-1]='\0';
            len--;
        }
    }
    
}

void clear_markdown(char *str)
{
    for (int i=0;i<strlen(str);i++)
    {
        if (str[i]=='#')
        {
            
            str[i]='\n';
            str[i+1]='\0';
            break;
        }
    }
}

//静态语法检查：检查冒号个数和命令前是否有\t
int check_static_syntax(data *result)
{
    int i=0,j=0;
    int count=0;
    int flag1=0;
    int flag2=0;
    
    count=have_maohao(result, i);
    flag1=is_zhibiao(result,i);
    flag2=is_lastline(result,i);
    if (flag1==1)
    {
        //command find before rule
        printf("\nLine%d:Command found before rule\n",result[i].line);
        exit(0);
    }
    if (count!=1)
    {
        printf("\nLine%d:Missing colon in target definition\n",result[i].line);
        exit(0);
    }
    if (flag2==1)
    {
        return 0;
    }

    i++;
    while (1)
    {
        flag1=is_zhibiao(result,i);
        count=have_maohao(result,i);
        
        if ( flag1==1 && count==0);
        else if(flag1==0 && count ==1);
        else
        {
            printf("\nLine%d:Missing colon in target definition\n",result[i].line);
            exit(0);
        }
        flag2=is_lastline(result,i);
        if (flag2==1)
        {
            break;
        }
        i++;
    }
    return 0;
}

int is_zhibiao(data *result,int i)
{
    if (result[i].linestr[0]=='\t')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int have_maohao(data *result,int i)
{
    int len=strlen(result[i].linestr);
    int count=0;
    for (int j=0;j<len;j++)
    {
        if (result[i].linestr[j]==':')
        {
            count++;
        }
    }
    return count;
}

int is_lastline(data *result,int i)
{
    int len=strlen(result[i].linestr);
    if(result[i].linestr[len-1]!='\n')
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int printf_lineerror(int line,int errorflag)
{
    if (line==0)
    {
        return 0;
    }
    if (errorflag==1)
    {
        printf("\nLine%d:Missing colon in target definition\n",line);
        return line;
    }
    if (errorflag==2)
    {
        printf("\nLine%d:Command found before rule\n",line);
        return line;
    }
}

void free_result(data *result)
{
    for (int i=0;i<MAX_LINE;i++)
    {
    }
    free(result);
}