#include <stdio.h>
#include <string.h>



int main() {
    char word1[20];
    char word2[20];
    char substring_test;

    printf("Input first word\n");
    scanf("%s", &word1);
    printf("Input second word\n");
    scanf("%s", &word2);
    printf("\n");

    if(strcmp(word1, word2) == 0){
        printf("The words are equal\n");
    } else{
        printf("The words are not equal\n");
    }

    if(strlen(word1) >= strlen(word2)){ //word1 is longer. test if word2 is substring
        substring_test = strstr(word1, word2);
        if(substring_test != NULL){
            printf("Word 2 is a substring of word 1");
        } else{
            printf("No substrings found");
        }
    } else if(strlen(word1) < strlen(word2)){ //word2 is longer. test if word1 is substring
        substring_test = strstr(word2, word1);
        if(substring_test != NULL){
            printf("Word 1 is a substring of word 2");
        } else{
            printf("No substrings found");
        }
    }




}
