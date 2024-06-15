#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void defineMiddle(int* x, const int width){

    if(width % 2 == 0){
        x[(width/2)+1] = 1;

    }else{
        x[width/2] = 1;
    }
}

void setup_process(int** x, const int elems){
    *x = (int *) calloc(elems,sizeof(int)); 
}

void print_arr(int* x, const int width){

    int i;
    
    for(i = 0; i < width; i++){
        
        if(x[i] == 1){
            printf("*");
        }
/*         else if(x[i] == -1){
            printf("?");
        } */
        else{printf(" ");}
    }
    printf("\n");

}

void print_bits(int* x, const int width){ /* This function works as intended */

    int i;
    for(i = 0; i < width; i++){
        printf("%d ",x[i]);
    }
    printf("\n");


}

int validNum(char * x,const int num,char* example){

    int i;

    for(i = 0; i < num; i++){

        if(((int) x[i]) < 48 || ((int) x[i]) > 57){

            printf("The arguments of this program are invalid. You gave %s when numbers were expected. This program uses base 10 numbers for its processing. Heres an example of a correct run of this program.\n%s",x,example);
            return 1;
        }

    }


    return 0;

}


void IntToByte(int x, int* arr){ /* THis functions works as intended */

    int byte[8] = {128,64,32,16,8,4,2,1};
    int index = 0;
    while (x != 0)
    {   
        if(x >= byte[index]){

            x -= byte[index];
            arr[index] = 1; 
        
        }
        else{

            arr[index] = 0;

        }
        index++;

    }


}

int ruleset(const int left, const int mid, const int right, int* byte){ 
 
/*     int sub_rules[8][3] = {

        {1,1,1},
        {1,1,0},
        {1,0,1},
        {1,0,0},
        {0,1,1},
        {0,1,0}, 
        {0,0,1},
        {0,0,0},

    }; */

    /* Something aint right here chief. Go to https://www.youtube.com/watch?v=W1zKu3fDQR8&t=534s */
    
    if(left == 1 && mid == 1 && right == 1 ){return byte[0];}
    if(left == 1 && mid == 1 && right == 0 ){return byte[1];}
    if(left == 1 && mid == 0 && right == 1 ){return byte[2];}
    if(left == 1 && mid == 0 && right == 0 ){return byte[3];}
    if(left == 0 && mid == 1 && right == 1 ){return byte[4];}
    if(left == 0 && mid == 1 && right == 0 ){return byte[5];}
    if(left == 0 && mid == 0 && right == 1 ){return byte[6];}
    if(left == 0 && mid == 0 && right == 0 ){return byte[7];}
   


    return -55;
}


void gen_process(int * CG,const int elems, int* byte){ /* Process next generation based on current generation then overwrite current gen with next gen */
    
    /* data setup */
    int i, back,forward;
    int* nextGen;
    nextGen = (int *) calloc(elems,sizeof(int)); 

    /* ------- */

    /* Configure what the neighbouring cells are */
    for(i = 0; i < elems-1; i++){
        forward = i+1;
        
        if(i == 0){
            back = elems-1;

        }else if(i == elems){
            forward = 0;}
        else{

            back = i-1;
    
            forward = i+1;
        }
        
          /*  printf("b: %d m: %d r: %d\n",back, i,forward); */
/*         printf("b: %d m: %d r: %d\n",CG[back], CG[i],CG[forward]); */
        nextGen[i] = ruleset(CG[back],CG[i],CG[forward],byte);
    }
    
    for(i = 0; i < elems; i++){
        CG[i] = nextGen[i];    
    }
 
    free(nextGen);
}


int main(int argc, char ** argv){


    /* Variable assignment */
    int* current_gen, *byte;
    int gens,wolfram,elems = 0; 
    char* example = "Here's an example of running this program correctly:\n\n\t ./task1 50 50 90\n\n";
    /*---------------------*/

    /* argument sanity checking */
    if(argc != 4){
        printf("EXPECTED: ./task1 <arg1> <arg2> <arg3>, all args have to have data! You filled in %d of these args.\n%s",argc-1,example); 
        return 1;}

    if(validNum(argv[1],strlen(argv[1]),example)){return 1;}
    if(validNum(argv[2],strlen(argv[2]),example)){return 1;}
    if(validNum(argv[3],strlen(argv[3]),example)){return 1;}


    /*---------------------*/  
    
    
    /* continue assigning vars */
    elems = strtol(argv[1],NULL,10) ;
    gens = strtol(argv[2],NULL,10);
    wolfram = strtol(argv[3],NULL,10);
    /* --------------------- */

    
    /* Sanity checking */
    if(elems <= 0){
        printf("The elements section of the program is invalid. You gave: %d, where any number greater than 0 is expected.\n%s",elems,example);
        return 1;} 

    if(gens <= 0){
        printf("The generation section of this program is invalid. You have %d, where any number greater than 0 is expected.\n%s",elems,example);
        return 1;

    }
    if(wolfram < 0 || wolfram > 255){
        
        printf("The wolfram section of this program is invalid. You gave %d where a number between 0-255 (including 0 and 255 as valid numbers) is expected.\n%s",wolfram,example);
        return 1;}
    /* ------- */


    /* pre generation setup */
    setup_process(&current_gen,elems);

    setup_process(&byte,8);

    IntToByte(wolfram,byte);
    defineMiddle(current_gen,elems); 
    /* -------------------- */
     
    /* Generation code */
   

     print_arr(current_gen,elems);
    while(gens != -1){
        gen_process(current_gen,elems,byte);
        print_arr(current_gen,elems); 
        gens--;
    }
    

    /* ---------------- */

    /* Free memory from the heap */
    free(current_gen);
    free(byte);
    /* ------ */

    return 0;
}





/* code graveyard */

/*int AsciiToInt(char a){
    
    if( ((int) a) < 48 || ((int) a) > 57){exit(EXIT_FAILURE);}
    return (int)a - 48;}

int StrToInt(char * a){

    int sum,count,i;
    sum = count = 0;
    
    for(i = strlen(a)-1; i >=0; i--){
        
        sum += AsciiToInt(a[i]) * power(10,count);
        count++; 

    }

    return sum;

int power(int number, int exponent){

    int n = 1;

     while(exponent != 0){
         exponent--;
         n *= number;
     }
   
     return n;
}


}*/