#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int** make_matrix(int n,int m)
{
	int** a;
	int i;
	a = malloc(n* sizeof(int*));
	for (i = 0; i < n; i++)
		a[i] = calloc(m+1, sizeof(int));//why the plus one here?
	return a;
}

typedef struct node_l node_l;

struct node_l
{	
	char letter;
	node_l* next;
};

typedef struct node_n node_n;

struct node_n
{	
	int value;
	int pX;
	int pY; 
};

node_n*** make_m(int n,int m)
{
	node_n*** a;
	int i,j;
	a = malloc(n* sizeof(node_n**));
	for (i = 0; i < n; i++)
		a[i] = calloc(m+1, sizeof(node_n*));//why the plus one here?
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			a[i][j]=calloc(1,sizeof(node_n));
	
	a[0][0]->pX=-1;//is this actually needed
	a[0][0]->pY=-1;//is this actually needed
	for(i=1;i<n;i++){
		a[i][0]->value=i*-4;
		a[i][0]->pX=i-1;
		a[i][0]->pY=0;
	}
	for(i=1;i<m;i++){
		a[0][i]->value=i*-4;
		a[0][i]->pX=0;
		a[0][i]->pY=i-1;
	}
	
	return a;
}

node_l* create_node(char letter)
{
	node_l* p = calloc(1, sizeof(node_l));
	p->letter = letter;
	return p; 
}

int check_letter(char* l, char word)
{	
	int i=0;
	while(word!='\0'){
			if(word==l[i]){
				return i; 
			}	
			i++;
		}
	return -1; //this should never happen and will crash the program. 
}	

int* find_match(char* l, node_l* word, int k)
{	
	//this should reverse the order again, so that the first word in the letter is the smallest. Therefore
	//we have to do the iterating version and not the opt version, as it will not work otherwise. 
	int* list = calloc(k,sizeof(int));
	int i=0;
	node_l* temp = word; 
	while(temp!=NULL){
		list[k-1-i]=check_letter(l,temp->letter); 
		i++;
		temp=temp->next;
	}	
	return list;
	
}

void Opt (node_n*** memory, int** matrix, int* wordOne, int n, int* wordTwo,int m)
{	
	int i,j;
	int a,b,c;
	for(i=1;i<n;i++){
		for(j=1;j<m;j++){
			a=memory[i][j-1]->value-4;
			c=memory[i-1][j]->value-4;
			b=memory[i-1][j-1]->value+matrix[wordOne[i-1]][wordTwo[j-1]];
			if(b>=a && b>=c){
				memory[i][j]->value=b;
				memory[i][j]->pX = i-1;
				memory[i][j]->pY = j-1;
			}else if(a>c){
				memory[i][j]->value=a;
				memory[i][j]->pX = i;
				memory[i][j]->pY = j-1;
			}else{
				memory[i][j]->value=c;
				memory[i][j]->pX = i-1;
				memory[i][j]->pY = j;
			}
		}	
	}	
}

void print1(char* l, int* word, node_n*** memory,int n,int m)
{	
	int pX,pY;
	pX=memory[n][m]->pX;
	pY=memory[n][m]->pY;
	if(pX==-1){
		return; //think this is possible even in a void method as long as we don't return anything.
	}
	print1(l, word, memory, pX,pY);
	if(pX<n){
		char a = l[word[n-1]];
		printf("%c", a);
	}else if(pY<m){
		printf("%c", '*');
	}
}	

void print2(char* l, int* word, node_n*** memory,int n,int m)
{	
	int pX,pY;
	pX=memory[n][m]->pX;
	pY=memory[n][m]->pY;
	if(pX==-1){
		return; //think this is possible even in a void method as long as we don't return anything.
	}
	print2(l, word, memory, pX,pY);
	if(pY<m){
		char a = l[word[m-1]];
		printf("%c", a);
	}else if(pX<n){
		printf("%c", '*');
	}
}	

int main(int argc, char** argv)
{
	//could save all things in arrays instead if I prefered, but linked lists are nicer I think
	int i,j,k,q,count=0; //if things fuck up check the k, count and l, variables
	node_l* letters = NULL; 
	node_l* temp; 
	int t = getchar(); 
	while(t!='\n'){
		if(t!=' '){
			temp = letters; 
			letters = create_node(t);
			letters->next=temp; 
			count++;
		}	
		t=getchar();
	}
	char* l = calloc(count+1, sizeof(char));
	temp = letters;
	
	//making an array for the letters that matches the matrix in order. 
	for(i=0;i<count;i++){
		l[count-1-i]=temp->letter;
		temp=temp->next;
	}	
	l[count]='\0';
	
	int** matrix = make_matrix(count,count);
	for(i=0;i<count;i++){
		for(j=0;j<count;j++){
		scanf("%d\n", &matrix[i][j]);//Why do you have the \n in the scanf func?
		}	
	}
	
	
	scanf("%d\n", &q);
	
	for(i=0;i<q;i++){
		node_l* word1 = NULL;
		node_l* word2 = NULL;
		temp = NULL; 
		t=getchar();
		j=0;
		while(t!=' '&& t!='\n'){
			temp = word1;			
			word1=create_node(t);
			word1->next = temp;
			t=getchar();
			j++;
		}
		//putting the words in a numbered linked list that matches the l array and the matrix
		int* wordOne = find_match(l,word1,j);
		
		t=getchar();
		k=0;
		while(t!=' '&& t!='\n'){
			temp = word2;			
			word2=create_node(t);
			t=getchar();
			word2->next = temp;	
			k++;
		}
		//putting the words in a numbered linked list that matches the l array and the matrix
		int* wordTwo = find_match(l,word2,k);
		
		
		node_n*** memory = make_m(j+1,k+1);
		//put the algoritm here
		//It's done the iterated way
		Opt(memory, matrix, wordOne, j+1, wordTwo, k+1); 
		print1(l, wordOne, memory, j,k);
		printf(" ");
		print2(l, wordTwo, memory, j,k);
		printf("\n");
	}	
}