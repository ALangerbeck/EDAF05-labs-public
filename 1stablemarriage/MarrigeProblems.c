#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT		1	/* enable/disable prints. */

#if PRINT
#define pr(...)		do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define pr(...)		/* no effect at all */
#endif

static char* progname;

static int next_int()
{
        int     x;
        int     c;

	x = 0;
        while (isdigit(c = getchar()))
                x = 10 * x + c - '0';
        return x;
}

void fillArrays(int *persons[],int n){
    for
}


int main(int argc, char* argv[])
{   
	FILE*		in;	/* input file set to stdin	*/
	int		n;	/* number of nodes.		*/

	progname = argv[0];	/* name is a string in argv[0]. */

	in = stdin;		/* same as System.in in Java.	*/

	n = next_int();

	fclose(in);
    printf("Number of peeps: %d\n",n);

    int propsees[n][n+1];
    int proposers[n][n+1];

    

	return 0;
}