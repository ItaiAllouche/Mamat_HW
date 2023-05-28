#ifndef STUDENT_H
#define STUDENT_H
/* Defined elsewhere */
struct student;

/**
 * @brief Initializes the "student" data-structure, with name, id and pointer to list
 * @returns A pointer to the data-structure, or NULL in case of an error
 */
struct student* student_init(int id, const char *name);

void* student_clone(void *element);

/**
 * @brief Destroys "student", de-allocate all memory!
 */
void student_destroy(struct student *student);


/**
 * @brief Prints the courses of the student in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 *  @note The courses should be printed according to the order 
 * in which they were inserted into "student"
 */
void student_print_student(struct student *student);



/**
 * @brief calc the avarage grades of student
 * @returns The average, or -1 on error
 * @note  If the student has no courses, the average is 0.
 */



#endif