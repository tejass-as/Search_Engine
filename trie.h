#define MAX 200000

typedef struct node_trie {
    struct node_trie* child[26];
    int end_of_quest;
    int space;
    char ans[MAX];
} node_trie;

node_trie *insert_from_file();

void remove_spaces(char a[]);

char* search(node_trie *root,char* key);

int printAutoSuggestions(node_trie* root,char query[]) ;