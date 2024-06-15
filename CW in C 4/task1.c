#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int DataInFile(FILE* F,int choice){/* Choice allows to use this function in two ways. Grabbing word amount or newline amount */

    char ch = ' ';
    int count = 0;
    rewind(F);
    while((ch = fgetc(F))!= EOF){
        
        if(choice == 0 && ch == ','){       
            count++;
        }else if(choice == 1 && ch == 10){
            count++;
        } 

    }
 
    return count;
}

int isCSV(const char * filename){

    char chars[3];

    while(filename != NULL && *filename != '.'){
        /* printf("%c\n",*filename); */
        filename++;
    }
    filename++;

    chars[0] = *(filename++);
    chars[1] = *(filename++);
    chars[2] = *(filename++);

    if(chars[0] == 'c' && chars[1] == 's' && chars[2] == 'v'){
        return 1;
    }

    return 0;
}

double meanGrade(FILE* F, int studentCount){

    char ch = ' ' ;
    int counter;
    double sum = 0;
    char num[4] = {'0','0','0'};
    int comma,count;
    comma = count = counter = 0;
   
   
    rewind(F);

    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!= EOF){
        
        if(ch == 10){                   /* End of row do thing */           
            /*printf("%s\n",num); */
            /* printf("%ld\n",strtol(num,NULL,10)); */
            comma = 0;
            count = 0;
            counter++;
            sum += (double)strtol(num,NULL,10);

        }

        else if(ch == ','){comma =1;} /* make comma bool true if comma detected */
        else if(comma && ch != 10){ /* focus on data that is after comma and before newline */
            
           num[count] = ch;
           count++;

        }
        num[count] = 0;

    }
   /*  printf("\nMean: %f\n\n",sum); */
  
    
    return (double)(sum)/(double)(studentCount-1);
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

int* intARRAY(FILE* F){

    char ch = ' ' ;
    int counter,arraySize,comma,count,index;
    int* intARR;
    char num[4] = {'0','0','0'};

    comma = count = counter = index = 0;
    arraySize = makeArraySize(F);
    intARR = (int*)calloc(arraySize,sizeof(int));

    rewind(F);
    while((ch = fgetc(F))!= 10){}
    while((ch = fgetc(F))!= EOF){
        
        if(ch == 10){                             
            
            comma = 0;
            count = 0;
            counter++;
            intARR[index] = strtol(num,NULL,10);
            index++;
            num[0] = num[1] = num[2] = '0';

        }

        else if(ch == ','){comma =1;}
        else if(comma && ch != 10){  
           num[count] = ch;
           count++;

        }
        num[count] = 0;

    } 
    

    return intARR;

}

double SD(int* nums,double mean,int studentCount,FILE* numberCount){

    int i,arraySize;
    double sum = 0.0f;
    rewind(numberCount);
    arraySize = makeArraySize(numberCount);
    
    for(i = 0; i < arraySize;i++){

        sum = sum + pow(nums[i]-mean,2);

    }
    for(i = 0; i < (studentCount-1) - arraySize; i++ ){

        sum = sum + pow(0-mean,2);

    }
    
    sum = sum/(studentCount-1);
    sum = sqrt(sum);

    return sum;

}

int main(int argc, char** argv){

    FILE* f1, *f2;
    char* allo = (char*)calloc(1, sizeof(int));
    int* intARR,students;


    if(argc != 3){
        fprintf(stderr,"You entered %d argument(s) where 3 were expected (including the program itself as an arg)\n",argc);
        return 1;

    }
    
    f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"r");


    if( f2 == NULL || f1 == NULL) {

        fprintf(stderr,"Error reading files\nExiting program.\n");
        return 1;

    }
   
    intARR = intARRAY(f2);
    students = DataInFile(f1,1);
    
    printf("total students = %d\n",DataInFile(f1,1)-1);
    rewind(f1);
    rewind(f2);
    printf("absent students = %d\n", (DataInFile(f1,1)) - (DataInFile(f2,1)));
    rewind(f1);
    rewind(f2);
    printf("grade mean = %.2f\n",meanGrade(f2,DataInFile(f1,1)));  
    rewind(f1);
    rewind(f2);
    printf("grade sd = %.2f\n",SD(intARR,meanGrade(f2,students),students,f2));   


    free(allo);
    free(intARR);

    fclose(f1);
    fclose(f2);

    return 0;
}


/* TODO:


    output number of students                                                               -Done
    number of absent studies                                                                -Done                                                      
    mean of grades                                                                          -Done
    population standard deviation https://en.wikipedia.org/wiki/Standard_deviation          -Done



 */


  /*   for(i = 0; i < studentCount-1; i++){ */
           /*  
        
            printf("intARR[%d]: %d\n",i,intARR[i]);
            printf("mean %f\n",mean);
            printf("pow((intARR[%d] - %f),2) = %f\n",intARR[1],mean,pow(intARR[i]-mean,2)); 

        sum += pow((intARR[1] - mean),2); 
    }

    printf("sum: %f\n",sum);
    printf("Sum: %f\n",sqrt(sum/(double)(studentCount-1)));
    free(intARR);
*/

/* Code graveyard */
 /* int studentAmount(int nl_count){

    int i;
    int sum = 0;
 
    for(i = 1; i < nl_count; i++){ Setting i to 1 ignores the header of the CSV 
 
        sum++;

    }


    return sum;

}  */