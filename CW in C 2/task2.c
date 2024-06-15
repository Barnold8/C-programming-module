#include <stdio.h>

int getInput(){ /* Gets input from keyboard via terminal */

    int x;

    scanf("%d",&x);

    return x;

}

int getYear(int year){

    return (year + year / 4 - year / 100 + year / 400) % 7;

}


int weeksInYear(int year){

    if( getYear(year) == 4 || getYear(year - 1) == 3){
        return 53;

    }else{return 52;}

}

int myfloor(float number){
    
    return (int) number;

}

int isLeapYear(int yyyy){ /* This works  */

    
    if((yyyy % 400) == 0 ){

        return 1;
        
    }else if((yyyy % 4) == 0 && (yyyy % 100) != 0){

        return 1;

    }

    return 0;
}

int daysInYear(int dd, int mm,int yyyy){ /* returns the amount of days up until given date */
    /*jan 31
    feb 28
    mar 31
    april 30
    May 31
    JUne 30
    July 31
    August 31
    September 30
    October 31
    November
    December
*/

    int i;
    int num = 0;
    int months[12] = {31,0,31,30,31,30,31,31,30,31,30,31};
    
    months[1] = isLeapYear(yyyy) ? 29 : 28; /* Configure feb to month array */


    if(dd > 0){ /* if there are any days inputted, process them. - If there are leftover days in the month m-2 is to not go ino the month that the days reside in */

        for(i = 0; i <= mm-2;i++){

            num += months[i]; /* Add days to how many exist in the current month */
        }
        num += dd;  /* This line adds the days left in the month since we stop at the month before */
    }
    else{ /* Go through the months and add their respective days */

        for(i = 0; i <= mm-1;i++){
            num += months[i]; /* Add days to how many exist in the current month */
        }
   
    }
    return num;
}

int DayOfWeek(int dd,int mm, int yyyy){

    int MonthCodes[12] = {0,3,3,6,1,4,6,2,5,0,3,5};

    int YearCode = (yyyy % 10) +(((yyyy/ 10 ) % 10 )* 10); /* Got the way to get last digit from https://www.geeksforgeeks.org/find-first-last-digits-number/ and made my own way to get two digits */
    int MonthCode = MonthCodes[mm-1]; /* mm-1 means month input -1 because jan would be 1 but jans array index is 0 */
    int CenturyCode;
    int DateNumber = dd;
    int LeapYearCode = isLeapYear(yyyy) == 1 && mm <= 2 ? 1 : 0;
    YearCode = ( (YearCode + (YearCode / 4)) % 7);
    


    if(yyyy >= 1900 && yyyy < 2000){

        CenturyCode = 0;

    }else if(yyyy >= 2000 && yyyy < 2100){

        CenturyCode = 6;

    }else{CenturyCode = 4;}

    return (YearCode + MonthCode + CenturyCode + DateNumber - LeapYearCode) % 7; /* https://artofmemory.com/blog/how-to-calculate-the-day-of-the-week/ is how I figured a way to code a way to day of the week */
}

int calculate_week(int ordDay,int weekday, int year){ /* Fixed I think, could still prove to have errors */
    
    float week = myfloor((ordDay - weekday + 10)/7);

    if(week == 0){
        week = weeksInYear(year -1);
    }
    if(week > weeksInYear(year)){
        
        if(weekday < 4){
           
            week = 1;

        }
    }

    return week;
}

int ordinalDay(int dd,int mm, int yyyy){  /* Function tested and works as intended */
   
    int ordDay;

    if(mm == 1){
   
        return dd;
    }
    if(mm == 2){
      
        return dd + 31;
    }

    ordDay = myfloor((30.6 * mm) - 91.4) + dd;

    if(isLeapYear(yyyy)){
    
        return ordDay + 60;
    }

    return ordDay + 59;

}

/* Printing methods */
int calDate(int dd,int mm,int yyyy){ /* debugged */

    if(dd > 31 || mm > 12){
        
        return 1;

    }else if(dd <= 0 || mm <= 0 || yyyy <= 0){
        
        return 1;

    }

    if(dd < 10 && mm < 10){
        printf("%d-0%d-0%d\n",yyyy,mm,dd);
     
    }
    else if(mm < 10){
       
        printf("%d-0%d-%d\n",yyyy,mm,dd); /* This feels like a very messy way of doing it but I dont wanna allocate ram for a string so this is it */

    }else if(dd < 10){
        printf("%d-%d-0%d\n",yyyy,mm,dd);
    }
    else{

        printf("%d-%d-%d\n",yyyy,mm,dd);

    }
    return 0;

}

int ordinal(int dd, int mm, int yyyy){
    
    int days = daysInYear(dd,mm,yyyy);
    
    
    if(days < 100){

        if(days < 10){

            printf("%d-00%d\n",yyyy,daysInYear(dd,mm,yyyy));
        }else{
            printf("%d-0%d\n",yyyy,daysInYear(dd,mm,yyyy));

        }
        

    }
    else{printf("%d-%d\n",yyyy,daysInYear(dd,mm,yyyy));}

    

    return 0;    
}

int ISOConv(int dd, int mm, int yyyy){

    int weekDay = DayOfWeek(dd,mm,yyyy);
    int ordDay = ordinalDay(dd,mm,yyyy);  
    int week;
    int year = yyyy;

    if (weekDay == 0){
        weekDay = 7;}
    
    week = calculate_week(ordDay,weekDay,year);

    if((week == 53 || week == 52) && (mm == 1)){
        year -= 1;
            
    }else if(mm == 12 && week == 1){

        year += 1;

    }


    if(week < 10){
        printf("%d-W0%d-%d",year,week,weekDay);
    }else{
        printf("%d-W%d-%d",year,week,weekDay);
    }
    
    return 0;
}

void printDates(){
    
    int day,month,year;
    day = getInput();
    month = getInput();
    year = getInput();

    calDate(day,month,year); 

    ordinal(day,month,year);

    ISOConv(day,month,year);

    printf("\n");

}

/* -------------------- */

void debug(int dd,int mm, int yyyy){

    printf("Date debugging: \t %d-%d-%d\n",yyyy,mm,dd);

    printf("%d\n\n",ISOConv(dd,mm,yyyy));

}


int main(int argc, char** argv){

    printDates();

    return 0;
}