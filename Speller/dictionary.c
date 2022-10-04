// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned int wordcounter = 0;
unsigned int freecounter = 0;

void free_node(node *head);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int t_index = hash(word);

    for (node *tmp = table[t_index]; tmp != NULL; tmp = tmp -> next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            // printf("String found.\n");
            return true;
        }
    }
    // printf("Word not found.\n");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char tmp = word[0];
    tmp = toupper(tmp);
    unsigned int hash = tmp - 'A';
    return hash;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file dictionary
    FILE *dictionary_file = fopen(dictionary, "r");

    // Check for NULL pointer
    if (dictionary_file == NULL)
    {
        printf("Could not load file.\n");
        return false;
    }
    // Max LENGTH of each word
    int length_max = LENGTH;

    // Buffer to store each word
    char *buffer = malloc(sizeof(char) * length_max);

    // If dictionary has not ended
    while (fscanf(dictionary_file, "%s", buffer) != EOF)
    {
        // Create a new node pointer and allocate memory
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
        {
            printf("Out of memory.\n");
            free(new_node);
            free(buffer);
            fclose(dictionary_file);
            return false;
        }
        // Copy string from buffer to node
        strcpy(new_node -> word, buffer);

        // Hash table indexing
        unsigned int t_index = hash(new_node -> word);

        new_node -> next = table[t_index];
        table[t_index] = new_node;
        wordcounter++;
    }
    fclose(dictionary_file);
    free(buffer);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordcounter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        free_node(table[i]);
    }
    if (freecounter != wordcounter)
    {
        return false;
    }
    return true;
}

// Recursive function to unload a single linked list
void free_node(node *head)
{
    // Check if pointer is NULL
    if (head == NULL)
    {
        return;
    }
    // Apply the function recursively to the next node
    free_node(head-> next);

    // Stack the freeing of the current node
    free(head);
    freecounter++;
}




