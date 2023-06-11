#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // size of the pyramid, between 1 and 8
    int height;
    do
    {
        // asks and get input of the size of the pyramid
        height = get_int("Height: ");
        // will do this while the answear is incorrect
    } 
    while (height < 1 || height > 8);

    // for loop, counting first by rows then by lines
    for (int column = 1; column <= height; column++)
    {
        for (int pontos = height - column; pontos > 0; pontos--)
        {
            printf(" ");
        }
        for (int linha = 1; linha <= column; linha++)
        {
            printf("#");
        }
        // break line after each loop
        printf("\n");
    }
}
