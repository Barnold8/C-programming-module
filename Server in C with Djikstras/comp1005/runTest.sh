clear
gcc test.c linked_list.c graph.c -g -ansi -Wall --pedantic-errors -o test
echo "###################################-- Options --###################################"
echo " "

echo "1. run w/o mem check"
echo "2. run w/  mem check"


read input

echo " "
echo " "


if [[ $input == 1 ]]; then
        ./test
elif [[ $input == 2 ]]; then
        valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./test
else    
        echo "Incorrect input"
fi



#make clean task1_test_run

#echo "------------------------------------------------------------------------------------------------------------------------------------------------------------"

#make task1_test_memcheck
