#include "word_lib.h"
#include <stdio.h>
#include <string.h>
#define word 30
#define txt 1024
int main()
{
    char input_word[word];
    char input_text[txt];
    
      
    scanf("%[^\n\t' ']",input_word);
    scanf("%[^~]",input_text);
    strcat(input_text,"~");
    gem_seq(input_word,input_text);
    athbash_seq(input_word,input_text);
    anagram_seq(input_word,input_text);
    return 0;
}