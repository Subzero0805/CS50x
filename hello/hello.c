#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //intitalise variable (name) that stores the user's name.
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}