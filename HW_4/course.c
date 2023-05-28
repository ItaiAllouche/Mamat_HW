#include <stdlib.h>
#include <stdio.h>
#include <linked-list.h>
#include <string.h>
#include <course.h>

#define EXISTS 1
#define NOT_EXISTS -1
#define SUCCESES 0
#define FAILURE -1

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
    strcpy(new_course->name_course,name);
    return new_course;
}

void course_destroy( struct course *course){
    free(course->name_course);
    free(course);
}

void* course_clone(void *elemnt){
    struct course *tmp=(struct course*)elemnt;
    struct course *out=malloc(sizeof(struct course));
    if(out == NULL){
        return NULL;
    }
    strcpy(out->name_course,tmp->name_course);
    (out->grade)=(tmp->grade);
    return out;
} 

   //searching the course by the name in the list of the courses
int course_get_course_by_name(struct list *list_courses ,const char *name){
    struct iterator *iterator=list_begin(list_courses);
    struct course *curr_course=list_get(iterator);               
    while(iterator !=NULL){
        if(strcm(name,curr_course->name_course)){
            return EXISTS;
            }
        iterator=list_next(iterator);
    }
    return NOT_EXISTS;
}
                                            

void course_print_list_courses(struct list *list_courses){
    for(struct iterator *iterator=list_end(list_courses);iterator!=NULL;iterator=list_prev(iterator)){
        struct course *curr_course=list_get(iterator);
        printf("%s %d,",curr_course->name_course,curr_course->grade);
    }
}


void  course_list_copy(struct list *list_dest,struct list *list_sourc){
    struct iterator *iterator_course_s=list_back(list_sourc);
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