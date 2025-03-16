struct arraydata
{
    char target[20];
    char dependence[10][33];
    int count;
    int line;
};
struct arraydata* create_targetdata(char **result,int *num);
int find_target(char **result,int startline);
int check_target(struct arraydata *p,int num);
