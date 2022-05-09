#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

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
typedef struct point point;

struct point{
    int x_cord;
    int y_cord;
    int index;

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



float distance(point point1,point point2){
    return sqrt((point1.x_cord - point2.x_cord)^2 + (point1.y_cord - point2.y_cord)^2);
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

float bruteforce(int* px , int num_p,point* players){
    float min = INFINITY;

    for (int i = 0; i < num_p; i++)
    {
        for (int j = 0; j < num_p; j++)
        {
            float dist = distance(players[px[i]],players[px[j]]);
            if (dist < min)
            {
                min = dist;
            }
        }
    }
    return min;
    
}

float findClosest(int* px, int* py, point* players ,int num_p){

    if (num_p <= 3)
    {
        return bruteforce(px,num_p,players);
    }

    int mid = num_p / 2;
    
    int
    

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

    for (int i = 0; i < p; i++)
    {
        printf("%d,\n",px[i]);
    }
    


    return 0;
}