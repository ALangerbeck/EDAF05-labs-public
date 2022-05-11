#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node_t node_t;

struct node_t //might want the list part to be a seperate struct
{	
	int node;
	long x;
	long y;
	//int size;
	node_t* next;
};

void msortx(node_t** a, int l, int r, node_t** b)
{
	int m, i, j, k;
	
	if((r-l)==0)
		return;
	
	m=l+(r-l)/2;
	msortx(a,l,m,b);
	msortx(a,m+1,r,b);
	memcpy(b+l,a+l,sizeof(node_t*)*(m-l+1));
	memcpy(b+1+m,a+m+1,sizeof(node_t*)*(r-m));
	j=l;
	k=m+1;
	for(i=l;i<=r;i++){
		if(j==m+1)
			a[i]=b[k++];
		else if(k==r+1)
			a[i]=b[j++];
		else if(b[j]->x<b[k]->x)
			a[i]=b[j++];
		else if(b[j]->x==b[k]->x)//if they have the same x value sort after y value
			if(b[j]->y<b[k]->y)
				a[i]=b[j++];
			else 
				a[i]=b[k++];
		else
			a[i]=b[k++];
	}
}

void msorty(node_t** a, int l, int r, node_t** b)
{
	int m, i, j, k;
	
	if((r-l)==0)
		return;
	
	m=l+(r-l)/2;
	msorty(a,l,m,b);
	msorty(a,m+1,r,b);
	memcpy(b+l,a+l,sizeof(node_t*)*(m-l+1));
	memcpy(b+1+m,a+m+1,sizeof(node_t*)*(r-m));
	j=l;
	k=m+1;
	for(i=l;i<=r;i++){
		if(j==m+1)
			a[i]=b[k++];
		else if(k==r+1)
			a[i]=b[j++];
		else if(b[j]->y<=b[k]->y)
			a[i]=b[j++];
		else
			a[i]=b[k++];
	}
}

void mergesort(node_t** Px,node_t** Py, int n)
{
	node_t** temp1; 
	node_t** temp2; 
	
	if(n>0){
		temp1 = calloc(n, sizeof(node_t*));
		temp2 = calloc(n, sizeof(node_t*));
		msortx(Px, 0, n-1, temp1);
		msorty(Py, 0, n-1, temp2);
		free(temp1);
		free(temp2);
	}
}	

void ms(node_t** y, int n)
{	
	node_t** temp;
	
	if(n>0){
		temp = calloc(n, sizeof(node_t*));
		msorty(y, 0, n-1, temp);
		free(temp);
	}
}	

node_t* create_node(int node, long x, long y)
{
	node_t* p = calloc(1, sizeof(node_t));
	p->node = node;
	p->x = x;
	p->y = y;  
	p->next = NULL; 
	return p; 
}

double closest(node_t** Px, int xl, int xr, node_t** Py, int yl, int yr, int n)//check if I really need the left right attributes
{
	int i,j,k;
	double d1,d2;
	double d; 
	j=0;
	k=0;
	if((xr-xl)==0||(xr-xl)==1)//ändra basfallet så att om man har tre eller färre punkter ska man jämföra de med varandra
		return INFINITY;
	
	int m = xl+(xr-xl)/2;
	long x = Px[m]->x;
	long y = Px[m]->y;
	node_t** Ly = calloc(m-yl+1, sizeof(node_t*));
	node_t** Ry = calloc(yr-m, sizeof(node_t*));
	for(i=0; i<n; i++){
		if(Py[i]->x<x){//if other points have the same as the mid point it'll get fucked. 
			Ly[j]=Py[i];
			j++;
		}else if(Py[i]->x==x){
			if(Py[i]->y<=y){
				Ly[j]=Py[i];
				j++;
			}else{
				Ry[k]=Py[i];
				k++;
			}	
		}else{
			Ry[k]=Py[i];
			k++;
		}	
	}
	
	//we need to calculate the float point distance on this on 
	d1 = closest(Px, xl, m, Ly, yl, m, m-yl+1);
	d2 = closest(Px, m+1, xr, Ry, m+1, yr, yr-m);
	if(d1<d2)
		d=d1;
	else
		d=d2;
	
	node_t** Sy = calloc(n, sizeof(node_t*));
	
	long x1;
	long x2;
	j=0;
	if(d==INFINITY){
		x1=-9223372036854775807;
		x2=9223372036854775807;
	}else{
		x1 = x-d;
		x2 = x+d;
	}
	j=0;
	for(i=0; i<n; i++){
		if(Py[i]->x<=x2 && Py[i]->x>=x1){
			Sy[j]=Py[i];
			j++;
		}
	}
	for(i=0;i<j;i++){
		int p; 
		if(j<i+8)
			p=j;
		else 
			p = i+8;
		for(k=i+1;k<p;k++){
			long xd = Sy[i]->x - Sy[k]->x;
			long yd = Sy[i]->y - Sy[k]->y;
			double distance = sqrt(xd*xd+yd*yd);
			if(distance < d)
				d=distance;
		}	
	}	
	return d;
	
}

double closest_points(node_t* list, int n)
{
	node_t** Px = calloc(n, sizeof(node_t*)); 
	node_t** Py = calloc(n, sizeof(node_t*));
	node_t* temp = list; 
	int i = 0; 
	while(temp!=NULL){
		Px[i]=temp;
		Py[i]=temp; 
		temp=temp->next;
		i++;
	}	
	mergesort(Px, Py, n);
	//check if the sorting works properly
	double ans = closest(Px, 0, n-1, Py, 0, n-1, n); 
	free(Px);
	free(Py);
	return ans;
}	


int main(int argc, char** argv)
{
	
	int n, i;
	long x,y; //tried changing this to long hoping that would fix it but it still fucks up
	
	node_t* list = NULL; 
	node_t* temp; 
	
	scanf( "%d\n", &n);
	for(i=0; i<n; i++){
		scanf( "%ld %ld\n", &x, &y);
		temp = create_node(i,x,y);
		temp->next = list;
		list = temp; 
	}	
	double d = closest_points(list, n);
	printf("%.6f\n", d);
	
}