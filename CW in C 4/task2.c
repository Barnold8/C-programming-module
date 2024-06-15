#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Student{

    int grade;
    int ID;
    char fname[20];
    char lname[20];

};


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

int correctFiles(const char* A, const char * B){

    int x = 1;

    while(x){

        if(*A == '_'){x = 0;}
        A++;

    }x = 1;
    while(x){

        if(*B == '_'){x = 0;}
        B++;
    }
    if(*A == 's' && *B=='a'){
       
        return 1;
    }
    return 0;
}

int makeArraySize(FILE* F){

    char ch = ' ' ;
    int arraySize = 0;
   
      rewind(F);
    /* Get the length of the array to allocate */

    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!= EOF){
     
        if(ch == 10){                           
        
            arraySize++;

        }
   
    }
    /* -------------------------------------- */


    return arraySize;
}

void setIDs(FILE* F,struct Student* S){

    char ch = ' ';
    int comma,index,x,f;
    char tempstring[10];
    index = comma = x = f = 0;

    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!= EOF){

        if(!comma && ch != ','){
           tempstring[x] = ch;
            x++;

        }

        if(ch == ','){comma = 1;}
        else if(ch == 10){
            tempstring[x] = 0;
            comma = 0;
            x = 0;

            S[index].ID = strtol(tempstring,NULL,10);

            index++;
        }
    }
}

int** genGrades(FILE* F,struct Student* S){

    char ch = ' ';
    int x,comma,index, IDindex,ID,grade,i;
    char IDstring[50];
    char gradestring[3];
    int** grades;
    int gradeArraySize;
    x = comma = index = IDindex = 0;

    gradeArraySize = makeArraySize(F)+1;

    rewind(F);
    grades = (int**)calloc(gradeArraySize,sizeof(int*));
    for(i = 0; i < gradeArraySize; i++){

        grades[i] = (int*)calloc(2,sizeof(int));
    }

    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!= EOF){

         if(comma>=1 && ch != ','){
            gradestring[x] = ch;
            x++;
        }else if(comma <=0 &&  ch != ','){

         /* '   printf("%c",ch);' */
            IDstring[IDindex] = ch;
            IDindex++; 

        }

        if(ch == ','){comma++;}
        else if(ch == 10){

            IDstring[IDindex] = 0;
            ID = strtol(IDstring,NULL,10);
            grade = strtol(gradestring,NULL,10);
            grades[index][0] = ID;
            grades[index][1] = grade;
            comma = 0;
            x = 0;
            IDindex = 0;
            index++;
        }
        
    }

    ID = strtol(IDstring,NULL,10);
    grade = strtol(gradestring,NULL,10);
    grades[index][0] = ID;
    grades[index][1] = grade;


    
    
    return grades;
}

char** setL_Name(FILE * F, struct Student *S,int arrSize){

    char** names, ch;
    int i,j,comma,charDex,index;
    comma = charDex = index = 0;

    names = (char**)calloc(arrSize,sizeof(char*));

    for(i = 0; i < arrSize; i++){

        names[i] = (char*)calloc(50,sizeof(char));
        for(j = 0; j < 50; j++){

            names[i][j] = '.'; /* This is the only workaround I can find to allow data to be inputted into the sodding strings */

        }

    }

    rewind(F);
    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!=EOF){
    
        if(comma % 2 == 1 && ch != ','){
        
            names[index][charDex] = ch;
            charDex++;
        }
        if(ch == ','){comma++;}
        else if(ch ==  10){
            comma = 0;
            names[index][charDex] = 0;
            charDex = 0;
            index++;

        }
    }
    
    return names;

}

char ** setF_Name(FILE * F, struct Student *S,int arrSize){

    char** names, ch;
    int i,j,comma,charDex,index;
    comma = charDex = index = 0;

    names = (char**)calloc(arrSize,sizeof(char*));

    for(i = 0; i < arrSize; i++){

        names[i] = (char*)calloc(50,sizeof(char));
        for(j = 0; j < 50; j++){

            names[i][j] = '.'; /* This is the only workaround I can find to allow data to be inputted into the sodding strings */

        }

    }

    rewind(F);
    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!=EOF){
    
        if(comma % 2 == 0 && ch != ','){

            if((int)ch > 64 && (int)ch < 123 ){
            
                names[index][charDex] = ch;
                charDex++;
            }
        }
        if(ch == ','){comma++;}
        else if(ch ==  10){
            comma = 0;
            names[index][charDex] = 0;
            charDex = 0;
            index++;

        }
    }
    
    return names;


}


int main(int argc, char** argv){

    FILE* f1, *f2;
    struct Student* class;
    int i,j,fNameSize;
    int** grades;
    char** first_names;
    char** last_names;

    if(argc != 3){
        fprintf(stderr,"You entered %d argument(s) where 3 were expected (including the program itself as an arg)\n",argc);
        return 1;

    }
    
    f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"r");


    if( f2 == NULL || f1 == NULL) {

        fprintf(stderr,"Error reading files\nExiting program.\n");
        return 1;

    }else if(!isCSV(argv[1]) || !isCSV(argv[2])){

        fprintf(stderr,"Files entered are not type .csv\nExiting program.\n");
        return 1;
    }

    if(!correctFiles(argv[1],argv[2])){

        fprintf(stderr,"The students file was expected first and the activity file was expected second. However, you havent provided this.\n");
        return 1;
    }
   
    class = (struct Student*)calloc(makeArraySize(f1),sizeof(struct Student));

    fNameSize = makeArraySize(f1);


    first_names = setF_Name(f1,class,fNameSize);
    last_names = setL_Name(f1,class,fNameSize);

    rewind(f1);
    setIDs(f1,class);
    rewind(f1);     


    for(i = 0; i < fNameSize;i++){
        j = 0;
        while(first_names[i][j] != 0){
            /* printf("%c",first_names[i][j]); */
            class[i].fname[j] = first_names[i][j];
            j++;
        }
    }   

    grades = genGrades(f2,class);


    for(i = 0; i < fNameSize; i++){

      /*   printf("gradeID: %d\tgrade:%d"); */

    }

    for(i = 0; i < fNameSize; i++){
        j= 0;
        while(last_names[i][j]){

            class[i].lname[j] = last_names[i][j];
            j++;
        }

    }


    for(i = 0; i < fNameSize;i++){

        for(j = 0; j < makeArraySize(f2)+1; j++){

            if(class[i].ID == grades[j][0]){
               
                class[i].grade = grades[j][1];
                   
            }

        }

    }

    for(i = 0; i < fNameSize;i++){

        printf("%s %s %d\n",class[i].fname,class[i].lname,class[i].grade);
 
    }


    for(i = 0; i < fNameSize; i++){

        free(first_names[i]);
        free(last_names[i]);
    }
    for(i = 0; i < makeArraySize(f2)+1; i++){
        
        free(grades[i]);
    }


    fclose(f1);
    fclose(f2);
    free(grades);
    free(first_names);
    free(last_names);
    free(class);

    return 0;

}