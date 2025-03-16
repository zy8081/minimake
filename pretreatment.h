#define MAX_LINE 100
typedef struct LineNode
{
    char str[50];
    struct LineNode *next;
}nodel;

int is_emptyline(char *str);
char** pretreatment(int flag);
void clear_markdown(char *str);
void clear_emptytail(char *str);
int check_static_syntax(char **result);
int is_zhibiao(char **result,int i);
int have_maohao(char **result,int i);
int is_lastline(char **result,int i);
int printf_lineerror(int line,int errorflag);
void free_result(char **result);

nodel *create_nodel(void);