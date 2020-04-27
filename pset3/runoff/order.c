#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int arr[4] = {1, 6, 4, 3};
    for (int i = 0; i < 4; i++)
    {
        printf("[%i]: %i\n", i, arr[i]);
        for (int j = 0; j < 4; j++)
        {
            int temp;
            if (arr[i] < arr[j])
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                
            }
        }
    }
    printf("\n\n\n");
    for (int i = 0; i < 4; i++)
    {
        printf("[%i]: %i\n", i, arr[i]);
    }

}