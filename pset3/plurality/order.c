#include <stdio.h>
#include <cs50.h>

void order(int numbers[], int size);

int main(void)
{
    int amount = get_int("Amount: ");
    int numbers[amount];
    for (int i = 0; i < amount; i++)
    {
        numbers[i] = get_int("Number: ");
    }
    order(numbers, sizeof numbers / sizeof numbers[0]);
    
}

void order(int numbers[], int size)
{
    printf("Size: %i\n", size);
    //printf("Size: %i\n", sizeof numbers[0]);
    for (int i = 0; i < size; i++)
    {
        printf("Value: %i\n", numbers[i]);
        for (int j = 0; j < size; j++)
        {
            if(numbers[i] > numbers[j])
            {
                printf("True? %i\n", numbers[i]);
                
            }
        }
    }
}