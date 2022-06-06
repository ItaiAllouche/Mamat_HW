#include <iostream>
#include <cstring>
#include "string.h"
#include "port.h"
#include "field.h"

const int TOTAL_STRIGNS = 4;

using namespace std;

Port::Port(String pattern) : Field(pattern), max(0), min(0){};


//recive full trimed rule e.g dest-port=   23-25
bool Port::set_value(String val){
    String *ranges;
    size_t total = 0;
    const char* delimitors ="=-";
    //spilt to dest,port,23,25
    val.split(delimitors, &ranges, &total);
    if(total != TOTAL_STRIGNS){
        delete[] ranges;
        return false;
    }

    String trimmed_min = ranges[2].trim();
    String trimmed_max = ranges[3].trim();
    this->min=trimmed_min.to_integer();
    this->max=trimmed_max.to_integer();
    if(min == 0 || max == 0){
       delete[] ranges;
        return false;
    }
    delete[] ranges;
    return true;
};


//recive full trimed port e.g  23
bool Port::match_value(String value)const{
    int curr_port= value.to_integer();
    if(curr_port >=min && curr_port<=max){
        return true;
    }
    return false;
};

