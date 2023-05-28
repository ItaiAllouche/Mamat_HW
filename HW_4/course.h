#ifndef COURSE_H
#define COURSE_H
/* Defined elsewhere */
struct course;


/**
 * @return pointer to course 
 */
struct course* course_init(int grade, const char *name);

void course_destroy(struct course *course);

void* course_clone(void *element);

/**
 *@note the decription of each function is **above** the statment
 */

/**
 * @brief add course with grade and name to courses
 */
void course_add_course(int grade, const char* name, struct list *courses);

/**
 * @brief checking if course with name does exsist in courses(list)
 * @returns 1 if does exsits and -1 if doesnt **important!**
 */
int course_get_course_by_name(const char* name, struct list *courses)

/**
 * @brief copying the content (courses) in list_sourc to list_dest
 * */
void course_list_copy(struct list* list_dest, struct list *list_sourc)

/**
 * @brief printing courses(list)
 * */
void course_print_list_courses(struct list *courses)

float course_avg_courses(struct list* courses);

#endif

/** functions from itay- course.c:
 * course_add_course
 * course_get_course_by_name
 * course_list_copy
 * course_print_list_courses

