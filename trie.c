#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "trie.h"

// for creating a new node in trie
node_trie *new_node() {
    node_trie *t = NULL;
    t = (node_trie *)malloc(sizeof(node_trie));
    if (!t)
        return NULL;
    else
    {
        int i;
        t->end_of_quest = 0;
        for (i = 0; i < 26; i++)
            t->child[i] = NULL;
    }
    return t;
}


node_trie *insert_from_file()
{

    node_trie *root = NULL;

    // creating a new node at root
    if ((root = (malloc(sizeof(node_trie)))) == NULL)
        printf("Out of Memory");
    
    int i;
    for (i = 0; i < 26; i++)
        root->child[i] = NULL;
    
    // value of end_of_quest of new node is kept 0
    root->end_of_quest = 0;

    int index;

    node_trie *tmp = root;

    // opening the database file
    FILE *fp = fopen("db.txt", "r+");
    if (!fp)
        printf("Error in opening the database.");
    
    char quest[10000];
    char ans[200000];

char *line = NULL;
size_t len = 0;
    // inserting all the questions and answers from the database in the trie
    while (getline(&line, &len, fp) != -1)
    {
        char *separator = strstr(line, " ? ");
        if (separator == NULL) {
            printf("Error: Incorrect line format: %s\n", line);
            continue;
        }

        // Extract the question and answer strings
        *separator = '\0'; // Null-terminate the question part
        char *quest = line;
        char *ans = separator + 3; // Move past " - " to point to the start of the answer

            // Insert the question into the trie
            int quest_len = strlen(quest);
            for (int i = 0; i < quest_len; i++) {
                if (isalpha(quest[i]))
                    index = (int)tolower(quest[i]) - 'a';
                else if (quest[i] == ' ') {
                    tmp->space = 1;
                    continue;
                }

                // ... Rest of the code remains unchanged ...
                if (index > 25 || index < 0)
                    continue;
                // creating a new node for a character
                if (tmp->child[index] == NULL) {
                    if ((tmp->child[index] = malloc(sizeof(node_trie))) == NULL)
                        printf("Out of memory");
                    
                    tmp = tmp->child[index];
                    tmp->space = 0;
                    int j;
                    for (j = 0; j < 26; j++)
                        tmp->child[j] = NULL;
                    tmp->end_of_quest = 0;
                } else
                    tmp = tmp->child[index];
                
            }

            tmp->end_of_quest = 1;
            strcpy(tmp->ans, ans);

            tmp = root;
            free(line);
        line = NULL;
        len = 0;
    }
    fclose(fp);
    free(line);
    return root;
}

char *search(node_trie *root, char *key) {
    // char pref[100];
    node_trie *tmp = root;

    int i;
    for (i = 0; key[i] != '\0'; i++) {
        // pref[i] = key[i];
        int index = (int)tolower(key[i]) - 'a';
        // when a character of the question is not present then return null as that question is not present
        if (tmp->child[index] == NULL)
            return NULL;
        // pref[i] = key[i];
        tmp = tmp->child[index];
    }

    // after reaching the end of the question(i.e. last node) return the ans which is stored
    if (tmp->end_of_quest == 1)
        return tmp->ans;
    else
        return NULL;
    
}

// Helper function to remove spaces from a string
void remove_spaces(char a[]) {
    int i = 0;
    int j = 0;
    while (a[i]) {
        if (a[i] != ' ')
            a[j++] = a[i];
        i++;
    }
    a[j] = '\0';
}

int isLastNode(node_trie* root) {
    for (int i = 0; i < 26; i++) {
        if (root->child[i])
            return 0;
    }
    return 1;
}

void suggestions(node_trie *root, char currPrefix[]) {
    // Store the original length of currPrefix
    int originalLength = strlen(currPrefix);

    // if we get the complete question print the entire question
    if (root->end_of_quest)
        printf("%s\n", currPrefix);
    
    // All children struct node pointers are NULL (when we reach the last node return)
    if (isLastNode(root))
        return;
    
    for (int i = 0; i < 26; i++) {
        if (root->child[i]) {
            // append current character to currPrefix string
            int p = 97 + i;
            char c = (char)p;

            if (root->space == 1) {
                char sp = ' ';
                strncat(currPrefix,&sp, 1);
            }

            strncat(currPrefix, &c, 1);

            // recur over the rest
            suggestions(root->child[i], currPrefix);

            // Reset currPrefix to its original length
            currPrefix[originalLength] = '\0';
        }
    }
}


// print suggestions for given query prefix.
int printAutoSuggestions(node_trie *root, char query[]) {
    node_trie *temp = root;

    // Check if prefix is present and find the node with last character of given string.
    int i;
    int n = strlen(query);
    for (i = 0; i < n; i++) {
        int index = (int)tolower(query[i]) - 'a';

        // no string in the Trie has this prefix
        if (!temp->child[index])
            return 0;

        temp = temp->child[index];
    }

    // If prefix is present as a question.
    int isWord = (temp->end_of_quest == 1);

    // If prefix is last node of tree (has no children)
    int isLast = isLastNode(temp);

    // If prefix is present as a question, but there is no subtree below the last matching node.
    if (isWord && isLast) {
        printf("\n \n");
        // puts(query);
        printf("*****Match Found*****\n\n");
        printf("%s", query);
        return -1;
    }

    // If there are are nodes below last matching character.
    if (!isLast) {
        char prefix[MAX];
        strcpy(prefix, query);
        printf("\n\nMatch Found :-\n");
        suggestions(temp, prefix);
        return 1;
    }
    return 1;
}