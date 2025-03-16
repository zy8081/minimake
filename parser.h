struct arraydata
{
    char target[20];
    char dependence[10][33];
    int count;
};
struct arraydata* create_data(char **result);
