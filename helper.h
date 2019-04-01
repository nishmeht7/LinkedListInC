typedef struct node {

    union {
        int i;
        double d;
        float f;
        char* str[20];

    } data;

    int type; //1 =int, 2 = double, 3 = float, 4 = string
    union data;
    char* dataStr[20];
    struct node* next;
}node;


