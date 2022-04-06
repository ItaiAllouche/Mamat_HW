#!/bin/bash
function word_counter(){
    wget -q -O- $1 >file.txt
    Benn_appear=$(grep -c Bennett file.txt)
    Net_appear=$(grep -c Netanyahu file.txt)
    if [[ $Benn_appear == 0 && $Net_appear == 0 ]];
    then echo ',-'
    else
    echo -n ", Netanyahu, "$Net_appear | tr '\n' ' '
    echo -n ", Bennett, "$Benn_appear 
    echo 
    fi   
}
 wget  https://www.ynetnews.com/category/3082 
 grep -E -o "https:\/\/www.ynetnews.com\/article\/+[a-z,0-9,A-Z]+" 3082 | uniq | tee list_of_links.txt | wc -l >results.csv
 (while read line; do echo -n $line && (word_counter $line) ; done < list_of_links.txt) >>results.csv
 
 
