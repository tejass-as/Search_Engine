typedef struct node {
    char time[200];
    char quest[20000];
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef node *root;

void initSplay(root *t);

void insert(root *t, char time[200], char qu[20000]);

node *load_from_file();

char *create_key();

void insert_in_file(char *key, int freq);

void inorder(root t);

void preorder(root t);

void destroy(root *t);

void recent_quest(root t);

void display_history(root t);