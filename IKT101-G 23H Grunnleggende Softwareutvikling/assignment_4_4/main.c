#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main() {

    char input[20];
        printf("Input string\n");
        scanf("%s", &input);
    char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
    int count[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < strlen(input); ++j) {
            if (alphabet[i] == tolower(input[j])) {
                count[i]++;
            }
        }
    }

    for (int i = 0; i < 26; ++i) {
        if(count[i] != 0) {
            printf("'%c' : %d\n", alphabet[i], count[i]);
        }
    }

}
