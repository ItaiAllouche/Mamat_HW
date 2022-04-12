#!/bin/bash
read num_of_course

num_of_arg=$(echo $num_of_course | wc -w)
if [[ $num_of_arg > 1 ]]; then 
echo "Wrong number of arguments" >&2
exit 1
fi

file_name="$num_of_course".txt
file_is_exist=$( ls | grep  $file_name | wc -w)
if [[ $file_is_exist = 0 ]]; then
echo "Course not found" >&2
exit 1
fi

dir_name="$num_of_course"_stat
dir_is_exist=$( ls | grep $dir_name | wc -w)
if [[ $dir_is_exist = 1 ]]; then
rm -r "$num_of_course"_stat
fi

mkdir "$num_of_course"_stat

awk '{print $2}' 044101.txt > grades1.txt
cat grades1.txt | sed 1d > grades.txt
rm grades1.txt
mv grades.txt "$num_of_course"_stat
path=./"$num_of_course"_stat/grades.txt

gcc -g -Wall calc_statistics.c -o prog
./prog $path > course_statistics.txt
cat course_statistics.txt
mv course_statistics.txt "$num_of_course"_stat














