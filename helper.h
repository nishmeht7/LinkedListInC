typedef struct node {
    union {
        int i;
        double d;
        char str[20];
    } data;

    //data version of the string
    char dataStr[20];
    int type; //1 =int, 2 = double, 3 = string
    union data;
    struct node* next;
}node;


