#include <iostream>
#include <fstream>
#include "hashtab.hpp"
#include "preftree.hpp"
#include "rbtree.hpp"
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
using namespace std;

#define MAX_WORDS 200000


double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

int main() {
    char words[MAX_WORDS][10];
    for (int i = 0; i < MAX_WORDS; i++){
        cin >> words[i];
    }

    FILE *file;
    file = fopen("data_ex1.txt", "w");
    char str[100];

    RedBlackTree<char> rbtree;
    struct trie *tree = new struct trie;
    struct listnode *hashtab[HASHTAB_SIZE];
    hashtab_init(hashtab);

    for (int i = 2; i <= MAX_WORDS; i++) {
        rbtree.insert(*words[i - 1]);
        trie_insert(tree, words[i - 1], words[i]);
        hashtab_add(hashtab, words[i - 1], i - 1);
        if (i % 10000 == 0)
        {
            char w[10];
            strcpy(w, words[getrand(0, i - 1)]);
            int k = 1;
            double t1 = wtime() * k;
            rbtree.search(w[i - 1]);
            t1 = wtime() * k - t1;
            printf("Trie n=%d; time = %.30lf\n", i, t1);

            
            double t2 = wtime() * k;
            trie_lookup(tree, w);
            t2 = wtime() * k - t2;
            printf("Trie n=%d; time = %.30lf\n", i, t2);


            double t3 = wtime() * k;
            hashtab_lookup(hashtab, w);
            t3 = wtime() * k - t3;
            printf("Hashtab n=%d; time = %.30lf\n\n", i, t3);

            fputs(str, file);
        }
    }
    delete(tree);

    
    return 0;
}

// int main()
// {
//     char words[MAX_WORDS][10];
//     FILE *file;
//     int word_count = 0;
//     file = fopen("dataA-Z.txt", "r");
//     while (fscanf(file, "%s", words[word_count]) == 1)
//     {
//         word_count++;
//     }
//     fclose(file);

//     file = fopen("data_ex1.txt", "w");
//     char str[100];

//     struct bstree *tree = bstree_create(words[0], 0);

//     struct listnode *hashtab[HASHTAB_SIZE];
//     hashtab_init(hashtab);

//     for (int i = 2; i <= MAX_WORDS; i++)
//     {
//         bstree_add(tree, words[i - 1], i - 1);
//         hashtab_add(hashtab, words[i - 1], i - 1);
//         if (i % 10000 == 0)
//         {
//             char w[10];
//             strcpy(w, words[getrand(0, i - 1)]);
//             int k = 1;
//             double t1 = wtime() * k;
//             bstree_lookup(tree, w);
//             t1 = wtime() * k - t1;
//             printf("RBtree n=%d; time = %.9lf\n", i, t1);

//             double t2 = wtime() * k;
//             hashtab_lookup(hashtab, w);
//             t2 = wtime() * k - t2;
//             printf("Hashtab n=%d; time = %.9lf\n\n", i, t2);

//             snprintf(str, 100, "%d %.9lf %.9lf\n", i, t1, t2);
//             fputs(str, file);
//         }
//     }
// }