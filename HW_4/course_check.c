#include <stdlib.h>
#include <stdio.h>
#include "grades.h"
#include "linked-list.h"
#include <string.h>

#define EXISTS 1
#define NOT_EXISTS -1
#define SUCCESES 0
#define FAILURE -1
#define MIN_GRADE 1
#define MAX_GRADE 100


struct course {
   const char *name_course;
    int grade;
};

struct course* course_init(int grade,const char *name){
    struct course *new_course=malloc(sizeof(struct course)+1);
    if(new_course==NULL){
        return NULL;
    } 
    new_course->grade=grade;
    new_course->name_course=malloc(strlen(name)+1);
    strcpy((char*)new_course->name_course,name);
    return new_course;
}

void course_destroy( struct course *course){
    free((char*)course->name_course);
    free(course);
}

int course_clone(void *elemnt, void **output){
    struct course *sourc=(struct course*)elemnt;
    struct course *target=malloc(sizeof(struct course));
    if(target == NULL){
        return FAILURE; 
    }
    target->grade = sourc->grade;
    target->name_course=malloc(strlen(sourc->name_course)+1);
    strcpy((char*)(target->name_course),(sourc->name_course));
    *output=target;
    return SUCCESES;
} 

   //searching the course by the name in the list of the courses
int course_get_course_by_name(struct list *list_courses ,const char *name){
    struct iterator *iterator=list_begin(list_courses);
    struct course *curr_course=list_get(iterator);               
    while(iterator !=NULL){
        if(strcmp(name,curr_course->name_course)==0){
            return EXISTS;
            }
        iterator=list_next(iterator);
    }
    return NOT_EXISTS;
}
                                            

void course_print_list_courses(struct list *list_courses){

    /*for(struct iterator *iterator=list_end(list_courses);iterator!=NULL;iterator=list_prev(iterator)){
        struct course *curr_course=list_get(iterator);
        printf("%s %d,",curr_course->name_course,curr_course->grade);*/
        struct iterator *iterator=list_end(list_courses);
        struct course* curr_course=list_get(iterator);
        printf(" %s %d",curr_course->name_course,curr_course->grade);
        iterator=list_prev(iterator);
        curr_course=list_get(iterator);
        while(iterator != NULL){
            printf(" ,%s %d",curr_course->name_course,curr_course->grade);
            iterator=list_prev(iterator);
            curr_course=list_get(iterator);
        }

    }



void  course_list_copy(struct list *list_dest,struct list *list_sourc){
    struct iterator *iterator_course_s=list_end(list_sourc);
    while(iterator_course_s!=NULL){
        list_push_front(list_dest,list_get(iterator_course_s));
    
        iterator_course_s=list_prev(iterator_course_s);
    } 
}



int course_add_course(int grade,const char *name,struct list *list){
    struct course *new_course=course_init(grade,name);
    if(new_course == NULL){
        return FAILURE;
    }
    list_push_front(list,new_course);
    course_destroy(new_course);
    return SUCCESES;    
}

float course_avg_courses(struct list* courses){
    int tot_sum=0;
    size_t num_of_courses=list_size(courses);
    struct iterator *iterator=list_begin(courses);
    //if the list is empty
    if(iterator==NULL){
        return 0;
    }
    struct course *curr_course=list_get(iterator);
    while(iterator!=NULL){
        tot_sum+=curr_course->grade;
        iterator=list_next(iterator);
        curr_course=list_get(iterator);
    }
    return (float)(tot_sum/num_of_courses);
}
//
//student modole
struct student {
    int id;
    char *name;
    struct list *courses;
};

struct student* student_init(int id, const char *name){
    struct student *curr_student = malloc(sizeof(struct student));
     if(curr_student == NULL){
        return NULL;
    }
    char* str = malloc(sizeof(char)*(strlen(name)+1));
    if(str == NULL){
        return NULL;
    }
    strcpy(str,name);
    curr_student->id = id;
    curr_student->name = str;
    curr_student->courses = list_init((void*)course_clone,(void*)course_destroy);
    return curr_student;
}


int student_clone(void *element, void** output){
    struct student *str= (struct student*)element;
    struct student *out = malloc(sizeof(struct student));
    if(out == NULL){
        return FAILURE;
    }
    out=student_init(str->id,str->name);

    /*out->courses=list_init((void*)course_clone,(void*)course_destroy);
    out->name=malloc(strlen(str->name)+1);
    strcpy(out->name, str->name);
    out->id=str->id;*/
    course_list_copy(out->courses, str->courses);
    *output=out;
    return SUCCESES;
}

void student_destroy(struct student *student){
    free(student->name);
    list_destroy(student->courses);
    free(student); 
} 

void student_print_student(struct student *student){
    printf("%s %d:",student->name,student->id);
    course_print_list_courses(student->courses);
}
//

//start grade modole
struct grades {
    struct list *student_list;
};

