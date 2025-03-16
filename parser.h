
struct arraydata
{
    char target[20];
    char dependence[10][33];
    int count;
    int line;
};

struct arraydata* create_targetdata(data *result,int *num);
int find_target(data *result,int startline);
int check_target(struct arraydata *p,int num);
int check_dependence(struct arraydata *p,int num);
