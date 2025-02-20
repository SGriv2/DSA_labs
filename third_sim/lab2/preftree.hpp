typedef struct trie
{
    char *value;
    char ch;
    struct trie *sibling;
    struct trie *child;
} trie;

struct trie *trie_delete(struct trie *root, char *key);
struct trie *
trie_delete_dfs(struct trie *root, struct trie *parent, char *key, int *found);
struct trie *trie_insert(struct trie *root, char *key, char *value);
char *trie_lookup(struct trie *root, char *key);
trie *trie_create();
