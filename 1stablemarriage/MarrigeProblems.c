#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT		0	/* enable/disable prints. */

#if PRINT
#define pr(...)		do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define pr(...)		/* no effect at all */
#endif

static char* progname;

struct list_proposers {
	int     index;
	struct list_proposers*	next;
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


int main(int argc, char* argv[])
{   
        FILE*		in;	/* input file set to stdin	*/
        int		n;	/* number of nodes.		*/

        progname = argv[0];	/* name is a string in argv[0]. */
        in = stdin;		/* same as System.in in Java.	*/
        n = next_int();
        pr("Number of peeps: %d\n",n);

        int proposees[n][n];
        int proposers[n][n];
        memset(proposees, 0, n*sizeof(proposees[0]));
        memset(proposers, 10, n*sizeof(proposers[0]));
        pr("Init test: %d\n",proposees[0][0]);

        int proposedTo[n][n];

        int partners[n];

        for (int i = 0; i < 2*n;i++){
                partners[i] = -1;
                int personIndex;
                int input = next_int();
                        while(input == 0){
                                input = next_int();
                        }
                personIndex = input - 1;
                int isProposee;
                if (proposees[personIndex][0] == 0){
                        isProposee = 1;
                }else{  
                        isProposee = 0;
                }
                for (int j = 0; j < n;j++){
                        int input = next_int();
                        while(input == 0){
                                input = next_int();
                        }
                        if(isProposee){
                                proposees[personIndex][j] = input;
                        }else{
                                proposers[personIndex][j] = input;
                                proposedTo[personIndex][j] = 0;
                        }
                }
        }

        if (PRINT) {
                fclose(in);
                pr("proposees:\n");
                for (int i = 0; i < n;i++){
                        for (int j = 0; j < n;j++){
                                pr("%d ",proposees[i][j]);
                
                        }       
                        pr("\n");
                }

                pr("Proposers:\n");
                for (int i = 0; i < n;i++){
                        for (int j = 0; j < n;j++){
                                pr("%d ",proposers[i][j]);
                
                        }       
                        pr("\n");
                }
        }

        //The algorithm
        struct list_proposers temp = {0,NULL};
        struct list_proposers* first = &temp;
        int proposerIndex; 
        int proposeeIndex;
        for(int i = 1; i < n;i++){
                struct  list_proposers Newtemp = {i,first};
                first = &Newtemp;
        }

        while(first != NULL){
                pr("First in list is: %d\n",first->index +1);
                proposerIndex = first->index; 
                first = first->next;

                for( int i = 0; i < n;i++){
                        int rank = n+1;
                        if ((proposedTo[proposerIndex][i] != 1) && proposers[proposerIndex][i] < rank){
                                proposeeIndex = i;
                                rank = proposers[proposeeIndex][i];
                                if(rank = 1){break;}
                        }
                }

                proposedTo[proposerIndex][proposeeIndex] = 1;

                if (partners[proposeeIndex] == -1){
                        partners[proposeeIndex] = proposerIndex;
                        pr("A singel propsee is paired\n");
                }else if (proposees[proposeeIndex][partners[proposeeIndex]] 
                                > proposees[proposeeIndex][proposerIndex]){
                        struct list_proposers temp = {partners[proposeeIndex],first};
                        first = &temp;
                        partners[proposeeIndex] = proposerIndex;
                        pr("A proposer is swaped\n");
                }else{
                        struct list_proposers temp = {proposerIndex,first};
                        first = &temp;
                        pr("A failed proposal\n");
                }
        }

        for(int i = 0; i < n;i++){
                printf("%d\n",partners[i]+1);
        }

	return 0;
}