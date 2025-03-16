#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
struct arraydata* create_data(char **result)
{
    struct arraydata *p=(struct arraydata *)malloc(sizeof(struct arraydata));
    char str[30]={'\0'};
    int len=strlen(result[0]);
    int i,j,k;

    for (i=0;i<len;i++)
    {
        if (result[0][i]==':')
        {
            break;
        }
    }

    k=0;
    for (j=i-1;j>=0;j--)
    {
        if (result[0][j]==' '&&k==0)
        {
            continue;
        }
        if (result[0][j]==' '&&k!=0)
        {
            break;
        }
        str[j]=result[0][j];
        k++;
    }

    strcpy(p->target,str+j+1);

    p->count=0;
    j=i+1;
    i=0;
    while(result[0][j]!='\n')
    {
        k=0;

        for (;;j++)
        {
            if (result[0][j]==' '&&k==0)
            {
                continue;
            }
            if (result[0][j]==' '&&k!=0)
            {
                break;
            }
            if (result[0][j]=='\n')
            {
                break;
            }
            str[k]=result[0][j];
            k++;
        }
        str[k]='\0';
        strcpy(p->dependence[i],str);
        i++;
        p->count++;
    }
    return p;
}

