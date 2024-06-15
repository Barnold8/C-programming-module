#include <stdio.h>
#include <string.h>

long int factorial(long int number){
    int i;
    long int n = number;
    long int temp = 1;

    for(i = 1; i <= n; i++){

        temp = temp * i;

    }

    return temp;

}



long int MyPow(const long int num,long int exp){

    long int n = num;
    int i;

    if(exp == 0){
        return 1;
    }


    for(i = exp-1; i > 0; i--){

        n *= num;

    }
    return n;
}

int ascINT(const char * c){
   
    return (int)*c - 48;

}

int strINT(const char* s){

    int num = 0;
    int i;

    /* NEED ERROR CHECKING HERE */

    for(i = 0; i < strlen(s); i++){

        if((int)s[i]< 48 || (int)s[i] > 57){

            return __INT_MAX__;

        }

    }

    if(strlen(s) == 1){
        num += ascINT(&s[0]);
        
    }
    else{

        num += ascINT(&s[1]);
        num += ascINT(&s[0]) * 10;

    }

    return num;
}

void print_Pascal(const int lines){
    
    int i, j;

    if(lines == 1){

        printf("%ld\n", factorial(lines));

    }
    else{
            for(i = lines-1; i >= 0; i--){

            for(j = 0; j <(i+1); j++ ){

                printf("%ld ", factorial(i) / (factorial(j)*factorial(i-j)));

            }
        printf("\n");
    }
}

    
    
}

int main(int argc, char** argv ){

    int lines;

    if(argc != 2){

        printf("This program needs 1 arguments passed into it before execution. You passed in %d arguments.\n\nExiting program...\n",argc - 1);
        return 1;
    }

    lines = strINT(argv[1]);
    
    if(lines > 20 || lines < 1){

        printf("Your argument was invalid. A number between 1-20 was expected. However, you gave %d\n", lines);
        return 1;
    }

    print_Pascal(lines);


    return 0;

}