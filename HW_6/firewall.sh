#!/bin/bash 
cat $1 | sed '/^#/d'| grep "\S" | sed 's/#.*//' > rules.txt                  
touch packets.5txt 
while read -r packet; do
    echo $packet >> packets_with_space.txt  
done

 cat packets_with_space.txt | sed 's/ //g' > packets.txt

while read -r rule; do
    echo $rule > valid_rule.txt 
    
    curr_single_rule1=$(awk -F, '{print $1}' valid_rule.txt)  
    cat packets.txt | ./firewall.exe $curr_single_rule1 > packets.1txt
    curr_single_rule2=$(awk -F, '{print $2}' valid_rule.txt) 
    cat packets.1txt | ./firewall.exe $curr_single_rule2 > packets.2txt 
    curr_single_rule3=$(awk -F, '{print $3}' valid_rule.txt) 
    cat packets.2txt | ./firewall.exe $curr_single_rule3 > packets.3txt 
    curr_single_rule4=$(awk -F, '{print $4}' valid_rule.txt) 
    cat packets.3txt | ./firewall.exe $curr_single_rule4 > packets.4txt 

    cat packets.4txt >> packets.5txt
    
done < rules.txt
cat packets.5txt | sort | uniq | grep "\S" 
rm -r *txt



 