#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT 1 /* enable/disable prints. */

#if PRINT
#define pr(...)                       \
    do                                \
    {                                 \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)
#else
#define pr(...) /* no effect at all */
#endif

static char *progname;

static int next_int()
{
    int x;
    int c;
    x = 0;
    while (isdigit(c = getchar()))
        x = 10 * x + c - '0';
    return x;
}

int main(int argc, char *argv[])
{
    FILE *in; /* input file set to stdin	*/
    int n;    /* number of people.		*/
    int p;    // Number of pairs

    progname = argv[0]; /* name is a string in argv[0]. */
    in = stdin;         /* same as System.in in Java.	*/

    scanf("%d", &n);
    scanf("%d", &p);

    pr("Number of people: %d\n", n);


    return 0;
}