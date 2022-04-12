#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Please enter Height (1-8): ");
    }
    while (height < 1 || height > 8);

    //printf("Stored: %i\n",height);
    //for each column
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }
        //for each row, for each j that is less than i, each cell that is less than the current column num
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}