#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void string_reverse(char input_word[], char palindrome[]){

    strcpy(palindrome, input_word);
    int count;
    for (int i = 0; i < strlen(input_word); ++i) {
        count = strlen(input_word) - i -1;
        input_word[i] = palindrome[count];
    }
}

bool is_palindrome(char input_word[], char palindrome[]){
      if (strcmp(input_word, palindrome) == 0){
        return 1;
    } else{
        return 0;
    }
}


int main() {

    char input_word[20];
        printf("Input word\n");
        scanf("%s", &input_word);
    char palindrome[strlen(input_word)];

    string_reverse(input_word, palindrome);

    printf("The word contains %llu letters\n", strlen(input_word));
    if(is_palindrome(input_word, palindrome)){
        printf("The word is a palindrome\n");
    } else{
        printf("The word is not a palindrome\n");
    }
    printf("The word reversed is '%s'", input_word);

}
