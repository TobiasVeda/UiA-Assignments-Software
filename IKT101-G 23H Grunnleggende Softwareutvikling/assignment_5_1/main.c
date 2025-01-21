#include <stdio.h>
#include <string.h>

typedef struct {
    int student_id;
    char name[50];
    int age;
} student_t;

student_t struct_input(student_t student){
    printf("Input student id\n");
    scanf("%d", &student.student_id);
    printf("Input name\n");

    // Clear the input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    fgets(student.name, sizeof(student.name), stdin);
    student.name[strlen(student.name) -1] = 0;
    printf("Input age\n");
    scanf("%d", &student.age);

    return student;
}

void struct_print(student_t student){
    printf("Student id: %d\n", student.student_id);
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
}

int main(){
    student_t student;

    student = struct_input(student);
    struct_print(student);
}