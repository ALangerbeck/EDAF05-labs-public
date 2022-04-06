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

/*
typedef struct edge edge;
struct node{
    g_node* u;
    g_node* v;
};
*/

typedef struct graph graph;

struct graph
{
    int n;       /* nodes.			*/
    node *nodes; /* array of n nodes.		*/
                 // edge*		e;	/* array of m edges.		*/
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

void printAdjacent(graph *g)
{
    for (int i = 0; i < g->n; i++)
    {
        node *tempNode = &g->nodes[i];
        list* adj = tempNode->adjacency;
        if (tempNode->adjacency == NULL){pr("Node %d, Word: %s Adj: None\n", i, tempNode->word);}
        else{
            pr("Node %d,Word: %s Adj:",i,tempNode->word);
            while (adj != NULL)
            {
                pr(" %s ",adj->node->word);
                adj = adj->next;
            }
            pr("\n");
        
        }
    }
}

graph *init_graph(int n)
{
    node *word_nodes = (node *)malloc(n * sizeof(node));
    graph *g = (graph *)malloc(sizeof(graph));
    g->nodes = word_nodes;
    g->n = n;
    char temp_char;

    // pr("g1\n");
    node *current_node;
    for (int i = 0; i < n; i++)
    {
        current_node = &g->nodes[i];
        current_node->index = i;

        for (int j = 0; j < WORD_LENGTH; j++)
        {
            temp_char = getchar();
            while (isspace(temp_char))
            {
                temp_char = getchar();
            }
            current_node->word[j] = temp_char;
        }
    }

    // pr("g2\n");
    char tempWord[WORD_LENGTH];
    char tempChar;
    int letterMissing = 0;
    for (int i = 0; i < n; i++)
    { // pr("g2.1\n");
        current_node = &g->nodes[i];
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                // pr("g2.2\n");
                letterMissing = 0;
                for (int o = 0; o < WORD_LENGTH; o++)
                {
                    tempWord[o] = g->nodes[j].word[o];
                }
                // pr("g2.3\n");
                for (int outerWordIndex = 1; outerWordIndex < WORD_LENGTH; outerWordIndex++)
                {
                    temp_char = current_node->word[outerWordIndex];
                    for (int innerWordIndex = 0; innerWordIndex < WORD_LENGTH; innerWordIndex++)
                    {
                        if (current_node->word[outerWordIndex] == tempWord[innerWordIndex])
                        {
                            tempWord[innerWordIndex] = '@';
                            letterMissing = 0;
                            break;
                        }
                        else
                        {
                            letterMissing = 1;
                        }
                    }
                    if (letterMissing == 1)
                    {
                        break;
                    }
                }
                // pr("g2.4\n");
                if (letterMissing == 0)
                {
                    list *adjacentNode = (list *)malloc(sizeof(list));
                    adjacentNode->node = &g->nodes[j];
                    adjacentNode->next = current_node->adjacency;
                    current_node->adjacency = adjacentNode;
                }
                // pr("g2.5\n");
            }
        }
    }

    return g;
}

void enqueue(queue *q, node *node)
{
    //pr("ENQ1\n");
    list *insertee = (list *)calloc(1, sizeof(list));
    insertee->node = node;
    insertee->next = NULL;
    //pr("ENQ2\n");
    if (q->first == NULL)
    {   //pr("ENQ2.1\n");
        q->first = insertee;
        q->last = insertee;
    }
    else
    {   
        //pr("ENQ2.2\n");
        q->last->next = insertee;
        //pr("ENQ2.3\n");
        q->last = insertee;
        
    }
    //pr("ENQ3\n");
}

node* dequeue(queue *q)
{
    node *returnNode;
    list *l;

    if (q->first == NULL)
    {
        return NULL;
    }
    else if (q->first == q->last)
    {
        l = q->first;
        returnNode = l->node;

        q->last = NULL;
        q->first = NULL;
        free(l);
        return returnNode;
    }
    else
    {
        l = q->first;
        returnNode = l->node;
        q->first = q->first->next;
        free(l);
        return returnNode;
    }
}

