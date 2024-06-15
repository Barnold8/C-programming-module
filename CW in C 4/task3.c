#include <stdio.h>
#include <stdlib.h>

int isCSV(const char * filename){

    int x = 1;
    char c[3];
    while(x){

        if(*filename == '.'){x = 0;}
        filename++;

    }
    c[0] = *filename;
    filename++;
    c[1] = *filename;
    filename++;
    c[2] = *filename;
    if(c[0] == 'c' && c[1] == 's' && c[2]== 'v'){return 1;}
    
    return 0;
}

int correctFiles(const char* A, const char * B,const char *C){

    int x = 1;

    while(x){

        if(*A == '_'){x = 0;}
        
        A++;

    }x = 1;
    while(x){

        if(*B == '_'){x = 0;}
        
        B++;
    }
    x =1;
    while(x){

        if(*C == '_'){x = 0;}
    
        C++;
    }

    if(*A == 's' && *B=='a'&& *C == 'r'){
       
        return 1;
    }
  

    return 0;
}



int main(int argc, char** argv){

    FILE* f1, *f2,*f3;
    int* x;

    x = (int*)calloc(1,sizeof(int));

    if(argc != 4){
        fprintf(stderr,"You entered %d argument(s) where 4 were expected (including the program itself as an arg)\n",argc);
        return 1;

    }
    
    f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"r");
    f3 = fopen(argv[3],"w");


    if( f3 == NULL || f2 == NULL || f1 == NULL) {

        fprintf(stderr,"Error reading files\nExiting program.\n");
        return 1;

    }else if(!isCSV(argv[1]) || !isCSV(argv[2]) || !isCSV(argv[3])){

        fprintf(stderr,"Files entered are not type .csv\nExiting program.\n");
        return 1;
    }

    if(!correctFiles(argv[1],argv[2],argv[3])){

        fprintf(stderr,"The students file was expected first and the activity file was expected second. However, you havent provided this.\n");
        return 1;
    }

    free(x);
    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}