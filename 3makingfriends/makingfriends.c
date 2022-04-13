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

typedef struct arc_list arc_list;
typedef struct node node;
typedef struct arc_queue arc_queue;
typedef struct arc arc;
typedef struct graph graph;

struct arc
{
    node *u;
    node *v;
    int index;
    int minutes;
    arc *next;
};

struct node
{
    int index;
    arc_list *arc;
    node *parrent;
    int size;
};
struct graph
{
    int n;       /* nodes.			*/
    int p;       // number of arcs
    node *nodes; // array of nodes
    arc *arcs;   // arra of arcs
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

graph *initGraph(int n, int p)
{
    graph *g = (graph *)malloc(sizeof(graph));
    node *nodes = (node *)malloc(n * sizeof(node));
    arc *arcs = (arc *)malloc(p * sizeof(arc));

    g->arcs = arcs;
    g->nodes = nodes;
    g->n = n;
    g->p = p;

    if (PRINT)
    {
        for (int i = 0; i < n; i++)
        {
            g->nodes[i].index = i;
        }
    }

    int temp;
    for (int i = 0; i < p; i++)
    {
        //pr("Inputted Arc: %d ", i);
        g->arcs[i].index = i;
        scanf("%d", &temp);
        //pr("u: %d ", temp);
        g->arcs[i].u = &g->nodes[temp - 1];
        scanf("%d", &temp);
        //pr("v: %d ", temp);
        g->arcs[i].v = &g->nodes[temp - 1];
        scanf("%d", &temp);
        //pr("weight: %d\n", temp);
        g->arcs[i].minutes = temp;
    }
    return g;
}

void swapArray(arc *arr, int i, int j)
{
    arc temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void heapify(arc *arr, int n, int i)
{
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].minutes > arr[largest].minutes)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].minutes > arr[largest].minutes)
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swapArray(arr, i, largest);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

void heapSort(arc *arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end
        swapArray(arr, 0, i);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void freeGraph(graph *g)
{
    free(g->arcs);
    free(g->nodes);
    free(g);
}

// Tried this firs was way to slow for bigger cases


node *find(node *v)
{
    if (v->parrent == NULL){
        return v;
    } else {
        v->parrent = find(v->parrent);
        return v->parrent;
    }
}


void unite(node *u, node *v)
{
    v->parrent = u;
}

arc *kruskal(graph *g)
{
    arc *returnTree = NULL; //= (arc*)malloc(sizeof(arc));
    arc *tempArc;
    node *temp1;
    node *temp2;

    heapSort(g->arcs, g->p);

    for (int i = 0; i < g->p; i++)
    {
        pr("--- processing arc: %d (%d <-> %d) ---\n", g->arcs[i].index, g->arcs[i].u->index + 1, g->arcs[i].v->index + 1);
        temp1 = find(g->arcs[i].u);
        temp2 = find(g->arcs[i].v);
        pr("sets: %d and %d\n", temp1->index + 1, temp2->index + 1);
        if (temp1 != temp2)
        {   
            unite(temp1, temp2);
            pr("united sets %d and %d\n", temp1->index + 1, temp2->index + 1);
            if (returnTree != NULL)
            {
                g->arcs[i].next = returnTree;
                returnTree = &g->arcs[i];
            }
            else
            {
                returnTree = &g->arcs[i];
            }
            pr("Inserted : %d with weight: %d\n", returnTree->index, returnTree->minutes);
        }
        pr("\n");
    }

    return returnTree;
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
    pr("Number of pairs: %d\n", p);

    graph *g = initGraph(n, p);
    arc *tree = kruskal(g);

    pr("Done with algorithm, Calculating sum of arcs \n");

    
    int sum = 0;
    while (tree != NULL)
    {
        sum = sum + tree->minutes;
        pr("Arc id: %d ", tree->index);
        pr("Cumulative sum: %d\n", sum);
        tree = tree->next;
    }

    pr("Final sum: ");
    printf("%d\n", sum);

    freeGraph(g);

    return 0;
}