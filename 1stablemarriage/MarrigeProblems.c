#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINT		0	/* enable/disable prints. */

#if PRINT
#define pr(...)		do { fprintf(stderr, __VA_ARGS__); } while (0)
#else
#define pr(...)		/* no effect at all */
#endif

static char* progname;

typedef struct list_proposers list_proposers;
struct list_proposers{
	int     index;
	list_proposers*	next;
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
        int (*proposees)[n][n] = calloc(n*n,sizeof(proposees));
        pr("test 2\n");
        int (*proposers)[n][n] = calloc(n*n,sizeof(proposers));
        //memset(proposees, 0, n*sizeof(proposees[0]));
        //memset(proposers, 10, n*sizeof(proposers[0]));
        pr("test2\n");
        pr("Init test: %d\n",*(proposees)[0][0]);

        int (*proposedTo)[n][n] = calloc(n*n,sizeof(proposedTo));

        int partners[n];
        for (int i = 0; i < n; i++)
        {
                partners[i] = 0;
        }
        
        int isProposee;
        int personIndex;
        for (int i = 0; i < 2*n;i++){
                int input = 0;
                        while(input == 0){
                                input = next_int();
                        }
                personIndex = input - 1;
                
                if (partners[personIndex] == 0){
                        isProposee = 1;
                        partners[personIndex] = -1;
                        pr("Added proposee %d :",input);
                }else{  
                        isProposee = 0;
                        pr("Added proposer %d :",input);
                }
                for (int j = 0; j < n;j++){
                        input = 0;
                        while(input == 0){
                                input = next_int();
                        }
                        if(isProposee){

                                //proposees[personIndex][j] = input-1;
                                (*proposees)[personIndex][input-1] = j+1;
                        }else{
                                //proposers[personIndex][j] = input-1;
                                (*proposers)[personIndex][input-1] = j+1;
                                (*proposedTo)[personIndex][j] = 0;
                        }

                        pr(" %d ",input );
                        
                }
                pr("\n");
                
        
        }
        fclose(in);

        if (PRINT) {
                pr("proposees:\n");
                for (int i = 0; i < n;i++){
                        for (int j = 0; j < n;j++){
                                pr("%d ",(*proposees)[i][j]+1);
                
                        }       
                        pr("\n");
                }

                pr("Proposers:\n");
                for (int i = 0; i < n;i++){
                        for (int j = 0; j < n;j++){
                                pr("%d ",(*proposers)[i][j]+1);
                
                        }       
                        pr("\n");
                }
        }



        
        //The algorithm
        
        list_proposers * proposers_structs = (list_proposers *) malloc(n*sizeof(list_proposers));
        proposers_structs[0].index = 0;
        proposers_structs[0].next = NULL;
        list_proposers * first = (list_proposers *) malloc(sizeof(list_proposers));
        first = &proposers_structs[0];
        pr("inputed: %d\n",first->index+1);
        for(int i = 1; i < n;i++){
                proposers_structs[i].index = i;
                proposers_structs[i].next = first;
                first = &proposers_structs[i];
                pr("inputed: %d\n",first->index+1);
        }
        
        int proposerIndex; 
        int proposeeIndex;
        while(first != NULL){
                pr("First in list is: %d\n",first->index +1);
                proposerIndex = first->index; 
                pr("Proposer index: %d\n",proposerIndex);
                first = first->next;
                int rank = n+1;
                for( int i = 0; i < n;i++){
                        if (((*proposedTo)[proposerIndex][i] != 1) && ((*proposers)[proposerIndex][i] < rank)){
                                proposeeIndex = i;
                                rank = (*proposers)[proposerIndex][i];
                                 pr("Rank of %d is %d\n",i,rank);
                                if(rank == 1){break;}
                        }
                }

                (*proposedTo)[proposerIndex][proposeeIndex] = 1;

                if (partners[proposeeIndex] == -1){
                        partners[proposeeIndex] = proposerIndex;
                        pr("A singel propsee is paired (%d,%d)\n",proposeeIndex+1,proposerIndex+1);
                }else if ((*proposees)[proposeeIndex][partners[proposeeIndex]] 
                                > (*proposees)[proposeeIndex][proposerIndex]){
                        list_proposers temp = {partners[proposeeIndex],first};
                        first = &temp;
                        partners[proposeeIndex] = proposerIndex;
                        pr("A proposer is swaped (%d,%d)\n",proposeeIndex+1,proposerIndex+1);
                }else{
                        list_proposers temp = {proposerIndex,first};
                        first = &temp;
                        pr("A failed proposal , %d to %d\n",proposeeIndex+1,proposerIndex+1);
                }
                pr("current pairing: ");
                for(int i = 0; i < n; i++)
                {
                        pr("(%d,%d)",i+1,partners[i]+1);
                }
                pr("\n");
                //if(PRINT){sleep(3);}
                
        }

        for(int i = 0; i < n;i++){
                printf("%d\n",partners[i]+1);
        }
        free(proposees);
        free(proposers);
        free(proposedTo);
	return 0;
}