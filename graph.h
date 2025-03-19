#define MAX_SIZE 100


typedef struct vertextype
{
    char name[33];
    int in;
    int out;
}vertextype;
typedef struct
{
    vertextype vertex[MAX_SIZE];
    int matrix[MAX_SIZE][MAX_SIZE];
    int vertex_num;
    int edge_num;
}graph;

typedef struct vertexnode
{
    int in;
    int index;
    struct node *next;
}vernode;

typedef struct node
{
    int index;
    struct node *next;
}node;

typedef struct nodec
{
    /* data */
}nodec;




void calculate_all_dep(struct arraydata *p,int totalnum,int comline);
void init_graph(graph *grap,struct arraydata *p,int totalnum,int comline);
int dep_to_target(graph *grap,struct arraydata *p,int totalnum,char *target);
int get_name_to_num(graph *grap,char *name);
void print_graph_matrix(graph *grap);
void cal_in(graph *grap);
vernode *create_nodelist(graph *grap);
void tuopu_sort(graph *grap,vernode *p,char **name);
void run_command(char **name,int namenum,struct arraydata *p,int arraynum,data *result);