typedef struct stack {
    int top;
    int size;
    struct node_freq **arr;
} stack;

void init_stack(stack *s);

int isFull(struct stack *s);

int isEmpty(struct stack *s);

void push(struct stack *s, struct node_freq *n);

struct node_freq *pop_Stack(struct stack *s);