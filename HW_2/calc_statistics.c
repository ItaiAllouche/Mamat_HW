#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_TO_PASS 55
#define NORMALIZED 100
#define COLUMNS 10
#define EMPTY -1

int main (int argc, char *argv[]){
 
    FILE *fp2;  

    fp2 = fopen(argv[1], "r");
    if (fp2==NULL){
        return 0;
    }
    
    int num_of_students=0;
    int sum_of_grades=0;
    int curr_grade;
    int min_grade=EMPTY;
    int max_grade=EMPTY;
    int num_of_pass=0;
    int hist [COLUMNS][COLUMNS]={{0}};

    while((fscanf(fp2, "%d", &curr_grade))>0){
        num_of_students++;
        sum_of_grades+=curr_grade;
        if(curr_grade>max_grade ||max_grade==EMPTY){
            max_grade=curr_grade;
        }
        if(curr_grade<min_grade ||min_grade==EMPTY){
            min_grade=curr_grade;
        }
        if(curr_grade>=MIN_TO_PASS){
            num_of_pass++;
        }
        hist[(curr_grade-1)/10][(curr_grade-1)%10]++;
    }

    float avg=((float)sum_of_grades/num_of_students);
    float pass_rate=((float)num_of_pass/num_of_students)*NORMALIZED;
    int median, counter=0;

    for(int i=0; i<COLUMNS; i++){
        for(int j=0; j<COLUMNS; j++){
            if (hist[i][j]!=0){
                int temp=hist[i][j];
                while(temp){
                    counter++;
                    if(counter==(num_of_students+1)/2){
                         median=(i)*COLUMNS+(j+1);
                         break;
                    }
                    temp--;
                }     
            }  
        }
    }
    
    printf("num of students = %d\n",num_of_students);
    printf("avg = %.3lf\n",avg);
    printf("the median is - %d\n",median);
    printf("max garde = %d, min grade = %d\n",max_grade,min_grade);
    printf("pass rate = %.2lf%c\n",pass_rate,'%');

    for(int i=0; i<COLUMNS; i++){
        for(int j=0; j<COLUMNS; j++){
            printf("%d ",hist[i][j]);
        }
        printf("\n");
    }
    fclose(fp2);
    return 0;   
}
