#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "trie.h"
#include "splaytree.h"
#include "splaytree_freq.h"

int main(int argc, char *argv[]) {

    char quest[10000];
    char ans[MAX];
    char prefix[MAX];
    int a, b, c, d, p1, k;
    char j;
    node_trie *root = insert_from_file();

    if(argc == 1) {
        printf("\n");
        printf(" =============================================\n");
        printf(" |             SEARCH ENGINE                |\n");
        printf(" =============================================\n");
        printf(" |  Use the following options               |\n");
        printf(" |                                          |\n");
        printf(" |  -s Search for a question                |\n");
        printf(" |  -a Auto-suggest based on prefix         |\n");
        printf(" |  -r View recently asked questions        |\n");
        printf(" |  -h View search history                  |\n");
        printf(" |  -fm View most frequently searched       |\n");
        printf(" |  -fl View least frequently searched      |\n");
        printf(" |  -d Clear search history                 |\n");
        printf(" |                                          |\n");
        printf(" =============================================\n");
        return 0;
    }

    if (strcmp(argv[1], "-s") == 0) {
        while (1) {

            fflush(stdin);
            printf("\nEnter question : ");
            scanf("%[^\n]s", quest);
            insert_in_file(quest, 0);

            remove_spaces(quest);

            if (search(root, quest)) {
                strcpy(ans, search(root, quest));
                printf("%s", ans);
            } else {
                printf("\nTry Searching for another question .....\n");
            }
            fflush(stdin);
            printf("\nWant to continue [y/n] ?");
            fflush(stdin);
            scanf("%c", &j);
            if (j == 'n') {
                break;
            }
        }
    } else if (strcmp(argv[1], "-a") == 0) {
        for (k = 2; k < argc; k++) {
            strcat(prefix, argv[k]);
        }
        remove_spaces(prefix);
        p1 = printAutoSuggestions(root, prefix);
        printf("\n");
    } else if (strcmp(argv[1], "-r") == 0) {
        node *p2 = load_from_file();
        printf("\n*** Recently asked question : ***\n\n");
        recent_quest(p2);
        destroy(&p2);
        printf("\n");
    } else if (strcmp(argv[1], "-h") == 0) {
        node *p3 = load_from_file();
        display_history(p3);
        destroy(&p3);
        printf("\n");
    } else if (strcmp(argv[1], "-fm") == 0) {
        node_freq *p4 = NULL;
        p4 = load_from_file_freq();
        
        if (p4 == NULL) {
            printf("No frequency data available.\n");
            return 1;
        }
        
        // Find the maximum frequency
        int max_frequency = max_using_stack(p4, 0); // Start with 0 as initial max
        
        printf("\n**** Most Frequently searched questions ****\n");
        print_max(p4, max_frequency);
        
        // No need to rewrite files after just viewing
        // Rewrite(p4, "freq_bck.txt", "freq.txt");
        
        printf("\n");
    } else if (strcmp(argv[1], "-fl") == 0) {
        node_freq *q = NULL;
        q = load_from_file_freq();
        
        if (q == NULL) {
            printf("No frequency data available.\n");
            return 1;
        }
        
        // Find the minimum frequency - start with INT_MAX or q's frequency
        int min_frequency = min_using_stack(q, INT_MAX);
        
        printf("\n**** Least searched questions ****\n");
        print_min(q, min_frequency);
        
        // No need to rewrite files after just viewing
        // Rewrite(q, "freq_bck.txt", "freq.txt");
        
        printf("\n");
    } else if (strcmp(argv[1], "-d") == 0) {
        fclose(fopen("backup.txt", "w"));
        fclose(fopen("backup_key.txt", "w"));
        fclose(fopen("freq.txt", "w"));
        fclose(fopen("freq_bck.txt", "w"));
        printf("\n\n\tBrowser history cleared..!!!\n");
    }

    return 0;
}