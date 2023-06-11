#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // setting the variables
    float cash;
    int coins, change, count;

    // takes the float input, payment
    do
    {
        cash = get_float("Change owed?");
    }
    while (cash < 0);

    // change in cents, after getting just cents
    coins = (round(cash * 100));
        
    // take the change and verify the quarter quantity    
    count = coins / 25;
    change = coins % 25;

    // take the change and verify the dim quantity    
    count += change / 10;
    change = change % 10;

    // take the change and verify the nickel quantity    
    count += change / 5;
    change = change % 5;

    // take the change and verify the pennie quantity    
    count += change / 1;
    change = change % 1;
    
    printf("%i", count);
}
