#include <iostream>
#include "string.h"
#include "field.h"

using namespace std;

    Field::Field(String pattern) : pattern(pattern) {};

    Field::~Field(){
         
         };
       
    

//split packet to 8 sub-field,s finding field with pattern and call match value with field+1
    bool Field::match(String packet){
        String *fields;
        size_t total = 0;
         const char* delimitors = ",=";
         packet.split(delimitors, &fields, &total);
         for(size_t i=0; i<total; i+=2){
             if(pattern.equals(fields[i].trim())){
                 if(match_value(fields[i+1].trim())){
                    delete[] fields;
                    return true;
                 }
                 delete[] fields;
                 return false;
             }               
        }
         delete[] fields;
         return false;
     };
     
     
