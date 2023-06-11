// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"


#define ALPHABET_SIZE 26

// Represents a node - like in the speller/load video CS50's
typedef struct node
{
    bool is_word; // to know if the word ends
    struct node *children[ALPHABET_SIZE + 1];
}
node;

// create the root pointer
node *root;


int counter = 0;


// custom functions


int letterToInt(char letter)
{
    if (letter == '\'')
        return 26;
    else if (letter >= 'a' && letter <= 'z')
        return letter - 'a';
    else if (letter >= 'A' && letter <= 'Z')
        return letter - 'A';

    // case not in the alphabet
    return -1;
}

node  *nodeCreate()
{
    node *nodePointer = malloc(sizeof(node));
    nodePointer->is_word = false;
    for (int i = 0; i < ALPHABET_SIZE + 1; i++)
    {
        nodePointer->children[i] = NULL;
    }    
    return nodePointer;
}




// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node *nodePointer = root;
    for (int i = 0, length = strlen(word); i <= length; i++)
    {
        if (word[i] == '\0')
        {
            if (nodePointer->is_word == true)
                return true;
            else
                return false;
        }
        int index = letterToInt(word[i]);
        if (nodePointer->children[index] == NULL)
            return false;
        
        nodePointer = nodePointer->children[index];
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
        fclose(file);
    }


    // root of the tries node - Initialize: is_word = false and all children NULL
    root = nodeCreate();
    node *nodePointer = root;
    
    int index;
    
    // in each iteration malloc a new node
    for (char c = fgetc(file); c != EOF; c = fgetc(file))
    {

        if (c != '\n')
        {
            index = letterToInt(c);
            if (nodePointer->children[index] == NULL)
            {
                nodePointer->children[index] = nodeCreate();
            }
            nodePointer = nodePointer->children[index];
        }
        else
        {
            nodePointer->is_word = true;
            counter += 1;
            nodePointer = root;
        }

    }
    
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}


void unloadTracker(node *nodePointer)
{
    
    for (int i = 0; i < ALPHABET_SIZE + 1; i++)
    {
        if (nodePointer->children[i] != NULL)
        {
           unloadTracker(nodePointer->children[i]); 
        }
    }
    
    free(nodePointer);    
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // using recursion
    
    unloadTracker(root);
    return true;

}
