#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splaytree_freq.h"
#include "stack.h"
#include <limits.h>

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

    if (*t == NULL) {
        *t = nn;
        return;
    }
    
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
node_freq* load_from_file_freq() {
    FILE *fp1 = fopen("freq_bck.txt", "r");
    FILE *fp2 = fopen("freq.txt", "r");
    
    if (!fp1 || !fp2) {
        printf("Error opening frequency files\n");
        return NULL;
    }
    
    root1 t = NULL;
    initSplay_freq(&t);
    
    char question[20000];
    int frequency;
    
    // Read questions and frequencies line by line
    while (fgets(question, sizeof(question), fp1)) {
        // Remove newline character
        question[strcspn(question, "\n")] = 0;
        
        // Read corresponding frequency
        if (fscanf(fp2, "%d\n", &frequency) != 1) {
            printf("Error reading frequency value\n");
            break;
        }
        
        // Insert into splay tree
        insert_freq(&t, frequency, question);
    }
    
    fclose(fp1);
    fclose(fp2);
    
    return t;
}

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
            }
            else
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
            }
            else
                break;
        }
    }
    return a;
}

// 4. Fix the print_max function
void print_max(root1 t, int max_freq) {
    if (t == NULL)
        return;
    
    // Use a stack for non-recursive traversal
    typedef struct {
        node_freq* data[1000];
        int top;
    } NodeStack;
    
    NodeStack stack;
    stack.top = -1;
    
    // Push function
    #define PUSH(node) stack.data[++stack.top] = node
    // Pop function
    #define POP() stack.data[stack.top--]
    // Is empty check
    #define IS_EMPTY() (stack.top == -1)
    
    // Start with the root
    PUSH(t);
    
    // Traverse the tree and print nodes with frequency equal to max_freq
    while (!IS_EMPTY()) {
        node_freq* current = POP();
        
        // Print if frequency matches the max
        if (current->freq == max_freq) {
            printf("\n\033[1;34mQuestion: %s\n", current->quest);
            printf("Frequency: %d\n\033[0m", current->freq);
        }
        
        // Push right and left children (if they exist)
        if (current->right != NULL)
            PUSH(current->right);
        if (current->left != NULL)
            PUSH(current->left);
    }
}

// 5. Fix the print_min function
void print_min(root1 t, int min_freq) {
    if (t == NULL)
        return;
    
    // Use a stack for non-recursive traversal
    typedef struct {
        node_freq* data[1000];
        int top;
    } NodeStack;
    
    NodeStack stack;
    stack.top = -1;
    
    // Push function
    #define PUSH(node) stack.data[++stack.top] = node
    // Pop function
    #define POP() stack.data[stack.top--]
    // Is empty check
    #define IS_EMPTY() (stack.top == -1)
    
    // Start with the root
    PUSH(t);
    
    // Traverse the tree and print nodes with frequency equal to min_freq
    while (!IS_EMPTY()) {
        node_freq* current = POP();
        
        // Print if frequency matches the min
        if (current->freq == min_freq) {
            printf("\n\033[1;34mQuestion: %s\n", current->quest);
            printf("Frequency: %d\033[0m\n", current->freq);
        }
        
        // Push right and left children (if they exist)
        if (current->right != NULL)
            PUSH(current->right);
        if (current->left != NULL)
            PUSH(current->left);
    }
}

// 6. Fix the Rewrite function
void Rewrite(root1 t, char *filename1, char *filename2) {
    if (t == NULL) {
        // Don't rewrite empty trees - this would erase the files
        printf("Warning: No data to write to files.\n");
        return;
    }
    
    // First, create temporary files
    char temp_filename1[256];
    char temp_filename2[256];
    sprintf(temp_filename1, "%s.tmp", filename1);
    sprintf(temp_filename2, "%s.tmp", filename2);
    
    FILE *fp1 = fopen(temp_filename1, "w");
    FILE *fp2 = fopen(temp_filename2, "w");
    
    if (!fp1 || !fp2) {
        printf("Error opening temporary files for rewriting\n");
        if (fp1) fclose(fp1);
        if (fp2) fclose(fp2);
        return;
    }
    
    // Track whether we've successfully written any data
    int data_written = 0;
    
    // Create our own stack for traversal
    struct Stack {
        node_freq* nodes[1000];
        int top;
    } stack;
    stack.top = -1;
    
    // Define stack operations
    #define STACK_PUSH(n) (stack.nodes[++stack.top] = (n))
    #define STACK_POP() (stack.nodes[stack.top--])
    #define STACK_EMPTY() (stack.top < 0)
    
    // Do an inorder traversal to preserve order
    node_freq* current = t;
    
    while (current != NULL || !STACK_EMPTY()) {
        // Reach the leftmost node
        while (current != NULL) {
            STACK_PUSH(current);
            current = current->left;
        }
        
        // Process current node
        current = STACK_POP();
        
        // Write to files - make sure we add newline to questions
        fprintf(fp1, "%s\n", current->quest);
        fprintf(fp2, "%d\n", current->freq);
        data_written = 1;
        
        // Move to right subtree
        current = current->right;
    }
    
    // Close temp files
    fclose(fp1);
    fclose(fp2);
    
    // Only replace original files if we successfully wrote data
    if (data_written) {
        // Replace original files with temp files
        remove(filename1);
        remove(filename2);
        rename(temp_filename1, filename1);
        rename(temp_filename2, filename2);
        printf("Frequency files updated successfully.\n");
    } else {
        // Remove temp files if no data was written
        remove(temp_filename1);
        remove(temp_filename2);
        printf("Warning: No data was written to frequency files.\n");
    }
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