struct grades* grades_init(){
    struct grades *new_grades = malloc(sizeof(struct grades));
    new_grades->student_list = list_init((void*)student_clone,(void*)student_destroy);
   return new_grades;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades->student_list);
    free(grades);
}

/** find student by id
 * returns pointer to student or null if doesent exsits
 */
struct student* grades_get_student_by_id(struct grades *grades, int id){
    struct iterator *iterator = list_begin(grades->student_list);
    if(iterator == NULL){
        return NULL;
    }

    struct student *curr_student = list_get(iterator);
    while(iterator != NULL){
        if((curr_student->id) == id){
            return curr_student;
        }
        iterator = list_next(iterator);
        curr_student = list_get(iterator);
    }
    return NULL;
} 


int grades_add_student(struct grades *grades, const char *name, int id){
    //checking if the student is already exsist
    if(grades_get_student_by_id(grades,id) != NULL || grades == NULL){
        return FAILURE;
    }
    struct student *curr_student = student_init(id,name);
    if(list_push_front(grades->student_list,curr_student) != 0){
        return FAILURE;
    }
    student_destroy(curr_student);
    return SUCCESES;
}


int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    struct student* curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL 
                            || grade < MIN_GRADE || grade > MAX_GRADE){
        return FAILURE;
     }
     //checking if the course alreaday exsits
    if(course_get_course_by_name(curr_student->courses,name) == NOT_EXISTS){
        return course_add_course(grade, name, curr_student->courses);
    }
    return FAILURE;
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    struct student *curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL){
        *out = NULL;
        return FAILURE;
    }
    out = malloc((strlen(curr_student->name)+1));
    strcpy(*out,curr_student->name);
    return course_avg_courses(curr_student->courses);

}


int grades_print_student(struct grades *grades, int id){
    struct student *curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL){                       
        return FAILURE;
    }
    student_print_student(curr_student);
    return SUCCESES;  
}

int grades_print_all(struct grades *grades){
    struct iterator *iterator = list_end(grades->student_list);
    if(iterator == NULL){
        return FAILURE;
    }
    struct student *curr_student = list_get(iterator);
    while(iterator != NULL){
        student_print_student(curr_student);
        iterator = list_prev(iterator);
        curr_student = list_get(iterator);
    }
    return SUCCESES;
}
//


int main(){
    int grade=91;
    int id=123;
    const char* course_name1=NULL;
    const char* course_name2=NULL;
    const char* course_name3=NULL;
     const char* student_name=NULL;
    char course_m1[]="mmt";
    char course_m2[]="hfdgh";
    char course_m3[]="gfh";
    char stu_m[]="itai";
    student_name=stu_m;
    course_name1=course_m1;
    course_name2=course_m2;
    course_name3=course_m3;
    struct grades* my_grade=grades_init();
    grades_add_student(my_grade,student_name,id);
    grades_add_grade(my_grade,course_name1,id,grade);
    grades_add_grade(my_grade,course_name2,id,93);
    grades_add_grade(my_grade,course_name3,id,95);
    grades_print_student(my_grade,id);
    char** out=NULL;
    float av=grades_calc_avg(my_grade,id,out);
    printf("%f",av);


    return 0;
}

