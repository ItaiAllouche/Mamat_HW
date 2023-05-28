#include <stdlib.h>
#include <stdio.h>
#include <grades.h>
#include <linked-list.h>
#include <student.h>
#include <course.h>
#include <string.h>


struct student {
    int id;
    char *name;
    struct list *courses;
};

struct student* student_init(int id, const char *name){
    struct student *curr_student = malloc(sizeof(struct student));
    char* str = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(str,name);
    curr_student->id = id;
    curr_student->name = str;
    curr_student->courses = list_init(course_clone,course_destroy);
}


void* student_clone(void *element){
    struct student *str= (struct student*)element;
    struct student *out = malloc(sizeof(struct student));
    strcpy(out->name, str->name);
    out->id=str->id;
    course_list_copy(out->courses, str->courses)
    return out;
}

void* student_destroy(*struct student *student){
    free(student->name);
    list_destroy(student->courses);
    free(student); 
} 

void student_print_student(struct student *student){
    printf("%s %d: ",student->name,student->id);
    course_print_list_courses(student->courses);
}

