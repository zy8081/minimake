

#define MAX_LINE 100
typedef struct
{
    char linestr[50];
    int line;
}data;

int is_emptyline(char *str);
data* pretreatment(int flag);
void clear_markdown(char *str);
void clear_emptytail(char *str);
int check_static_syntax(data *result);
int is_zhibiao(data *result,int i);
int have_maohao(data *result,int i);
int is_lastline(data *result,int i);
int printf_lineerror(int line,int errorflag);
void free_result(data *result);
