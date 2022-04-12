// Implements a dictionary's functionality

#include <ctype.h> //
#include <stdbool.h> //
#include <stdio.h> //
#include "dictionary.h"
#include <stdint.h> //
#include <stdlib.h> //
#include <strings.h> //
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


typedef uint8_t  BYTE;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N] = {NULL};

//linked list creation function
node *create_node(int hash_num);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    //hash for the word we are checking
    int tmp_hash;
    tmp_hash = hash(word);

    // varibale we can loop over without mutating the original hash table
    // if we useed table[tmp_hash] = table[hash] -> next is because we will change the acutal
    // underlying hash table every loop

    node *curr = table[tmp_hash];

    char *currword;

    // whilst we are still within the hash table
    while (curr != NULL)
    {
        int x = strcasecmp(curr->word, word);

        // if there is a match 0 would be returned
        if (x == 0)
        {
            return true;
        }
        // there is no match, so check the next node
        curr = curr -> next;
    }

    // no match was found
    return false;
}




// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int val = toupper(word[0]) - 'A';
    return val % N;
}


//track the num of words
int COUNTER = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open.");
        return 1;
    }


    char word[LENGTH + 1];
    int index;

    // Scan each word in the file, until we reach the end of the file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a node for each word
        node *n = malloc(sizeof(node));

        //if there is no word.
        if (n == NULL)
        {
            return false;
        }

        //copy the word into the node
        strcpy(n -> word, word);

        //get the index of the word via the hash
        index = hash(word);

        //every time we check a word, increase the counter
        COUNTER++;

        // setting up the new node to point to the same pointer as the table
        // this will enable us to then point the table at the current node.
        n -> next = table[index];
        table[index] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return COUNTER;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    int buckets = 0;

    while (buckets < N)
    {
        while (table[buckets] != NULL)
        {
            node *tmp = table[buckets];
            table[buckets] = table[buckets] -> next;
            free(tmp);
        }
        buckets = buckets + 1;
    }

    return true;
}
