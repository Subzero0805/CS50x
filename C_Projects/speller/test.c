#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//creating a node structure
typedef struct node
{
    char letters[3];
    struct node *next;
}
node;

//creating hashtable
node *hash_table[26] = {NULL};

//list of strings
char *words[4] = {"aa", "ab", "b", "c"};

//global head of the linked list


//hash function
int hash(char *letters);

int main(void)
{
    node *list = NULL;

    node *c = malloc(sizeof(node));
    if (c == NULL)
    {
        return 1;
    }
    node *head = malloc(sizeof(node));
    if (head == NULL)
    {
        return 1;
    }
    //c -> letters[3] = "aa"
    for (int i = 0; i < 4; i++)
    {
        char *curr_word = words[i];
        //printf("%s\n",curr_word);
        //for (int j = 0; curr_word[j] != '\0'; j++)
        //{
        //c -> letters[i] = curr_word[i];
        //}
        int hash_val = hash(&curr_word[0]);
        //printf("%i\n", hash_val);
        if (hash_table[hash_val] != NULL)
        {

            for (int j = 0; curr_word[j] != '\0'; j++)
            {
                c -> letters[i] = curr_word[i];
                //printf("%c\n", c ->letters[i]);
            }
            c -> next = head;

            list = c;
            head = c;
        }
        else
        {
            for (int j = 0; curr_word[j] != '\0'; j++)
            {
                head -> letters[i] = curr_word[i];
                //printf("%c\n", head ->letters[i]);
            }
            head -> next = NULL;
            list = head;
            hash_table[hash_val] = list;
        }

    }

    printf("%s\n", hash_table[0] -> letters);
    printf("%s\n", hash_table[1] -> letters);
    printf("%s\n", hash_table[2] -> letters);


    /*char *letter_a = words[0];
    for (int i = 0; letter_a[i] != '\0'; i++)
    {
        c -> letters[i] = letter_a[i];
    }

    //int hash_val_c = hash(c -> letters[3]);

    int hash_val_c = hash(&c -> letters[0]);
    printf("%i\n",hash_val_c);
    c -> next = NULL;
    list = c;
    hash_table[hash_val_c] = list;

    node *a = malloc(sizeof(node));
    if (a == NULL)
    {
        return 1;
    }
    //a -> letters[0] = "ab";
    char *letter_b = words[1];
    for (int i = 0; letter_b[i] != '\0'; i++)
    {
        a -> letters[i] = letter_b[i];
    }
    //int hash_val_a = hash(a -> letters);
    int hash_val_a = hash(&a -> letters[0]);
    printf("%i\n", hash_val_a);
    //printf("%s\n",a -> letters);
    a -> next = NULL;
    list -> next = a;

    for (node *tmp = list; tmp != NULL; tmp = tmp -> next)
    {
        printf("%s\n", tmp -> letters);
    }*/
    //print first node in location hash table 0
    //printf("%s\n",hash_table[hash_val_a] -> letters);
    //print second node in location hash table 0
    //printf("%s\n",hash_table[hash_val_a] -> next -> letters);

    while (list != NULL)
    {
        node *tmp = list -> next;
        free(list);
        list = tmp;
    }



    return 0;
}

int hash(char *letters)
{
    int val = letters[0] - 'a';
    return val;
}
