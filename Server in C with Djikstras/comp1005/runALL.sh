clear
echo "###################################-- Options --###################################"

echo " "

echo "1. run w/o mem check"
echo "2. run w/  mem check"

read input

if [[ $input == 1 ]]; then
        make clean task1_test_run
elif [[ $input == 2 ]]; then
        make task1_test_memcheck
else    
        echo "Incorrect input"
fi



#make clean task1_test_run

#echo "------------------------------------------------------------------------------------------------------------------------------------------------------------"

#make task1_test_memcheck
