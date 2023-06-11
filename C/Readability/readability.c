#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // declare the sum of characters
    int sum = 0;

    // declare the sum of words
    int words = 0;

    // declare the sum of sentences
    int sentence = 0;

    // declare de grade by index
    int grade = 0;


    // get input the text to be analyzed
    string text = get_string("Text: ");

    // loop for checking each char of the text
    for (int i = 0; i < strlen(text); i++)
    {
        // checks if the char in the actual position is a letter, lower or upper
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') /*|| text[i] == '-'*/)
        {
            sum += 1;
        }
        if (text[i + 1] == ' ' || text[i + 1] == '\0')
        {
            words += 1;
        }
        if ((text[i] == '.' && text[i - 2] != 'M' && text[i - 2] != 'm' && text[i - 3] != 'M' && text[i - 3] != 'm') || text[i] == '!'
            || text[i] == '?')
        {
            sentence += 1;
        }
    }


    float L = (float) sum / (float) words * 100;
    // printf("%f\n", L);
    float S = (float) sentence / (float) words * 100;
    // printf("%f\n", S);

    float index = 0.0588 * L - 0.296 * S - 15.8;

    /*printf("%i letter(s)\n", sum);
    printf("%i word(s)\n", words);
    printf("%i sentence(s)\n", sentence);
    printf("%f\n", index);*/

    grade = round(index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}