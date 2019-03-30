struct node {
    union {
        int i;
        double d;
        char str[20];
    } data;

    //string version of the data
    char dataStr[20];
    int type; //1 =int, 2 = double, 3 = string
    union data;
    struct node* next;
}node_default = {NULL, 0, NULL, NULL};

typedef struct node node;



