#include <stdio.h>
#include <stdlib.h>
#define SIZE 200
#include "stack.h"
#include "splaytree_freq.h"

void init_stack(stack *s) {
    s->top = -1;
    s->size = SIZE;
    s->arr = (struct node_freq **)malloc(s->size * sizeof(struct node_freq *));
    return;
}

int isFull(struct stack *s) {
    return s->top == s->size - 1;
}

int isEmpty(struct stack *s) {
    return s->top == -1;
}


void push(struct stack *s, struct node_freq *n) {
    if (isFull(s))
        printf("Stack overflow.");
    else {
        s->top++;
        s->arr[s->top] = n;
    }
}

struct node_freq *pop_Stack(struct stack *s) {
    if (isEmpty(s))
        return NULL;
    else {
        struct node_freq *val = s->arr[s->top];
        s->top--;
        return val;
    }
}