#include <cs50.h>
#include <stdio.h>

//setting functions for later.
void block_with_space(int n);


int main(void)
{
    int height;
    do
    {
        height = get_int("Please enter Height (1-8): ");
    }
    while (height < 1 || height > 8);
    //using function to create blocks based on height
    block_with_space(height);
}




//function to create a reversed block
void block_with_space(int n)
{
    //Here n represents the selected height
    for (int i = 0; i < n; i++)
    {
        //creating spaces to cause the first cascade to go from right to left.
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
        //cascading blocks.
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        //print a space between the next cascading blocks
        printf("  ");
        //creating cascading blocks from left to right
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
