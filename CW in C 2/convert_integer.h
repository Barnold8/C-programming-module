/* copyright 2020 jamie twycross, jamie.twycross AT nottingham.ac.uk */
/* released under GNU GPL version 3 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int get_integer(void);
int convert_integer(char *);

/*	read a string from keyboard and convert to int value.
	if successful, returns the int value.
	if unsuccessful, return the value INT_MAX.
	unsuccessful if the string entered:
		* is not an integer (i.e. contains non-numeric characters)
		* is an integer but is greater than or equal to
		  the largest allowable int value
		* is an integer but is less than or equal to
		  the smallest allowable int value
*/
int get_integer(void)
{
	char str[64]; /* string to store input in */

	/* read string from keyboard */
	if(fgets(str, 63, stdin) == NULL)
	{
		/* error reading string */
		return INT_MAX; /* return error */
	}

	/* remove anything in string after line feed or carriage return */
	str[strcspn(str, "\r\n")] = '\0';

	return convert_integer(str);
}

int convert_integer(char *str)
{
	char *endptr;
	long val; /* converted number */

	/* return error if string NULL */
	if(!str)
		return INT_MAX;

	/* check if string empty or contains leading spaces */
	if (str[0] == '\0' || isspace((unsigned char) str[0]))
        return INT_MAX; /* return error */

	/* convert string to long integer */
	errno = 0;
	val = strtol(str, &endptr, 10);

	/* check if error converting number */
	if(errno != 0)
        return INT_MAX; /* return error */

	/* check entered value in int range */
	if(val <= INT_MIN || val >= INT_MAX)
        return INT_MAX; /* return error */

	/* check converted number bigger than minimum integer */
	if(val <= INT_MIN || errno == ERANGE)
        return INT_MAX; /* return error */

	/* check entire string successfully converted */
	if(endptr == str || *endptr != '\0')
        return INT_MAX; /* return error */

	/* success - return converted integer */
	return (int) val;
}
