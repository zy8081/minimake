
struct arraydata
{
    char target[20];
    char dependence[10][33];
    int count;
    int oldline;
    int newline;
    int runflag;
};

struct arraydata* create_targetdata(data *result,int *num);
int find_target(data *result,int startline);
int check_target(struct arraydata *p,int num);

