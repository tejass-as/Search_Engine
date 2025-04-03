#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "splaytree.h"

// initialize the splay tree
void initSplay(root *t) {
    *t = NULL;
    return;
}

// performs right rotation
void rightrotate(root *t, node *r) {

    node *p = r->left;
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

// performs left rotation
void leftrotate(root *t, node *r) {
    node *p = r->right;
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

// performs splaying operation
void splay(root *t, node *n) {
    node *r = *t;

    while (n->parent != NULL) {

        if (n->parent == r) { // node is a child of root, one rotation

            if (n == n->parent->left)
                rightrotate(t, n->parent);
            else
                leftrotate(t, n->parent);
        } else {

            node *p = n->parent;
            node *q = p->parent; // grandparent

            if (n->parent->left == n && p->parent->left == p) { // both are left children
                rightrotate(t, q);
                rightrotate(t, p);
            } else if (n->parent->right == n && p->parent->right == p) { // both are right children
                leftrotate(t, q);
                leftrotate(t, p);
            } else if (n->parent->right == n && p->parent->left == p) {
                leftrotate(t, p);
                rightrotate(t, q);
            } else if (n->parent->left == n && p->parent->right == p) {
                rightrotate(t, p);
                leftrotate(t, q);
            }
        }
    }
}

// insertion
void insert(root *t, char time[200], char qu[20000]) {

    node *nn = (node *)malloc(sizeof(node));

    if (!nn)
        return;

    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    strcpy(nn->time, time);
    strcpy(nn->quest, qu);

    if (*t == NULL) {
        *t = nn;
        return;
    }

    node *p, *q = NULL;
    p = *t;
    while (p) {
        q = p;
        if (strcmp(p->time, time) == 0) {
            free(nn);
            return;
        }

        if (strcmp(p->time, time) > 0)
            p = p->left; // advance p
        else
            p = p->right;
    }

    if (strcmp(q->time, time) > 0)
        q->left = nn;
    else
        q->right = nn;
    
    nn->parent = q;
    splay(t, nn);
    return;
}

// gives the time when the question is searched
char *create_key() {
    time_t now;
    time(&now);
    char *dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0';
    return dt;
}

/*inserts the question searched in the backup question file ,time file 
and frequency file*/
void insert_in_file(char *key, int freq) {
    char time[200];
    char *td = create_key();
    strcpy(time, td);
    int found = 0;
    
    // First check if the question already exists in the frequency file
    FILE *fp_check = fopen("freq_bck.txt", "r");
    FILE *fp_freq_check = fopen("freq.txt", "r");
    
    if (fp_check && fp_freq_check) {
        char line[20000];
        int current_freq;
        char temp_file_bck[20000] = "";
        char temp_file_freq[20000] = "";
        
        // Read through the files to find if question exists
        while (fgets(line, sizeof(line), fp_check)) {
            line[strcspn(line, "\n")] = 0; // Remove newline
            fscanf(fp_freq_check, "%d\n", &current_freq);
            
            if (strcmp(line, key) == 0) {
                // Question found, increment frequency
                current_freq++;
                found = 1;
            }
            
            // Build temp content
            strcat(temp_file_bck, line);
            strcat(temp_file_bck, "\n");
            
            char freq_str[20];
            sprintf(freq_str, "%d\n", current_freq);
            strcat(temp_file_freq, freq_str);
        }
        
        fclose(fp_check);
        fclose(fp_freq_check);
        
        if (found) {
            // Rewrite the files with updated frequencies
            FILE *fp_bck_write = fopen("freq_bck.txt", "w");
            FILE *fp_freq_write = fopen("freq.txt", "w");
            
            if (fp_bck_write && fp_freq_write) {
                fprintf(fp_bck_write, "%s", temp_file_bck);
                fprintf(fp_freq_write, "%s", temp_file_freq);
                
                fclose(fp_bck_write);
                fclose(fp_freq_write);
            }
        }

    }
    
    // If question wasn't found, add it as a new entry
    if (!found) {
        // Add to history files
        FILE *fp1 = fopen("backup.txt", "a");
        if (!fp1)
            printf("error1");
        fprintf(fp1, "%s\n", key);
        fclose(fp1);

        FILE *fp2 = fopen("backup_key.txt", "a");
        if (!fp2)
            printf("error2");
        fprintf(fp2, "%s\n", time);
        fclose(fp2);

        // Add to frequency files with initial frequency of 1
        FILE *fp3 = fopen("freq_bck.txt", "a");
        if (!fp3)
            printf("error3");
        fprintf(fp3, "%s\n", key);
        fclose(fp3);

        FILE *fp4 = fopen("freq.txt", "a");
        if (!fp4)
            printf("error4");
        fprintf(fp4, "%d\n", 1); // Start with frequency 1, not 0
        fclose(fp4);
    }
}

// loads the content from the backups files in the splay tree
node *load_from_file() {

    char quest[20000];
    char time_q[200];

    root t;
    initSplay(&t);

    FILE *fp1 = fopen("backup_key.txt", "r");
    FILE *fp2 = fopen("backup.txt", "r");

    if (!fp1 || !fp2)
        return t;

    while (fgets(quest, 200, fp2)) {
        fgets(time_q, 200, fp1);
        insert(&t, time_q, quest);
    }

    fclose(fp1);
    fclose(fp2);
    return t;
}

// inorder traversal
void inorder(root t) {
    if (!t)
        return;
    inorder(t->left);
    printf("%s -- %s", t->quest, t->time);
    if (t->parent == NULL)
        printf("Null\n");
    else
        printf("\n%s - %s\n", t->parent->quest, t->parent->time);

    inorder(t->right);
}

// preorder traversal
void preorder(root t) {
    if (!t)
        return;
    printf("\033[1;34m%s ---- %s\033[0m\n\n", t->quest, t->time);
    preorder(t->left);
    preorder(t->right);
}

// gives the previous question which was searched
void recent_quest(root t) {
    printf("%s >> %s", t->quest, t->time);
    return;
}

void display_history(root t) {
    printf("\n\033[1;33m*****HISTORY*****\033[0m\n");
    preorder(t);
}

void destroy(root *t) {
    if (*t == NULL)
        return;
    destroy(&(*t)->left);
    destroy(&(*t)->right);
    free((*t));
}