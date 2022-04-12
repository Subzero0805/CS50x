#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

bool only_digits(string s);
char encrypted(char letter, int key);
char case_check(char curr_letter, int key);


int main(int argc, string argv[])
{
    //checking amount of inputs
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //idigit needs a char in order to work
    if (only_digits(argv[1]) != true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //making the inputted key a integer
    int key = atoi(argv[1]);

    //getting plaintext from user
    string text = get_string("plaintext:  ");


    //string encrypt_text = encrypted(text, key);

    printf("ciphertext: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char curr_letter = text[i];
        char encrypt_char = encrypted(curr_letter, key);
        printf("%c", encrypt_char);
    }
    printf("\n");

    //printf("ciphertext: %s\n",encrypt_text);
    return 0;

}

bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}


//updating the string so it's encrypted
char encrypted(char letter, int key)
{
    /* This for loop section is not needed, instructions asks for invidual charaters
    for(int i = 0, len = strlen(s); i < len; i++)
    {
        char letter = s[i];
        //letter is a character from a - z
        if (isalpha(letter))
        {
            //using the case_check function
            new_letter = case_check(letter, key);
            //replacing the current letter with the new letter
            //text[i] = new_letter; Not needed!
        }
    }*/

    //letter is a character from a - z
    if (isalpha(letter))
    {
        //using the case_check function
        char new_letter = case_check(letter, key);
        return new_letter;
    }
    else
    {
        return letter;
    }
}

//function to check for upper/lower case
char case_check(char curr_letter, int key)
{
    char changed_letter;
    //lowercase?
    if (islower(curr_letter))
    {
        //is the letter out of the lower case range?
        if (curr_letter + key > 122)
        {
            /*use the remainder for key */
            int new_key = key % 26;
            //is the new_key going to put the letter out of range?
            if (curr_letter + new_key > 122)
            {
                changed_letter = (curr_letter + new_key) - 26;
            }
            else
            {
                changed_letter = curr_letter + new_key;
            }
        }
        else
        {
            changed_letter = curr_letter + key;
        }
    }
    //the letter must be upper case
    else
    {
        //is the letter ouf of the upper case range?
        if (curr_letter + key > 90)
        {
            int new_key = key % 26;
            if (curr_letter + new_key > 122)
            {
                changed_letter = (curr_letter + new_key) - 26;
            }
            else
            {
                changed_letter = curr_letter + new_key;
            }
        }
        else
        {
            changed_letter = curr_letter  + key;
        }
    }
    return changed_letter;
}