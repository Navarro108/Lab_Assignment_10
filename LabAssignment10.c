#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node structure
struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

// Initializes a TrieNode
struct TrieNode* createNode() {
    struct TrieNode* pNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    pNode->isEndOfWord = 0;
    pNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    return pNode;
}

// Inserts the word to the trie structure
void insert(struct TrieNode *root, char *word) {
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = createNode();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = 1;
    pCrawl->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word) {
    struct TrieNode* pCrawl = root;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!pCrawl->children[index])
            return 0;
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord) ? pCrawl->count : 0;
}

// Deallocate the trie structure
void deallocateTrie(struct TrieNode *root) {
    if (!root)
        return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            deallocateTrie(root->children[i]);
    free(root);
}

// Reads the dictionary file and stores words into an array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found!\n");
        exit(1);
    }
    int numWords;
    fscanf(file, "%d", &numWords);
    for (int i = 0; i < numWords; ++i) {
        pInWords[i] = (char*)malloc(256 * sizeof(char));
        fscanf(file, "%s", pInWords[i]);
    }
    fclose(file);
    return numWords;
}

int main(void) {
    char *inWords[256];
    
    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary-1.txt", inWords);
    
    struct TrieNode *root = createNode();
    // Parse line by line, and insert each word to the trie data structure
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }
    
    // Words to check for occurrences
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }
    
    // Deallocate memory
    deallocateTrie(root);
    
    return 0;
}
