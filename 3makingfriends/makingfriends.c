#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT 1 /* enable/disable prints. */
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

typedef struct arc_list arc_list;
typedef struct node node;
typedef struct arc_queue arc_queue;
typedef struct arc arc;
typedef struct graph graph;

struct  arc
{
    node *u;
    node *v;
    int index;
    int minutes;
};


struct arc_queue
{
    arc_list *first;
    arc_list *last;
};



struct arc_list
{
    node *arc;
    arc_list *next;
};

struct node
{
    int index;
    arc_list *arc;
    node *next;
};
struct graph
{
    int n;       /* nodes.			*/
    int p;      //number of arcs
    node* nodes; //array of nodes
    arc* arcs;  //arra of arcs
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


graph* initGraph(int n, int p){
    graph *g = (graph *)malloc(sizeof(graph));
    node *nodes = (node *)malloc(n*sizeof(node));
    arc *arcs = (arc *)malloc(p*sizeof(arc));

    
    g->arcs = arcs;
    g->nodes = nodes;

    if (PRINT)
    {
        for (int i = 0; i < n; i++)
        {
            g->nodes[i].index = i;
        }
        
    }
    
    


    int temp;
    for (size_t i = 0; p < n; i++)
    {   
        g->arcs[i].index = i;
        scanf("%d",temp);
        g->arcs[i].u = &g->nodes[temp];
        g->nodes[temp].index = temp;
    }
    

}

int main(int argc, char *argv[])
{
    FILE *in; /* input file set to stdin	*/
    int n;    /* number of people.		*/
    int p;    // Number of pairs

    progname = argv[0]; /* name is a string in argv[0]. */
    in = stdin;         /* same as System.in in Java.	*/
    
    scanf("%1d",&n);
    scanf("%1d",&p);
    
    pr("Number of people: %d\n",n);
    pr("Number of pairs: %d\n",p);
    
    graph* g = initGraph(n,p);
    
}