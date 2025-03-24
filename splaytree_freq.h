typedef struct node_freq {
    int freq;
    char quest[20000];
    struct node_freq *left;
    struct node_freq *right;
    struct node_freq *parent;
} node_freq;

typedef node_freq *root1;

void initSplay_freq(root1 *t);

void insert_freq(root1 *t, int freq, char qu[20000]);

void Rewrite(root1 t, char *filename1, char *filename2);

node_freq *load_from_file_freq();

int max_using_stack(root1 t, int a);

int min_using_stack(root1 t, int a);

void print_max(root1 t, int m);

void print_min(root1 t, int m);

void preorder_freq(root1 t);