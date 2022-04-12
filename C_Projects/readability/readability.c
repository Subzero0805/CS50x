#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentance(string text);


// index = 0.0588 * L - 0.296 * S - 15.8
// L = avg letters per 100 words
// S = avg sentance per 100 words


int main(void)
{
    string text = get_string("Text: ");
    int num_letters = count_letters(text);
    int num_words = count_words(text);
    int num_sent = count_sentance(text);

    float L = (num_letters / (float) num_words) * 100;
    float S = (num_sent / (float) num_words) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int answer = round(index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    //printf("letters: %i| words: %i| L: %f | S: %f | index: %f | answer: %i\n",num_letters,num_words, L, S, index, answer);
    printf("Grade %i\n", answer);
    return 0;
}

int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letter_count += 1;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 1;
    for (int i = 0, length = strlen(text); i <= length; i++)
    {
        if (isspace(text[i]))
        {
            word_count += 1;
        }
    }
    return word_count;

}

int count_sentance(string text)
{
    int sent_count = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            sent_count += 1;
        }
    }
    return sent_count;
}