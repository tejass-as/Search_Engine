#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splaytree_freq.h"
#include "stack.h"

void initSplay_freq(root1 *t) {
    *t = NULL;
    return;
}

void rightrotate_freq(root1 *t, node_freq *r) {
    node_freq *p = r->left;
    r->left = p->right;
    if (p->right != NULL)
        p->right->parent = r;
    
    p->parent = r->parent;
    if (r->parent == NULL)
        *t = p;
    else if (r == r->parent->right)
       r->parent->right = p;
    else
        r->parent->left = p;

    p->right = r;
    r->parent = p;
}

void leftrotate_freq(root1 *t, node_freq *r) {
    node_freq *p = r->right;
    r->right = p->left;
    if (p->left != NULL)
        p->left->parent = r;
    
    p->parent = r->parent;
    if (r->parent == NULL)
        *t = p;
    else if (r == r->parent->left)
        r->parent->left = p;
    else
        r->parent->right = p;
    
        p->left = r;
    r->parent = p;
}

void splay_freq(root1 *t, node_freq *n) {
    node_freq *r = *t;
    while (n->parent != NULL) { // node is not root
        if (n->parent == r) { // node is a child of root, one rotation
            if (n == n->parent->left)
                rightrotate_freq(t, n->parent);
            else
                leftrotate_freq(t, n->parent);
        } else {
            node_freq *p = n->parent;
            node_freq *q = p->parent; // grandparent
            if (n->parent->left == n && p->parent->left == p) { // both are left children
                rightrotate_freq(t, q);
                rightrotate_freq(t, p);
            } else if (n->parent->right == n && p->parent->right == p) { // both are right children
                leftrotate_freq(t, q);
                leftrotate_freq(t, p);
            }
            else if (n->parent->right == n && p->parent->left == p) {
                leftrotate_freq(t, p);
                rightrotate_freq(t, q);
            } else if (n->parent->left == n && p->parent->right == p) {
                rightrotate_freq(t, p);
                leftrotate_freq(t, q);
            }
        }
    }
}

void insert_freq(root1 *t, int freq, char qu[20000]) {
    node_freq *nn = (node_freq *)malloc(sizeof(node_freq));
    if (!nn)
        return;
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    nn->freq = freq;
    strcpy(nn->quest, qu);

    if (*t == NULL)
        *t = nn;
        return;
    
    node_freq *p, *q = NULL;
    p = *t;
    while (p) {
        q = p;
        if (strcmp(p->quest, qu) == 0) {
            free(nn);
            p->freq++;
            splay_freq(t, p);
            return;
        }

        if (strcmp(p->quest, qu) > 0)
            p = p->left; // advance p
        else
            p = p->right;
    }

    if (strcmp(q->quest, qu) > 0)
        q->left = nn;
    else
        q->right = nn;

    nn->parent = q;
    splay_freq(t, nn);
    return;
}

//rewrites the files with new updated frequency
void Rewrite(root1 t, char *filename1, char *filename2) {
    FILE *fp1 = fopen(filename1, "w");

    FILE *fp2 = fopen(filename2, "w");

    if (!fp1 || !fp2)
        return;
    if (t == NULL)
        return;
    else {
        stack *s;

        init_stack(s);

        node_freq *p = t;
        do {

            while (p != NULL) {

                if (p->right != NULL)
                    push(s, p->right);
                push(s, p);

                p = p->left;
            }

            p = pop_Stack(s);
            if (p->right && p->right == s->arr[s->top]) {
                pop_Stack(s);
                push(s, p);
                p = p->right;
            } else {
                fprintf(fp1, "%s", p->quest);
                fprintf(fp2, "%d\n", p->freq);
                p = NULL;
            }

        } while (!isEmpty(s));
    }
    
    fclose(fp1);
    fclose(fp2);
}

//load all the question and frequency and will insert in splay tree
node_freq *load_from_file_freq() {
    char quest[20000];
    int freq;
    root1 t;
    initSplay_freq(&t);
    FILE *fp1 = fopen("freq_bck.txt", "r");
    FILE *fp2 = fopen("freq.txt", "r");
    if (!fp1 || !fp2)
        printf("error");

    while (fgets(quest, 20000, fp1)) {
        fscanf(fp2, "%d", &freq);
        insert_freq(&t, freq, quest);
    }

    fclose(fp1);
    fclose(fp2);

    return t;
}

//finds maximum frequency by traversing the tree
int max_using_stack(root1 t, int a) {
    if (!t)
        return -1;

    stack s;
    init_stack(&s);
    node_freq *p = t;

    while (1) {
        if (p != NULL) {
            if (a <= p->freq)
                a = p->freq;
            push(&s, p);
            p = p->left;
        } else {
            if (!isEmpty(&s)) {
                p = pop_Stack(&s);
                p = p->right;
            } else
                break;
        }
    }
    return a;
}

//finds minimum frequency by traversing the tree
int min_using_stack(root1 t, int a) {
    if (!t)
        return -1;
    
    stack s;
    init_stack(&s);
    node_freq *p = t;

    while (1) {
        if (p != NULL) {
            if (a >= p->freq)
                a = p->freq;
            push(&s, p);
            p = p->left;
        } else {
            if (!isEmpty(&s)) {
                p = pop_Stack(&s);
                p = p->right;
            } else
                break;
        }
    }
    return a;
}

//would compare the maximum value with the frequencies of all question and print maximum
void print_max(root1 t, int m) {
    if (!t)
        return;
    
    if (m == t->freq)
        printf("\n%s >> searched %d times", t->quest, t->freq);

    print_max(t->left, m);
    print_max(t->right, m);
}

//would compare the minimum value with the frequencies of all question and print minimum
void print_min(root1 t, int m) {
    if (!t)
        return;
    
    if (m == t->freq)
        printf("\n%s >> searched %d times", t->quest, t->freq);
    
    print_max(t->left, m);
    print_max(t->right, m);
}

void frequency(root1 t, int ch) {
    int max, min;
    max = min = t->freq;
    if (!t)
        return;

    max = max_using_stack(t, max);
    min = min_using_stack(t, min);
    if (ch == 1) {
        printf("Most Frequent search questions");
        print_max(t, max);
    } else if (ch == 0) {
        printf("Most least searched");
        print_min(t, min);
    } else {
        printf("Most Frequent search questions");
        print_max(t, max);
        printf("Most least searched");
        print_min(t, min);
    }

    return;
}

void preorder_freq(root1 t) {
    if (!t)
        return;
    printf("%s -- %d\n", t->quest, t->freq);
    preorder_freq(t->left);
    preorder_freq(t->right);
}