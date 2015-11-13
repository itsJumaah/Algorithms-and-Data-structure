//159201 assignment 1 skeleton
//You need to add your own AddNode and PrintLL functions, as well as an AddMatrices function
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
//#include <string>

using namespace std;

struct Node {  //declaration
	int row; //row index
	int column; //column index
	int value; //value 
	Node *next; //link to the next node
};

//Note: linked list shoudl stay sorted per row and per column in a row!


//Add new node to the list
//Allocation of the new node is done by new operator
void add_node(Node **a,int i,int j,int value)
{
    *a=new Node; //allocate new node
    //fill out node paramters
    (*a)->row=i;
    (*a)->column=j;
    (*a)->value=value;
    (*a)->next=NULL;
}

//Print matrix to stdout
//rows and cols must contain matrix dimensions
//NULL matrix is gracefully handled
void print_matrix(Node *a,int rows,int cols)
{
    //check head node validity
    if(!a)
       return;
    //Traverse all cells in matrix of size (rows x cols)
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            //check if the next node references the current cell
            if(a && a->row==i && a->column==j)
            {
                //Yes, we have a match for the cell
                printf("%4d ",a->value);
                a=a->next; //move to the next node/cell
            }
            else
            {
                //no nodes associated with the cell, value is 0
                printf("%4d ",0);
            }
        }
        printf("\n");
    }
}

//Matrix addition
//Returns newly allocated matrix in the form of the linked list
Node *add_matrix(Node *a,Node *b,int rows,int cols)
{
    Node *p=NULL; //new matrix to be returned
    Node **pp=&p; //current element pointer

    //Traverse all cells in both matrices
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            int val=0;
            //check if the current cell matches current a node
            if(a && a->row==i && a->column==j)
            {
                //and if we have corresponding b node - sum them up
                if(b && b->row==i && b->column==j)
                {
                    val=a->value+b->value;
                    b=b->next; //move to the next node in b
                }
                else
                    val=a->value;
                a=a->next; //move to the next node in a
                if(val)
                {
                   //value is non-zero, we need to add the new node
                   add_node(pp,i,j,val);
                   pp=&(*pp)->next; //move the placeholder for the next node
                }
            }
            else if(b && b->row==i && b->column==j)
            {
                //and if we have corresponding a node - sum them up
                if(a && a->row==i && a->column==j)
                {
                    val=a->value+b->value;
                    a=a->next;
                }
                else
                    val=b->value;
                b=b->next;
                if(val)
                {
                   add_node(pp,i,j,val);
                   pp=&(*pp)->next;
                }
            }
        }
    }
    return p; //return new matrix
}

//Read matrix from a text file
void read_matrix(Node* &a, const char *file_name,int *rows=NULL,int *cols=NULL)
{
    //reads a matrix from a file
    int col = 0, row = 0, value = 0;  
    ifstream input;
    Node **curr=&a;

    input.open(file_name);
    if(!input.good())
    {
        cout << "Cannot open file " << file_name << endl;
        exit(0);
    }
    int c;
    string line;
    //reads the first line to get dimensions
    if(input.good())
    {
	    getline(input,line);
	    stringstream sline(line);
	    sline >> row >> col;
    }
    if(rows)
        *rows=row;
    if(cols)
        *cols=col;
    //read matrix 
    for(int i = 0; i < row; ++i)
    {
        if(input.good()) 
        {
		getline(input,line);
		stringstream sline(line);
        	for(int j = 0; j < col; ++j)
                {
		    sline >> value;
	            if(value == 0) continue;
                    //add node
                    add_node(curr,i,j,value);
                    curr=&(*curr)->next;    
          	}
	}
    }
    input.close();
}

int main(int argc,char *argv[]) 
{
	Node *A = NULL;  // ALL linked-lists start empty
        Node *B = NULL;
        Node *C=NULL;    //resulted matrix
        int rows1,cols1;
        int rows2,cols2;
        string file1="matrix1.txt";
        string file2="matrix2.txt";

        if(argc>2)
            file1=argv[1];
        if(argc>3)
            file2=argv[2];
	read_matrix(A, file1.c_str(),&rows1,&cols1);
	read_matrix(B, file2.c_str(),&rows2,&cols2);
        printf("Matrix A:\n");
        print_matrix(A,rows1,cols1);
        printf("Matrix B:\n");
        print_matrix(B,rows2,cols2);
        if(rows1!=rows2 || cols1!=cols2)
           printf("Matrix dimensions do not match!\n");
        else
           C=add_matrix(A,B,rows1,cols1);
        printf("Resulted matrix:\n");
        print_matrix(C,rows1,cols1);
        return 0;
}

