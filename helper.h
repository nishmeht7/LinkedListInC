typedef struct node {

    union {
        int i;
        double d;
        float f;
        char* str[20];

        int type; //1 =int, 2 = double, 3 = float, 4 = string
    } data;

    union data;
    struct node* next;
}node;


