#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    int count;
    struct Trie *sub[26];
};

void insert(struct Trie **ppTrie, char *word)
{
    struct Trie *temp = *ppTrie;
    int length = strlen(word);
    for(int i = 0; i < length; i++)
    {
        int index = word[i] -'a';
        if(temp->sub[index] == NULL)
        {
            temp->sub[index] = (struct Trie*)calloc(1, sizeof(struct Trie));
        }
        temp = temp->sub[index];
    }
    temp->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *temp = pTrie;

    for(int x = 0; word[x] != '\0'; x++)
    {
        int index = word[x] - 'a';
        if(temp == 0)
        {
            return 0;
        }
        temp = temp->sub[index];
    }
    return temp->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie != NULL)
    {
        for(int x = 0; x < 26; x++)
        {
            if(pTrie->sub[x])
            {
                pTrie->sub[x] = deallocateTrie(pTrie->sub[x]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

int main(void)
{
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    struct Trie *trie = NULL;
    trie = (struct Trie*) malloc(sizeof(struct Trie));
    for(int i = 0; i < 26; i++)
    {
        trie->sub[i] = NULL;
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    int wordCount = sizeof(pWords) / sizeof(char*);
    for(int x = 0; x < wordCount; x++)
    {
        insert(&trie, pWords[x]);
    }


    for (int i = 0; i < 5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");
    return 0;
}