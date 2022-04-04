#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT		1	/* enable/disable prints. */
#define WORD_LENGTH  5   

#if PRINT
#define pr(...)		do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define pr(...)		/* no effect at all */
#endif

static char* progname;

typedef struct list list;
typedef struct node node;

struct list {
	node*		edge;
	list*		next;
};

struct node{
	int     index;
    char    word[5];
    list*   adjacency;
};

/*
typedef struct edge edge;
struct node{
	g_node* u;
    g_node* v;
};
*/

typedef struct graph graph;

struct graph {
	int		n;	/* nodes.			*/
	int		m;	/* edges.			*/
	node*		nodes;	/* array of n nodes.		*/
	//edge*		e;	/* array of m edges.		*/
};

static int next_int()
{
    int     x;
    int     c;
	x = 0;
    while (isdigit(c = getchar()))
            x = 10 * x + c - '0';
    return x;
}


graph* init_graph(int n){
    node * word_nodes = (node *) malloc(n*sizeof(node));
    graph * g = (graph *) malloc (sizeof(graph));
    g->nodes = word_nodes;
    char temp_char;

    node* current_node;
    for (int i = 0; i < n; i++)
    {   
        current_node = &g->nodes[i];
        for (int j = 0; j < WORD_LENGTH; j++)
        {   temp_char = getchar();
            while (isspace(temp_char))
            {
                temp_char = getchar();
            }
            
            current_node->word[i] = temp_char;
            sleep(0.1);
        }
        
    }
    return g;
    
}

int main(int argc, char* argv[])
{   
    FILE*		in;	/* input file set to stdin	*/
    int		n;	    /* number of words.		*/
    int     q;      // Number of queries

    progname = argv[0];	/* name is a string in argv[0]. */
    in = stdin;		/* same as System.in in Java.	*/

    n = next_int();
    q = next_int();
    pr("Number of words: %d\n",n);
    pr("Number of queries: %d\n",q);

    graph* g = init_graph(n);

    free(g->nodes);
    free(g);


}