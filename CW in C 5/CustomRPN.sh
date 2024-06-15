clear
gcc task3_test.c rpn.c queue.c stack.c linked_list.c -Wall -ansi --pedantic-errors -o task3_test -lm
./task3_test "12 * 173.45 ^ 33 / 2 -7 * 88 ^ (14 - 12)"