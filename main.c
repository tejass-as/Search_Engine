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
            // printf("\nWant to continue [y/n] ?");
            // fflush(stdin);
            // scanf("%c", &j);
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
        a = p4->freq;
        b = max_using_stack(p4, a);
        printf("\n**** Most Frequently searched questions ****\n");
        print_max(p4, b);
        Rewrite(p4, "freq_bck.txt", "freq.txt");
        printf("\n");
    } else if (strcmp(argv[1], "-fl") == 0) {
        node_freq *q = NULL;
        q = load_from_file_freq();
        c = q->freq;
        d = min_using_stack(q, c);
        printf("\n**** Least searched questions ****\n");
        print_min(q, d);
        Rewrite(q, "freq_bck.txt", "freq.txt");
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