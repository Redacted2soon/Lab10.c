#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *children[26];
};

void insert(struct Trie **ppTrie, char *word) {
    if (ppTrie == NULL || word == NULL) {
        return;
    }
    struct Trie *pTrie = *ppTrie;
    if (pTrie == NULL) {
        pTrie = (struct Trie*) malloc(sizeof(struct Trie));
        if (pTrie == NULL) {
            return;
        }
        pTrie->count = 0;
        for (int i = 0; i < 26; i++) {
            pTrie->children[i] = NULL;
        }
        *ppTrie = pTrie;
    }
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            struct Trie *newTrie = (struct Trie*) malloc(sizeof(struct Trie));
            if (newTrie == NULL) {
                return;
            }
            newTrie->count = 0;
            for (int j = 0; j < 26; j++) {
                newTrie->children[j] = NULL;
            }
            pTrie->children[index] = newTrie;
        }
        pTrie = pTrie->children[index];
    }
    pTrie->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    if (pTrie == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (pTrie->children[index] == NULL) {
            return 0;
        }
        pTrie = pTrie->children[index];
    }
    return pTrie->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL) {
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;
    char *pWords[] = {"not", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}
