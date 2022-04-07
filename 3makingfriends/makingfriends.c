#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT 0 /* enable/disable prints. */
#define WORD_LENGTH 5

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

typedef struct list list;
typedef struct node node;
typedef struct queue queue;

struct queue
{
    list *first;
    list *last;
};

struct list
{
    node *node;
    list *next;
};

struct node
{
    int index;
    char word[WORD_LENGTH];
    list *adjacency;
    int visited;
    node *pred;
};

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
    int n;    /* number of words.		*/
    int q;    // Number of queries

    progname = argv[0]; /* name is a string in argv[0]. */
    in = stdin;         /* same as System.in in Java.	*/
}