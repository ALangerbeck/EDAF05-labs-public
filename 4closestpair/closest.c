#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define PRINT 0 /* enable/disable prints. */

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
typedef struct point point;
typedef struct list_p list_p;

struct list_p
{
    point* p;
    list_p* next;

};


struct point{
    int x_cord;
    int y_cord;
    int index;
    point* next;
};

void merge(int arr[], int l, int m, int r,int isX,point* players)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    /* create temp arrays */
    int L[n1], R[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    int leftVal;
    int rightVal;
    while (i < n1 && j < n2) {
        if (isX)
        {   
            leftVal = players[L[i]].x_cord;
            rightVal = players[R[i]].x_cord;
        }else{
            int leftVal = players[L[i]].y_cord;
            int rightVal = players[R[i]].y_cord;
        }
        if (leftVal <= rightVal) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
        
        
    }
  
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
  
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r , int isX, point* players)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m,isX,players);
        mergeSort(arr, m + 1, r, isX,players);
  
        merge(arr, l, m, r, isX,players);
    }
}
static int next_int()
{
    int x;
    int c;
    x = 0;
    while (isdigit(c = getchar()))
        x = 10 * x + c - '0';
    return x;
}



double distance(point point1,point point2){
    return sqrt(pow((double) (point1.x_cord - point2.x_cord),2) + pow((double)(point1.y_cord - point2.y_cord),2));
}

point* inputPoints(int p){
    point *players = (point*)malloc(p*sizeof(point));
    int temp;
    for (int i = 0; i < p; i++)
    {
        players[i].index = i;
        scanf("%d",&temp);
        players[i].x_cord = temp;
        scanf("%d",&temp);
        players[i].y_cord = temp;
    }
    return players;
}
double min(double f1,double f2){
    if (f1 <= f2){ return f1;} else {return f2;}
}

double bruteforce(int* px , int num_p,point* players){
    double mindist = INFINITY;

    for (int i = 0; i < num_p; i++)
    {
        for (int j = 0; j < num_p; j++)
        {   
            if(i != j){
                double dist = distance(players[px[i]],players[px[j]]);
                if (dist < mindist)
                {
                    mindist = dist;
                }
            }
        }
    }
    return mindist;
    
}

double findClosest(int* px, int* py, point* players ,int num_p){
    int i,j;

    pr("Iterations with : %d things\n",num_p);
    if (num_p <= 2)
    {
        return bruteforce(px,num_p,players);
    }

    int lh = num_p / 2;
    int rh = lh;
    if(num_p % 2 != 0)
        rh = lh+1;
    
    int *ly = malloc(lh * sizeof(int));
    int *ry = malloc(rh * sizeof(int));
    int *lx = malloc(lh * sizeof(int));
    int *rx = malloc(rh * sizeof(int));
    if (!ly || !ry || !lx ||!rx) {
        // somethings fucked
        return -1.0;
    }

    memcpy(ly, py, lh * sizeof(int));
    memcpy(ry, py + lh, rh * sizeof(int));
    memcpy(lx, py, lh * sizeof(int));
    memcpy(rx, py + lh, rh * sizeof(int));

    double d1 = findClosest(lx, ly, players, lh);
	double d2 = findClosest(rx, ry,players, rh);
    
    pr("%f : %f\n",d1,d2);

    double d = min(d1,d2);
    pr("initial distance :%f\n",d);

    point** sy = malloc(num_p * sizeof(point*));
    int sy_lenght = 0;


    for (i = 0; i < num_p; i++) {
        pr("1: %d\n",i);
        if(lh != py[i]){
            point* temp_player1 = &players[lh];
            point* temp_player2 = &players[py[i]];
            if( temp_player1->x_cord - temp_player2->x_cord < d){
                sy[sy_lenght] = temp_player2;
                sy_lenght++;
                /*(point *)
                if(listhead == NULL){
                    listhead->p = &players[py[i]];
                }else{
                    tempList->next = listhead;
                    tempList->p = &players[py[i]];
                    listhead = tempList;
                }
                */
            }
        }
	}

    for (i = 0; i < sy_lenght; i++)
    {   
        int p;
        if(sy_lenght < i +8)
            p=sy_lenght;
        else
            p= i+8;
        
        for (j = i+1; j < p; j++)
        {
            pr("Points are %d and %d\n",sy[i]->index,sy[j]->index);
            //double temp_d = distance(*sy[i],*sy[j]);
            long xd = sy[i]->x_cord - sy[j]->x_cord;
			long yd = sy[i]->y_cord - sy[j]->y_cord;
            pr("Distances: %d and %d\n",xd,yd);
			double distance = sqrt((double)(xd*xd+yd*yd));

            if (distance < d)
                d = distance;
                pr("New minDist: %f\n",d);
        }
        
        

    }
    
    pr("A return value: %f\n",d);
    free(ly);
    free(lx);
    free(ry);
    free(rx);
    free(sy);
    return d;

}

int main(int argc, char *argv[])
{
    FILE *in; /* input file set to stdin	*/
    int p;    /* number of people.		*/
    
    progname = argv[0]; /* name is a string in argv[0]. */
    in = stdin;         /* same as System.in in Java.	*/

    scanf("%d", &p);

    pr("Number of points: %d\n", p);

    point *players = inputPoints(p);

    int* px = (int*) malloc(p*sizeof(int));
    int* py = (int*) malloc(p*sizeof(int));

    for (int i = 0; i < p; i++)
    {
        px[i] = i;
        py[i] = i;
    }
    
    mergeSort(px, 0, p - 1, 1,players);
    mergeSort(py, 0, p - 1, 0,players);

    if(PRINT){
        for (int i = 0; i < p; i++)
        {
            printf("Index: %d  X_cord: %d  Y_cord: %d\n",players[i].index,players[i].x_cord,players[i].y_cord);
        }
    }

    double mindist = findClosest(px,py,players,p);
    printf("%f",mindist);

    return 0;
}