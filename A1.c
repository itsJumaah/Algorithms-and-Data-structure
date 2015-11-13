//Assignment 1 - Unfinished
//You need to add  AddNode and PrintLL functions, as well as an AddMatrices function

#include <stdio.h>
#include <stdlib.h>
typedef struct Node Node;
struct Node {  //declaration
	int row;
	int column;
	int value;
	Node *next;
};

Node *A, *B;  //declaration

void AddNode(Node *&listpointer, int r, int c, int v);

void PrintLL(Node *listpointer, int r, int c);
	

void read_matrix(Node**a, char *file_name){
    //reads a matrix from a file
    
    int col = 0, row = 0, value = 0, nodecount = 0;  
    FILE *input = NULL;
    input = fopen(file_name, "r");
    
    if(input == NULL){
        printf("Cannot open file %s. Exiting.\n", file_name);
        exit(22);
    }
    //reads the matrix dimensions from the first line 
    fscanf(input, "%d %d", &row, &col); 
    
    //read matrix 
    int i; int j;
    for(i = 0; i < row; ++i){
        for(j = 0; j < col; ++j){
	    //reads each value from this row (second line onwards)
            fscanf(input, "%d", &value);
			  
            //if(value == 0) continue;
				if(nodecount < row*col) {
					AddNode(A, i, j, value);
					nodecount++;
				}
				if(nodecount > row*col && nodecount < row*col*2) {
					AddNode(B, i, j, value);
					nodecount++;
				}
				PrintLL(A, row, col);
	    
	    //The next line is for debbuging, it can be commented later
	    //printf("Element at (%d %d) is different than zero and it is: %d \n",i,j,value);
        }
	//the next line is for debbuging purposes, it can be commented out later
	//printf("\n");
    }
    
    fclose(input);
}

int main() {
	A = NULL;  // ALL linked-lists start empty
	B = NULL;
	read_matrix(&A, (char*)"matrix1.txt");
	read_matrix(&B, (char*)"matrix2.txt");
}

void PrintLL(Node *listpointer, int row, int col) {

Node *current;
  current = listpointer;
  while (true) {
    if (current == NULL) { 
		 break;
		}
		int i = 0, j = 0;
		while(i < row){
			printf("%d", current->value);
			i++;
			//current = current->next;
		}
		printf("\n");
		if(j = col){
				return;
		}
		current = current->next;
	}
}



void AddNode(Node *&listpointer, int r, int c, int v) {
	// adds a new node to the front of the list
  Node *temp;
  temp = new Node;
  temp->row = r;
  temp->column = c;
  temp->value = v;
  temp->next = listpointer;
  listpointer = temp;
}