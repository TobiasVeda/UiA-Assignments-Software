#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0; // kunne sende inn i hver funksjon, men alle funksjoner bruker den unntak main

typedef struct {
    char name[50];
    int age;
} struct_t;

void sort_struct(struct_t *student){
    struct_t temp;
    for (int i = 0; i < count-1; ++i) { // -1 prevent accessing OOB (i+1)

            if (student[i].age > student[i + 1].age) {
            temp = student[i + 1];
            student[i + 1] = student[i];
            student[i] = temp;
            }


    }
    int not_in_order = 0;
    for (int i = 0; i < count-1; ++i) { // -1 prevent accessing OOB (i+1)
        if(student[i].age > student[i+1].age){
            not_in_order++;
        };
    }
    if(not_in_order > 0){
        sort_struct(student);
    }
}

void struct_print(struct_t *student){

    if(count==0){
        printf("No students were given");
        return;
    }

    printf("Count: %d\n", count);
    for (int i = 0; i < count; ++i) {
        printf("Name = %s, Age = %d\n", student[i].name, student[i].age);
    }

    sort_struct(student);
    printf("Youngest: %s\n", student[0].name);
    printf("Oldest: %s\n", student[count-1].name);
};

//    int num = 5;
//    int *pnum = &num;
//    *pnum = 7;
//    pnum = 0x000
//
// *array == array[]

int main(){
    struct_t *student = malloc(sizeof(struct_t));

    for (int i = 0; i != -1; ++i) {
        student = realloc(student, (i+1)*sizeof(struct_t));

        printf("Input name\n");

        char stop[sizeof(student->name)/sizeof(char)] = {0};

        fgets(stop, sizeof(student->name), stdin);
        stop[strlen(stop) - 1] = 0;

        if(strcmp(stop,"stop")==0){
            break;
        } else{
            strcpy(student[i].name,stop);
        }

        printf("Input age\n");
        scanf("%d", &student[i].age);

        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        count++;
    }

    struct_print(student);
    free(student);
}


