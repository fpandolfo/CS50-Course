#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // first check the args on command line
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // then if its ok, declare variables
    int key = atoi(argv[1]);
    int letra = 0;
    int index = 0;
    
    // get the text for encrypt
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    // check char by char if it is alpha or not
    for (int i = 0; i < strlen(text); i++)
    {
        letra = text[i];
        // if its upper and alpha, shift alpha index
        if (isalpha(text[i]) && isupper(text[i]))
        {
            index = letra - 65;
            letra = (index + key) % 26;
            letra += 65;
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            index = letra - 97;
            letra = (index + key) % 26;
            letra += 97;
        }
        printf("%c", letra);
    }
    printf("\n");
}