node* BFS(graph *g, int rootIndex, int stopIndex)
{

    node* tempNode; //= (node*)calloc(1,sizeof(node));
    queue* nodeQueue = (queue*)calloc(1,sizeof(queue));
    list* adjacent; //= (list*)calloc(1,sizeof(list));

    for (int i = 0; i < g->n; i++)
    {
        g->nodes[i].pred = NULL;
        g->nodes[i].visited = 0;
    }
    //pr("BFS2\n");
    enqueue(nodeQueue, &g->nodes[rootIndex]);
    g->nodes[rootIndex].visited = 1; // Might be wrong assignment maybe dereference

    while (nodeQueue->first != NULL)
    {   
        tempNode = dequeue(nodeQueue);
        //printf("%d\n",tempNode->index);
        adjacent = tempNode->adjacency;

        //pr("BFS5\n");
        while (adjacent != NULL)
        {
            if (adjacent->node->visited == 0)
            {   pr("visited: %s\n",adjacent->node->word);
                adjacent->node->visited = 1;
                enqueue(nodeQueue, adjacent->node);
                adjacent->node->pred = tempNode;
                if (adjacent->node->index == stopIndex)
                {   
                    free(nodeQueue);
                    return adjacent->node;
                }
            }
            adjacent = adjacent->next;
        }

    }
    free(nodeQueue);
    return NULL;
}

int main(int argc, char *argv[])
{
    FILE *in; /* input file set to stdin	*/
    int n;    /* number of words.		*/
    int q;    // Number of queries

    progname = argv[0]; /* name is a string in argv[0]. */
    in = stdin;         /* same as System.in in Java.	*/

    n = next_int();
    q = next_int();
    pr("Number of words: %d\n", n);
    pr("Number of queries: %d\n", q);

    graph *g = init_graph(n);
    printAdjacent(g);

    char* word1 = (char*)calloc(WORD_LENGTH,sizeof(char));
    char* word2 = (char*)calloc(WORD_LENGTH,sizeof(char));
    char tempWord[WORD_LENGTH];
    node* returnNode;

    // Go through all queries
    for (int outer = 0; outer < q; outer++)
    {   
        //pr("New Query\n");
        int rootIndex = -1;
        int stopIndex = -1;

        // read the two query words
        for (int inner = 0; inner < WORD_LENGTH; inner++)
        {   
            char temp_char;
            temp_char = getchar();
            while (isspace(temp_char))
            {
                temp_char = getchar();
            }
            word1[inner] = temp_char;
            
        }
        pr("Root Word: %s\n",word1);
        
        for (int inner2 = 0; inner2 < WORD_LENGTH; inner2++)
        {   
            char temp_char;
            temp_char = getchar();
            while (isspace(temp_char))
            {
                temp_char = getchar();
            }
            word2[inner2] = temp_char;
        }
        pr("Stop Word: %s\n",word2);
        // get the indices of the two words
        for (int i = 0; i < g->n; i++)
        {
            strcpy(tempWord, g->nodes[i].word);
            pr("Word: %s\n",tempWord);
            if (strcmp(word1, tempWord))
            {
                rootIndex = i;
                pr("Got root index\n");
            }
            if (strcmp(word2, tempWord))
            {
                stopIndex = i;
                pr("Got stop index\n");
            }
            if (rootIndex != -1 && stopIndex != -1)
            {
                break;
            }
        }
    
        // see if there actually is words
        if (rootIndex == -1 || stopIndex == -1)
        {
            printf("At least one of the words in the querey does not exist\n");
        }
        pr("root index: %d stop index:%d\n",rootIndex,stopIndex);
        //run algorithm and print depending on result
        returnNode = BFS(g,rootIndex,stopIndex);
        if(returnNode == NULL){
            printf("Impossible\n");
        }else{
            int depth = 0;
            while (returnNode->pred != NULL)
            {   
                depth += 1;
                returnNode = returnNode->pred;
            }
            printf("%d\n",depth);
        }
    }

    // Free the allocated resources
    list *templist_1;
    list *templist_2;

    for (int i = 0; i < n; i++)
    {
        templist_1 = g->nodes[i].adjacency;
        while (templist_1 != NULL)
        {
            templist_2 = templist_1->next;
            free(templist_1);
            templist_1 = templist_2;
        }
    }
    free(word1);
    free(word2);
    free(g->nodes);
    free(g);
}