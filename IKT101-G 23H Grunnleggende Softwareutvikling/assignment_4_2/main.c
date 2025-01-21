#include <stdio.h>
#include <string.h>
#include <ctype.h>
char input_word[20];

void string_upper(){
    for (int i = 0; i < strlen(input_word); ++i) {
        input_word[i] = toupper(input_word[i]);
    }
}
void string_lower(){
    for (int i = 0; i < strlen(input_word); ++i) {
        input_word[i] = tolower(input_word[i]);
    }
}


int main() {

    printf("Input a word with an even number of characters\n");
    scanf("%s", &input_word);

    char input_word2[strlen(input_word)];
    strcpy(input_word2,input_word);

    string_upper();
    printf("The word in uppercase is '%s'\n", input_word);
    string_lower();
    printf("The word in lowercase is '%s'\n", input_word);

    printf("The word split in two is '");
    int midpoint = strlen(input_word)/2;
        for (int i = 0; i < strlen(input_word); ++i) {
        if (midpoint == i){
            printf(" - ");
            printf("%c", input_word2[i]);
        } else{
            printf("%c", input_word2[i]);
        }

    }
    printf("'");

}
