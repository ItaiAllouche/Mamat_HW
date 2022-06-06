#include <iostream>
#include <cstring>
#include "string.h"
#include "field.h"
#include "ip.h"

const int Byte1 = 1;
const int Byte2 = 2;
const int Byte3 = 3;
const int Byte4 = 4;
const int Mask = 5;
const int RuleLength = 6;
const int FULL = 32;

using namespace std;

Ip::Ip(String pattern) : Field(pattern), ip(0), mask(0){};

//recive full trimmed rule e.g  src-ip=122.0.0.0/8
bool Ip::set_value(String val){
    String *strings;
    size_t total = 0;
    const char* delimitors ="=/.";
    //spilt to src-ip,122,0,0,0,8
    val.split(delimitors, &strings, &total);
    if(total != RuleLength){
        delete[] strings;
        return false;
    }
    String trimmed_mask = strings[Mask].trim();
    int num_of_bites = trimmed_mask.to_integer();
    if(num_of_bites == FULL ){
        mask = 0xFFFFFFFF;
    }
    else{
        mask = ~((0xFFFFFFFF >> num_of_bites));
    }
    String trimmed1 = strings[Byte1].trim();
    String trimmed2 = strings[Byte2];
    String trimmed3 = strings[Byte3];
    String trimmed4 = strings[Byte4];
    ip = (((trimmed1.to_integer())<<24) | ((trimmed2.to_integer())<<16) | 
          ((trimmed3.to_integer())<<8) | ((trimmed4.to_integer())));
    delete[] strings;
    return true;
};


//recive full trimmed ip e.g 120.4.5.6
bool Ip::match_value(String value)const{
    String *strings;
    size_t zero = 0;
    const char* delimitors =".";
    //spilt to ,120,4,5,6
    value.split(delimitors, &strings, &zero);
    String trimmed1 = strings[0];
    String trimmed2 = strings[Byte1];
    String trimmed3 = strings[Byte2];
    String trimmed4 = strings[Byte3];

    int curr_ip = ((trimmed1.to_integer())<<24) | ((trimmed2.to_integer())<<16) | 
                   ((trimmed3.to_integer())<<8) | ((trimmed4.to_integer()));
    if((ip & mask) == (curr_ip & mask)){
        delete[] strings;
        return true;
    }
    delete[] strings;
    return false;
};
