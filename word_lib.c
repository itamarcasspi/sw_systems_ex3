#include "word_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD 30

void reverseString(char *str)
{
    int l, i;
    char *begin_ptr, *end_ptr, ch;
    l = strlen(str);
    begin_ptr = str;
    end_ptr = str;
    for (i = 0; i < l - 1; i++)
    {
        end_ptr++;
    }
    for (i = 0; i < l / 2; i++)
    {

        ch = *end_ptr;
        *end_ptr = *begin_ptr;
        *begin_ptr = ch;
        begin_ptr++;
        end_ptr--;
    }
}

int find_gem_value(char t)
{
    int ascii_val = (int)t;
    if (ascii_val > 64 && ascii_val < 91)
    {
        return ascii_val - 64;
    }
    if (ascii_val > 96 && ascii_val < 123)
    {
        return ascii_val - 96;
    }
    return 0;
}

char reverse_index(char t)
{
    int ascii_val = (int)t;
    if (ascii_val > 64 && ascii_val < 91)
    {
        return 91 - find_gem_value(t);
    }
    if (ascii_val > 96 && ascii_val < 123)
    {
        return 123 - find_gem_value(t);
    }

    return t;
}

struct Node
{
    struct Node *next, *prev;
    char data;
};

struct Node *head, *tail;

struct Node *GetNewNode(char x)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void backRemove()
{
    if (head == NULL)
    {
        return;
    }
    head = head->next;
}

int removeValue(char c)
{
    struct Node *temp = head;
    struct Node *temp_prev = temp;
    while (temp != NULL)
    {
        if (temp == head && temp->data == c)
        {
            backRemove();
            return 1;
        }
        if (temp->next == NULL && temp->data == c)
        {
            temp_prev->next = NULL;
            return 1;
        }

        if (temp->data == c)
        {
            temp_prev->next = temp->next;
            return 1;
        }
        temp_prev = temp;
        temp = temp->next;
    }
    return 0;
}

void frontInsert(char c)
{
    struct Node *temp = head;
    struct Node *newNode = GetNewNode(c);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    while (temp->next != NULL)
        temp = temp->next; // Go To last Node
    temp->next = newNode;
}

void Print()
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void seqPrint()
{
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%c", temp->data);
        temp = temp->next;
    }
}
int totalValue()
{
    int ans = 0;
    struct Node *temp = head;
    while (temp != NULL)
    {
        ans += find_gem_value(temp->data);
        temp = temp->next;
    }
    return ans;
}

int same_word_in_athbash(char *original, char *athbash_word)
{
    if (find_gem_value(*athbash_word) == 0)
    {
        return 0;
    }
    char *t1 = original, *t2 = athbash_word;
    for (; *t1 != '\0' && *t2 != '\0';)
    {
        if (find_gem_value(*t2) == 0)
        {
            t2++;
            continue;
        }
        if (*t1 != reverse_index(*t2))
        {
            return 0;
        }
        t1++;
        t2++;
    }
    return 1;
}

void loadWord(char *word)
{
    head = NULL;
    for (char *word_runner = word; *word_runner != '\0'; word_runner++)
    {
        frontInsert(*word_runner);
    }
}

//Actual functions:
void gem_seq(char *word, char *text)
{
    
    printf("Gematria Sequences: ");
    head = NULL;
    int word_value = 0;
    for (char *i = word; *i != '\0'; i++)
    {
        word_value += find_gem_value(*i);
    }
    if(word_value==0)
    {
        return;
    }
    int printed = 0;
    for (char *i = text; *i != '~' && *i != '\0';)
    {
        if (head != NULL && find_gem_value(head->data) == 0)
        {
            backRemove();
        }
        else if (totalValue() == word_value)
        {
            if (printed > 0)
            {
                printf("~");
            }
            seqPrint();
            backRemove();
            printed++;
        }
        else if (totalValue() < word_value)
        {
            frontInsert(*i);
            i++;
        }
        else if (totalValue() > word_value)
        {
            backRemove();
        }
    }
    if (totalValue() == word_value)
    {
        if (printed > 0)
        {
            printf("~");
        }
        seqPrint();
        backRemove();
        printed++;
    }
    printf("\n");
}

void athbash_seq(char *word, char *text)
{
    printf("Atbash Sequences: ");
    head = NULL;
    int printed = 0;
    for (char *i = text; *i != '~' && *i != '\0'; i++)
    {

        int word_len = strlen(word);
        int current_len = 0;
        for (char *index = i; *index != '~' && word_len > 0;)
        {
            if (find_gem_value(*index) == 0)
            {
                index++;
                current_len++;
                continue;
            }
            else
            {
                current_len++;
                index++;
                word_len--;
            }
        }
        char *current_word = malloc(sizeof(WORD));
        strncpy(current_word, i, current_len);
        if (same_word_in_athbash(word, current_word) > 0)
        {
            if (printed > 0)
            {
                printf("~");
            }
            printf("%s", current_word);
            printed++;
            continue;
        }
        char *input_word_reversed = malloc(sizeof(WORD));
        strcpy(input_word_reversed, word);
        reverseString(input_word_reversed);
        if (same_word_in_athbash(input_word_reversed, current_word) > 0)
        {
            if (printed > 0)
            {
                printf("~");
            }
            printf("%s", current_word);
            printed++;
        }
    }
    printf("\n");
}

void anagram_seq(char *word, char *text)
{
    head = NULL;
    int printed = 0;
    printf("Anagram Sequences: ");
    for (char *text_runner = text; *text_runner != '\0'; text_runner++)
    {
        loadWord(word);
        int current_len = 0;
        if (*text_runner == '\t' || *text_runner == '\n' || *text_runner == ' ')
        {
            continue;
        }

        for (char *current_word = text_runner; *current_word != '\0'; current_word++)
        {
            if (totalValue() == 0)
            {
                break;
            }
            if (*current_word == '\t' || *current_word == '\n' || *current_word == ' ')
            {
                current_len++;
                continue;
            }
            int contains = removeValue(*current_word) > 0;
            if (contains > 0)
            {
                current_len++;
                continue;
            }
            else
            {
                break;
            }
        }
        if (totalValue() == 0)
        {
            char *current_word_to_print = malloc(sizeof(WORD));
            strncpy(current_word_to_print, text_runner, current_len);
            if (printed > 0)
            {
                printf("~");
            }
            printf("%s", current_word_to_print);
            printed++;
        }
    }
}

