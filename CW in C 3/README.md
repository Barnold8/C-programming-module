# COMP1005 2021 Coursework 03

## Introduction

This activity focuses on writing one interesting program using command line arguments and dynamic memory allocation. There is **one task** to complete, details of which are given below. Links to external pages are provided in the details below which you will need to follow and read to complete the task.

## Assessment

This coursework is worth **5%** of your final course grade. The points awarded for each task are as follows:

|            | Compilation | Implementation | Execution | **Total** |
| ---------- | :---------: | :------------: | :-------: | :-------: |
| **Task 1** | 2           | 2              | 2         | **6**     |


For **Task 1**, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in [Task 1 Details](#details) below, you are awarded *one* point.  If your program is implemented so that no memory leaks occur when it is executed, you are awarded *one* point. If your program produces the correct output as described in [Task 1 Details](#details) below, you are awarded *one* point. If your program handles invalid input correctly as described in [Task 1 Details](#details) below, you are awarded *one* point.

Your score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk`. You can make as many revisions and pushes as you like, hopefully increasing your score as you do so. Your final score for the coursework will the score of your last push.

The contribution towards your final course grade is calculated as follows:

```maths
	floor(5 * task1_points_awarded / 6)
```

Your provisional score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk`. Your final score will be based on the code in the last commit pushed to `projects.cs.nott.ac.uk` *before* the coursework deadline. Commits pushed after the coursework deadline will be disregarded. After the coursework deadline, your code will undergo further review and, based on this review, your provisional score may go up or down. This further review will include checks for code plagiarism and for trivial implementations e.g. implementations just containing an empty main function or clearly not written following the task guidelines. Final scores will be published on the COMP1005 moodle pages around a week after the coursework deadline.

Your repository contains a file called `.gitlab-ci.yml`. This file is used during the assessment process and *must not* be removed or edited in any way. Any tampering with this file will result in a score of zero for this coursework.

This coursework is individual work i.e. *must be your own work* and follow the University [Academic integrity and misconduct](https://www.nottingham.ac.uk/studyingeffectively/studying/integrity/index.aspx) guidance.

## Task 1

### Overview

Cellular automata are fascinating models which have been studied extensively and have a wide range of applications in many fields. In this task you will implement an [elementary cellular automaton](http://mathworld.wolfram.com/ElementaryCellularAutomaton.html).

Your C source file for this task *must* be named `task1.c` and placed in the top-level directory of your git project for this coursework.

### Details

[Cellular automata](https://en.wikipedia.org/wiki/Cellular_automaton) have a long history in mathematics and computer science and were first discovered in the 1940s by John von Neumann and Stanislaw Ulam, two of the founding fathers of computer science. Since then they have found many applications in diverse field including artificial life, physics and biology. While simple to describe and implement, they are capable of generating amazingly complex behaviour, including chaotic dynamics and universal computation.

For this task you will implement the simplest type of cellular automaton - an [elementary cellular automaton](http://mathworld.wolfram.com/ElementaryCellularAutomaton.html). You should first read [this chapter](http://natureofcode.com/book/chapter-7-cellular-automata/), which will give you a good introduction to what an elementary cellular automaton is (you only need to read up to and not including Section 7.6). It also provides some example code. You should not copy this code directly, but use it to help you understand how to implement your own program.

Your program when run should take *three* values from the user as command line arguments. These values are:

1. the number of cells in the one-dimensional grid (a positive integer)
2. the number of generations to evolve and output the cellular automata for (a positive integer)
3. the Wolfram code specifying which the rule set to evolve your cellular automata with (an integer in the range `[0,255]`).

These three arguments should be specified in this order on the command line when the user runs your program. You should check that the arguments are all valid and within the ranges given. If the user enters the wrong number of arguments or invalid arguments e.g. the number of cells as `-10`, then your program should print an error message and exit with a non-zero exit value.

For the values specified by the user, your program should calculate and print each generation of the cellular automata on a newline. You should print a `*` (asterisk) character to show a cell is alive, and a ` ` (space) character to show a cell is dead. For the initial generation, you should start with a row of cells that are all dead, except for the centre cell (or left of centre cell for an even number of cells) which is alive. You should assume that your row wraps around, that is, the neighbour of the left-most cell is the right-most cell and vice versa.

For example, the output when the users run your program with 30 cells for 20 generations with rule 110 should be:

```bash
$ ./task1 30 20 110
               *
              **
             ***
            ** *
           *****
          **   *
         ***  **
        ** * ***
       ******* *
      **     ***
     ***    ** *
    ** *   *****
   *****  **   *
  **   * ***  **
 ***  **** * ***
** * **  ***** *
******* **   ***             *
      ****  ** *            **
     **  * *****           ***
    *** ****   *          ** *
```

You are free to choose whichever method you want to implement your program with the following restrictions:

* your implementation must contain a correctly declared `main` function
* you are not allowed to use global variables

Some hints for possible ways to implement your program are given below.

You could store the states of cells in the current and next generations in two arrays. The length of each array will be the number of cells specified by the user. Since this length is specified at runtime, you will need to allocate the memory for these arrays dynamically using `malloc` or `calloc`.

The main computation in your program could be performed by two nested loops. The outer loop would iterate over each generation. For each generation, an inner loop would iterate over all the cells in the current generation array. Based on the state in the current generation of each cell and its two neighbours, you can calculate the state in the next generation and store this in the next generation array. After calculating the next generation states for all cells in the current generation, you can then print out the next generation. Finally you can copy the next generation array to the current generation array, and perform the whole procedure again for the next generation.

To calculate the state of a cell in the next generation from it and its neighbours current state, you can use some simple binary manipulation. For example, say you were using the ruleset with Wolfram code 110 and you wanted to calculate the state in the next generation of a dead cell with two live neighbours i.e. `101`. First, treat `101` as a binary number and convert it to decimal i.e. `5`. Now right shift the rule number i.e. `110` by `5` and look at the value of the least significant bit i.e. `0`. This is the state of the cell in the next generation.  A complete set of pictures for each Wolfram code is given [here](http://mathworld.wolfram.com/ElementaryCellularAutomaton.html). [Rule 90](https://en.wikipedia.org/wiki/Rule_90) and [Rule 110](https://en.wikipedia.org/wiki/Rule_110) are particular interesting.

Your program should handle dynamically allocated memory correctly i.e. free all dynamically allocated memory. As discussed in lectures, a good tool for assessing if a program has handled dynamic memory allocation correctly is `valgrind`. To check your program using `valgrind` you can type:

```bash
$ valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./task1
```

If your program has correctly handled dynamic memory allocation, the last line of output should read:

```
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Extensions

A number of possible extensions to this task are discussed below. **No additional points** are given for implementing these extensions, but they are interesting to explore, and you should try to implement some of these if you have time and have completed all of the tasks above. I would be very interested to see and discuss your implementations in Lab sessions.

Do *not* implement any of these extensions in `task1.c` (otherwise the build pipeline may decrease your score for this task). Instead, create a *new source file* in your repository. I would suggest naming this file e.g. `task1extended.c`.

One obvious extension is to improve the graphical output. You could use OpenGL to do this (see e.g. [An Introduction on OpenGL with 2D Graphics](http://www3.ntu.edu.sg/home/ehchua/programming/opengl/cg_introduction.html)), although there are a number of other C graphics libraries which could work. Plotting rather than printing the output will allow you to explore a much larger grid and more easily view interesting behaviour.

Another extension is to allow different configurations for the initial state of the cellular automata. You might start from a random initial state, or allow the user to specify the initial state in a file. Starting from a random state is interesting since it helps you see how the cellular automata transitions from a disordered to ordered state. When starting from a random state, it is often useful to allow the user to specify a random seed, so that any interesting random initial states can be reproduced at a later time by entering the same random seed.

You can also increase the number of possible states a cell can have (and colour your output based on state), and the size of the cell neighbourhood, so that e.g. the *two* cells of the left of a cell and the *two* cells on the right influence the state of a cell. Overlaying two elementary cellular automata can also produce interesting results.

If you really like cellular automata, then have a look at John Conway's [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), the most famous 2D cellular automaton. Implementing and exploring this cellular automaton is lots of fun, see [this video](https://www.youtube.com/watch?v=C2vgICfQawE) for some examples of what is possible in the Game of Life. More implementation details can be found in Section 7.6 of [this chapter](http://natureofcode.com/book/chapter-7-cellular-automata/).
