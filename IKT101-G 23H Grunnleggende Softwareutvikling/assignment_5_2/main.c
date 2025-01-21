#include <stdio.h>
#include <stdlib.h> //exit
#include <string.h>

typedef struct {
    double student_id;
    char name[50];
    int age;
} student_t;

void struct_print(student_t student){
    printf("Student id: %.0lf\n", student.student_id);
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
};

student_t struct_input(student_t student){

    printf("Input student id\n");
    scanf("%lf", &student.student_id);
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

void read_file(student_t student){
    char linefeed_trash[5] = {0}; //nowhere

    FILE* read = fopen("student_read.txt", "r");

    fscanf(read, "%lf", &student.student_id);
        fgets(linefeed_trash, 2, read); //reads past linefeed and stores it nowhere
        //first one need a read length of 2, and the second one need 1. Don't know why

    fgets(student.name, sizeof(student.name), read);
        student.name[strlen(student.name) -1] = 0;
            fgets(linefeed_trash, 1, read); //reads past linefeed and stores it nowhere

    fscanf(read, "%d", &student.age);

    fclose(read);

    struct_print(student);
};

void write_file(student_t student){

    FILE* write = fopen("student_write.txt", "w");

    fprintf(write, "%.0lf\n", student.student_id);
    fprintf(write, "%s\n", student.name);
    fprintf(write, "%d", student.age);

    fclose(write);
};

void print_menu(student_t student){
    printf("1. Read student information from file\n");
    printf("2. Write student information to file\n");
    printf("3. Exit\n");
    int choice = 2;
    scanf("%d", &choice);

    if(choice == 1){ //read
        read_file(student);
    } else if(choice == 2){ //write
        student = struct_input(student);
        write_file(student);
    } else if(choice == 3){ //exit
        exit;
    }
};



int main(){
    student_t student;
    print_menu(student);
}

