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
        struct iterator *iterator=list_end(list_courses);
        struct course* curr_course=list_get(iterator);
        if(iterator != NULL){
            printf(" %s %d",curr_course->name_course,curr_course->grade);
            iterator=list_prev(iterator);
            curr_course=list_get(iterator);
        }
        
        while(iterator != NULL){
            printf(", %s %d",curr_course->name_course,curr_course->grade);
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
    if(list_push_front(list,new_course) != SUCCESES){
        return FAILURE;
    }
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
    return (float)((float)tot_sum/num_of_courses);
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
    printf("\n");
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
 * returns pointer to student or null if doesent exists
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
    if(list_push_front(grades->student_list,curr_student) != SUCCESES){
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
    return SUCCESES;  
}

int grades_print_all(struct grades *grades){
    if(grades == NULL){
        return FAILURE;
    }
    struct iterator *iterator = list_end(grades->student_list);
    struct student *curr_student = list_get(iterator);
    while(iterator != NULL){
        student_print_student(curr_student);
        iterator = list_prev(iterator);
        curr_student = list_get(iterator);
    }
    return SUCCESES;
}
//end grade modole









