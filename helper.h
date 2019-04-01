struct node {
    void *data;
    char dataStr[20];
    int type; //1 =int, 2 = double, 3 = string 4 = list
    struct node* next;
}node_default = {NULL, "\0", 0, NULL};

typedef struct node node;

