# COMP1005 2021 Coursework 02

## Introduction

This coursework focuses on writing interesting programs using functions, variables, operators, conditionals and loops. There are **two tasks** to complete, details of which are given below. Links to external pages are provided in the details below which you will need to follow and read to complete each task.

## Assessment

This coursework is worth **10%** of your final course grade. The points awarded for each task are as follows:

|            | Compilation | Implementation | Execution | **Total** |
| ---------- | :---------: | :------------: | :-------: | :-------: |
| **Task 1** | 2           | 1              | 2         | **5**     |
| **Task 2** | 2           | 3              | 8         | **13**    |

For **Task 1**, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in [Task 1 Details](#details) below, you are awarded *one* point. If your program produces the correct output as described in [Task 1 Details](#details) below, you are awarded *one* point. If your program handles invalid input correctly as described in [Task 1 Details](#details) below, you are awarded *one* point.

For **Task 2**, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in [Task 2 Details](#details-2) below, you are awarded a maximum of *two* points. If your program produces the correct output as described in [Task 2 Details](#details-2) below, you are awarded *eight* points.

Your score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk`. You can make as many revisions and pushes as you like, hopefully increasing your score as you do so. Your final score for the coursework will the score of your last push.

The contribution towards your final course grade is calculated as follows:

```maths
	floor(10 * (task1_points_awarded + task1_points_awarded) / 18)
```

Your provisional score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk`. Your final score will be based on the code in the last commit pushed to `projects.cs.nott.ac.uk` *before* the coursework deadline. Commits pushed after the coursework deadline will be disregarded. After the coursework deadline, your code will undergo further review and, based on this review, your provisional score may go up or down. This further review will include checks for code plagiarism and for trivial implementations e.g. implementations just containing an empty main function or clearly not written following the task guidelines. Final scores will be published on the COMP1005 moodle pages around a week after the coursework deadline.

Your repository contains a file called `.gitlab-ci.yml`. This file is used during the assessment process and *must not* be removed or edited in any way. Any tampering with this file will result in a score of zero for this coursework.

This coursework is individual work i.e. *must be your own work* and follow the University [Academic integrity and misconduct](https://www.nottingham.ac.uk/studyingeffectively/studying/integrity/index.aspx) guidance.

## Task 1

### Overview

**Pascal's triangle** (see [here](https://en.wikipedia.org/wiki/Pascal%27s_triangle) and [here](http://www.mathsisfun.com/pascals-triangle.html)) is an interesting pattern of numbers named after the French mathematical Blaise Pascal. Your task is to write a program to calculate and print out Pascal's triangle.

Your C source file for this task *must* be named `task1.c` and placed in the top-level directory of your git project for this coursework.

### Details

Your program should calculate Pascal's triangle for a given number of rows specified by the user and print out the triangle in the format described below. There are many ways to calculate the triangle (see the links in the [Overview](#overview) above for a starting point).

You are free to choose whichever method you want to implement your program with the following restrictions:

* you must *calculate* the values in the triangle, rather than e.g. store them in a precomputed lookup table
* your implementation must contain a correctly declared `main` function
* you are not allowed to use global variables

Your program should allow the user to specify the number of rows to print as a command line argument when your program is run. That is, if the user wants to print out the first **5** rows of Pascal's triangle, they will type:

```bash
$ ./task1 5
```

Your program should only allow users to specify integer values between *1* and *20* inclusive for the number of rows to print. If any other value for the number of rows is specified by the user (or no value at all), then your program should print an error message and return a *non-zero* exit value. If a valid value is specified, your program should print Pascal's triangle for the specified number of rows and return an exit value of *zero* (i.e. success).

**Hint**: Use `argc` and `argv` to get the number of rows specified by the user when the program is run. Use the standard library function `strtol` to convert the number of rows entered from a string to an integer and to check that the user has entered an integer. If you write your string to integer conversion code as a function, you can easily reuse it in Tasks 2 and 3 below.

Your program should output the rows of Pascal's triangle to `stdout` in *reverse order*. Here is an example output:

```bash
$ ./task1 5
1   4   6   4   1
  1   3   3   1
    1   2   1
      1   1
        1
```

As in this example, you should output the numbers as a **triangle**.

One possible way of implementing this task is to write *three* functions (in addition to `main`). The first function takes the number of rows `n` input by the user as an argument and calculates and outputs the values in each row of the triangle using two nested loops. The outer loop iterates over the rows i.e. `i = [n, 0]`, and the inner loop iterates over the range `j = [0, i]`. In the inner loop, a second function which calculates `C(i, j)` (the possible combinations of `i` objects from a set of `j` objects) is called repeatedly. This second function uses the standard equation to calculate `C(i, j)`, calling a third function several times to calculate the factorial of a given number i.e. this third function takes a number `x` as an argument and returns `x!`. Be careful with integer overflow, as calculating factorials of even small numbers will produce numbers which may be too big to store in an `int` type.

## Task 2

### Overview

The [Gregorian calendar](https://en.wikipedia.org/wiki/Gregorian_calendar) is a widely used calendar. A number of different standardised date formats can be used to represent dates in the Gregorian calendar. Your task is to write a program which accepts a date input by a user and calculates and prints out the date in three of these standardised formats: calendar date format, ordinal date format, and ISO week date format.

Your C source file for this task *must* be named `task2.c` and placed in the top-level directory of your git project for this coursework.

### Details

Dates can be specified and represented using different calendars and formats. In this task we will focus on dates specified in the [Gregorian calendar](https://en.wikipedia.org/wiki/Gregorian_calendar). When representing dates in the Gregorian calendar, different formats can be used. [International Standard ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) attempts to standardise the way Gregorian dates are represented (see [here](https://www.cl.cam.ac.uk/~mgk25/iso-time.html) for a useful summary).

The following definitions are given in ISO 8601:

* A [calendar date](https://en.wikipedia.org/wiki/Calendar_date) is a date in the format `YYYY-MM-DD`, where `YYYY` is the calendar year, `MM` is the calendar month, and `DD` is the calendar day of the month.

* An [ordinal date](https://en.wikipedia.org/wiki/Ordinal_date) is a date in the format `YYYY-DDD`, where `YYYY` is the calendar year and `DDD` is the calendar day of the year (ordinal day).

* A [week date](https://en.wikipedia.org/wiki/ISO_week_date) is a date in the format `YYYY-Www-D`, where `YYYY` is the calendar year to which the week belongs (ISO year), `ww` is the calendar week (ISO week), and `D` is the day of the week (ISO weekday number).

* The **ISO weekday number** assigns a number to each day of the week, with `Monday=1, Tuesday=2, ..., Sunday=7'.

Your task is to write a program which accepts the Gregorian day, month and year input (in that order) by the user and calculates and outputs the *correctly formatted* (as in the definitions above) **calendar date**, **ordinal date**, and **week date**.

Your program can use whichever method you choose to calculate the ordinal and week dates. However, you are **not allowed** to use library functions (C standard library or otherwise) in your program other than `printf`, and you must not use any global variables.

Your program should output **three** lines corresponding to the ISO 8601 extended format calendar date, ordinal date and week date respectively. For example, if the user enters the three numbers "4", "6", and "1945" (the date Monday 4th June 1945), your program should output:

```
1945-06-04
1945-155
1945-W23-1
```

You program will be tested by running it with a series of randomly generated dates between the years 1900 and 2100. For this task, you can assume all dates input by the user will be valid (this is not generally a good assumption for a program though!).

Since we have not covered keyboard input yet in lectures, a function to read a number from the keyboard is provided. This function is called `get_integer()` and is provided in the `convert_integer.h` header file. To use this function, include the header file at the top of your program and call the function three times to read in the day, month and year respectively from the keyboard:

```c
#include "convert_integer.h"

...

	day = get_integer();
	month = get_integer();
	year = get_integer();

...
```

One approach which you could use (although you are free to use any approach you like) is to break the problem down into smaller steps and procedure calls (viz. *procedural decomposition*) to first calculate the ordinal date from the calendar date, and then use the ordinal date to calculate the week date. Some hints for how to do this are given below. If you take the approach suggested below, you will quite likely end up with *nine* functions (not listed in any particular order):

1. a main function
2. a function which calculates the ISO week year
3. a function which calculates the ISO week number
4. a function which calculates the weeks in a year
5. a function which calculates the ISO weekday number
6. a function which calculates the day of the week for 1st January
7. a function which calculates the ordinal day
8. a function which calculates if a year is a leap year or not
9. a function which rounds down a decimal to an integer

In your `main` function, aside from getting the user input and printing the results as described above, you can call function ` to calculate the ordinal day, and functions 5, 3 and 2 to calculate the ISO week date. All the other functions are called from these four functions to help in their calculations.

The first step in the suggested approach is to calculate the ordinal date. The following pseudocode calculates and returns the ordinal day from a calendar date (see [here](https://en.wikipedia.org/wiki/Ordinal_date) for more details):

```python
def calculate_ordinal_day(day, month, year):
	if month is January:
		return day
	if month is February:
		return day + 31
	ordinal_day = floor(30.6 * month - 91.4) + day
	if year is leap year:
		return ordinal_day + 60
	return ordinal_day + 59
```

Where the `floor` function returns the largest integer not greater than an given value (you will need to write your own `floor` function rather than use the one in the C standard library). Do *not* call your function `floor` though, otherwise it will clash with the standard library function. You will also need to write a function which determines if a year is a leap year. [Leap years in the Gregorian calendar](https://en.wikipedia.org/wiki/Leap_year#Gregorian_calendar) are defined as:

> Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100, but these centurial years are leap years if they are exactly divisible by 400. For example, the years 1700, 1800, and 1900 were not leap years, but the years 1600 and 2000 were.

Once you have the ordinal day, you can use the ordinal day along with the day of the week to calculate the ISO week. So, first we need to calculate the day of the week for our particular date.

[Gauss' algorithm](https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gauss.27s_algorithm) is once approach to calculate the day of the week. Gauss' algorithm calculates the day of the week of 1st January for a particular year, and we can then use some straightforward modulo 7 arithmetic on the ordinal day to calculate the day of the week for our specific calendar date. Gauss' algorithm to calculate the day of the week `d` of 1st January is:

```maths
d = mod(1 + 5 * mod(Y-1, 4) + 4 * mod(Y-1, 100) + 6 * mod(Y-1, 400), 7)
```

Where `Y` is the calendar year, and `mod(X, Y)` returns X modulo Y. Note that Gauss' algorithm returns `d=0` for Sunday, `d=1` for Monday, ..., `d=6` for Saturday, whereas ISO weekday numbers are `Monday=1, Tuesday=2, ..., Sunday=7`. Now we have the day of the week of 1st January for our year, we can use this and the ordinal day we calculated to work out the ISO week day for our particular date using modulo 7 arithmetic.

Going back to calculating the ISO week, we can now do this using the ordinal day and ISO week day for any calendar date. The algorithm for doing this is (more details [here](https://en.wikipedia.org/wiki/ISO_week_date#Calculating_the_week_number_of_a_given_date)):

```python
def calculate_week(ordinal_day, week_day, year):
	week = floor((ordinal_day - week_day + 10) / 7)
	if week is 0:
		week = weeks_in_year(year - 1)
	if week > weeks_in_year(year):
		if week_day before Thursday:
			week = 1
```

Where the `weeks_in_year` function returns the number of weeks in a given calendar year. The number of weeks in a year can be calculated using the following pseudocode (see [here](https://en.wikipedia.org/wiki/ISO_week_date#Weeks_per_year) for details):

```python
def p(year):
	p = mod(year + year / 4 - year / 100 + year / 400, 7)

def calculate_weeks_in_year(year):
	if p(year) is 4 or p(year - 1) is 3:
		weeks_in_year = 53
	else:
		weeks_in_year = 52
```

The ISO year is straightforward to work out for the ISO week returned by this algorithm. If the calendar month is December and the ISO week returned is 1, then the ISO year is the year following the calendar year. If the calendar month is January and ISO week returned is 52 or 53 then the ISO year is the previous calendar year.