/*
#define SUCCESS 0
#define FAILURE -1
#define MAX_GRADE 100
#define MIN_GRADE 0
#define EXISTS 1
#define NOT_EXISTS -1

//start course modole
struct course {
   const char *name_course;
    int grade;
};

struct course* course_init(int grade,const char *name){
    struct course *new_course=malloc(sizeof(struct course)+1);
    if(new_course==NULL){
        return NULL;
    } 
    new_course->grade=grade;
    new_course->name_course=malloc(strlen(name)+1);
    strcpy((char*)new_course->name_course,name);//
    /*strcpy(new_course->name_course,name);
    return new_course;
}

void course_destroy( struct course *course){
    free((char*)course->name_course);
    /*free(course->name_course);
    free(course);
}

void* course_clone(void *element){
    struct course *tmp=(struct course*)element;
    struct course *out=malloc(sizeof(struct course));
    if(out == NULL){//* before out was removed
        return NULL;
    }
    strcpy((char*)out->name_course,tmp->name_course);
    (out->grade)=(tmp->grade);
    return out;
} 

   //searching the course by the name in the list of the courses
int course_get_course_by_name(struct list *list_courses ,const char *name){
    struct iterator *iterator=list_begin(list_courses);
    struct course *curr_course=list_get(iterator);               
    while(iterator !=NULL){
        if(strcmp(name,curr_course->name_course)){
            return EXISTS;
            }
        iterator=list_next(iterator);
    }
    return NOT_EXISTS;
}
                                            

void course_print_list_courses(struct list *list_courses){
    for(struct iterator *iterator=list_end(list_courses);iterator!=NULL;
                                            iterator=list_prev(iterator)){
        struct course *curr_course=list_get(iterator);
        printf("%s %d,",curr_course->name_course,curr_course->grade);
    }
}


void course_list_copy(struct list *list_dest,struct list *list_sourc){
    struct iterator *iterator_course_s=list_end(list_sourc);
    while(iterator_course_s!=NULL){
        list_push_front(list_dest,list_get(iterator_course_s));
        iterator_course_s=list_prev(iterator_course_s);
    } 
}



int course_add_course(int grade,const char *name,struct list *list){
    struct course *new_course=course_init(grade,name);
    if(new_course == NULL){
        return FAILURE;
    }
    list_push_front(list,new_course);
    course_destroy(new_course);
    return SUCCESS;    
}

float course_avg_courses(struct list* courses){
    int tot_sum=0;
    size_t num_of_courses=list_size(courses);
    struct iterator *iterator=list_begin(courses);
    //if the list is empty
    if(iterator==NULL){
        return 0;
    }
    struct course *curr_course=list_get(iterator);
    while(iterator!=NULL){
        tot_sum+=curr_course->grade;
        iterator=list_next(iterator);
        curr_course=list_get(iterator);
    }
    return (float)(tot_sum/num_of_courses);
}
//end course modole



//start student modole
struct student {
    int id;
    char *name;
    struct list *courses;
};

struct student* student_init(int id, const char *name){
    struct student *curr_student = malloc(sizeof(struct student));
     if(curr_student == NULL){
        return NULL;
    }
    char* str = malloc(sizeof(char)*(strlen(name)+1));
    if(str == NULL){
        return NULL;
    }
    strcpy(str,name);
    curr_student->id = id;
    curr_student->name = str;
    curr_student->courses = list_init((void*)course_clone,(void*)course_destroy);
    return curr_student;
}


void* student_clone(void *element){
    struct student *str= (struct student*)element;
    struct student *out = malloc(sizeof(struct student));
    strcpy(out->name, str->name);
    out->id=str->id;
    course_list_copy(out->courses, str->courses);
    return out;
}

void student_destroy(struct student *student){
    free(student->name);
    list_destroy(student->courses);
    free(student); 
} 

void student_print_student(struct student *student){
    printf("%s %d: ",student->name,student->id);
    course_print_list_courses(student->courses);
}

//end student modole


//start grade modole
struct grades {
    struct list *student_list;
};

struct grades* grades_init(){
    struct grades *new_grades = malloc(sizeof(struct grades));
    new_grades->student_list = list_init((void*)student_clone,(void*)student_destroy);
   return new_grades;
}

void grades_destroy(struct grades *grades){
    list_destroy(grades->student_list);
    free(grades);
}

/** find student by id
 * returns pointer to student or null if doesent exsits
 
struct student* grades_get_student_by_id(struct grades *grades, int id){
    struct iterator *iterator = list_begin(grades->student_list);
    if(iterator == NULL){
        return NULL;
    }

    struct student *curr_student = list_get(iterator);
    while(iterator != NULL){
        if((curr_student->id) == id){
            return curr_student;
        }
        iterator = list_next(iterator);
        curr_student = list_get(iterator);
    }
    return NULL;
} 


int grades_add_student(struct grades *grades, const char *name, int id){
    //checking if the student is already exsist
    if(grades_get_student_by_id(grades,id) != NULL || grades == NULL){
        return FAILURE;
    }
    struct student *curr_student = student_init(id,name);
    if(list_push_front(grades->student_list,curr_student) != 0){
        return FAILURE;
    }
    student_destroy(curr_student);
    return SUCCESS;
}


int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
    struct student* curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL 
                            || grade < MIN_GRADE || grade > MAX_GRADE){
        return FAILURE;
     }
     //checking if the course alreaday exsits
    if(course_get_course_by_name(curr_student->courses,name)){
        return FAILURE;
    }
    return course_add_course(grade, name, curr_student->courses);
}

float grades_calc_avg(struct grades *grades, int id, char **out){
    struct student *curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL){
        *out = NULL;
        return FAILURE;
    }
    *out = malloc(sizeof(char)*(strlen(curr_student->name)+1));
    strcpy(*out,curr_student->name);
    return course_avg_courses(curr_student->courses);

}


int grades_print_student(struct grades *grades, int id){
    struct student *curr_student = grades_get_student_by_id(grades,id);
    if(curr_student == NULL || grades == NULL){                       
        return FAILURE;
    }
    student_print_student(curr_student);
    return SUCCESS;  
}

int grades_print_all(struct grades *grades){
    struct iterator *iterator = list_end(grades->student_list);
    if(iterator == NULL){
        return FAILURE;
    }
    struct student *curr_student = list_get(iterator);
    while(iterator != NULL){
        student_print_student(curr_student);
        iterator = list_prev(iterator);
        curr_student = list_get(iterator);
    }
    return SUCCESS;
    */

