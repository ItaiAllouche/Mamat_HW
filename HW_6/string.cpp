#include <iostream>
#include <cstring>
#include "string.h"

using namespace std;
const int EQUAL = 0;
const int ERROR = 0;

char* allocate_and_copy(const char *str){
    size_t len = strlen(str);
    char *returned  = new char[len+1];
    strcpy(returned, str);
    return returned;
}


String::String(): data(nullptr), length(0){}

String::String(const String &str) :
    data(allocate_and_copy(str.data)),
    length(str.length){};

String::String(const char *str) : data(allocate_and_copy(str)), length(strlen(str)+1){};////+1?""

String::~String(){
    delete[] data; 
};

String& String::operator=(const String &rhs){
    if(this == &rhs){
        return *this;
    };
    
    delete[] data;
    length = rhs.length;
    data = new char[length+1];
    strcpy(data,rhs.data);
    return *this;
};

String& String::operator=(const char *str){
    delete[] data;
    length = strlen(str);
    data = new char[length+1];
    strcpy(data,str);
    
    return *this;
};

bool String::equals(const String &rhs) const{
    if(length == rhs.length && strcmp(data,rhs.data) == EQUAL){
        return true;
    }
    return false;
};

bool String::equals(const char *rhs) const{
        if(length == strlen(rhs) && strcmp(data,rhs) == EQUAL){
        return true;
    }
    return false; 
};

//checking if current element is a delimiter
bool find_delimiter(char element, const char* delimiters){
    int i=0;
    while(delimiters[i] !='\0'){
        if(element == delimiters[i]){
            return true;
        }
        i++;
    }
    return false;
};


void String::split(const char *delimiters, String **output, size_t *size) const{
    size_t start=0,end=1;
    size_t array_size=0,temp_length=(length-1);
    //compute array_size
    //ignoring delimiters at the begininng of the string
      while(find_delimiter(data[start],delimiters)){
            start++;
            end=start;
        }
        //if all data is a delimiter
         if(data[start] == '\0'){
            *output = nullptr;
            return;
        }

        //ignoring delimiters at the end of the string
        while(find_delimiter(data[temp_length],delimiters)){
            temp_length--;
        }

        while(end <= temp_length){ 
            if(find_delimiter(data[start],delimiters)){
            start++;
            end=start;
            }

            if(end != start && find_delimiter(data[end],delimiters)){
                array_size++;
                start=end+1;
            };
            end++;
        }

        //final sub string
        array_size++;

        //finish compute array_size 
        
        if(output == nullptr || array_size == 0){
            *(size) = array_size;
            return;
        } 
        
 
        *output = new String[array_size];
        char *temp_data = new char[length+1];
        strcpy(temp_data,data);
        char *token = strtok(temp_data, delimiters);
        int i=0;
        while(token != NULL){
            (*output)[i] = String(token);
            token = strtok(NULL, delimiters);
            i++;
        }
         *(size) = array_size; 
         delete[] temp_data;
         return;           
};


int String::to_integer() const{
    return atoi(data);
};

String String::trim() const{
    size_t left=0, right = length-1;
    while(data[left] == ' ' && left<=length){
        left++;
    }
    while(data[right] == ' ' && right >=0){
        right--;
    }
    
    char  *trimmed = new char[right-left+2];
    strncpy(trimmed, data+left, right-left+1);
    String trimmed_string(trimmed);
    delete[] trimmed;
    return trimmed_string;
}




