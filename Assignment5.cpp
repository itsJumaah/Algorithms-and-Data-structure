//Bilal Jumaah - 12232659

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

// implement the Tree class here, you can copy the one from week 5 slides
class Tree {
private:
  char data;
  Tree *leftptr, *rightptr;
 
public:
  Tree(char newthing, Tree* L, Tree* R);  // constructor with paramters
  ~Tree() { }
  char RootData() { return data; }  // inline functions
  Tree* Left() { return leftptr; }
  Tree* Right() { return rightptr; }
};

Tree::Tree(char newthing, Tree* L, Tree* R) {
  data = newthing;
  leftptr = L;
  rightptr = R;
}

/* implement your stack here*/
struct Node {
  Tree* data;
  Node *next;
};

class Stack {
private:                         //the data differs from the array
  Node *listpointer;
public:                          //the functions (methods) are identical
  Stack();
  ~Stack();
  void Push(Tree* newthing);
  void Pop();
  Tree* Top();
  bool isEmpty();
};

Stack::Stack() {
// constructor
  listpointer = NULL;
}

Stack::~Stack() {
// destructor

}

//Stack S; //Declare your stack of Tree* here 
void Stack::Push(Tree* newthing) {
// place the new thing on top of the stack
Node *temp;
  temp = new Node;             //same as add node to front of linked-list
  temp->data = newthing;
  temp->next = listpointer;    //NOTE: no overflow problem
  listpointer = temp;
}
void Stack::Pop() {
// remove top item from the stack
Node *p;
  p = listpointer;
  if (listpointer != NULL) {     //        check to avoid underflow
     listpointer = listpointer->next;
     delete p;                //always delete a TEMPORARY variable
  }
}

Tree* Stack::Top() {
// return the value of the top item
  return listpointer->data;  //WARNING: what if listpointer is NULL?
}

bool Stack::isEmpty() {
// returns true if the stack is empty
  if (listpointer == NULL) {
     return true;
  }
  return false;
}

/* implement your recursive funtions for traversals */
void InOrder(Tree *T) { 
	if(T == NULL) { return; } 
	if(T->Left()!=NULL)printf("(");
	InOrder(T->Left()); 
	printf("%c", T->RootData());
	InOrder(T->Right()); 
	if(T->Right()!=NULL)printf(")");
}

void PostOrder(Tree *T) {
	if(T == NULL) { return; }
	PostOrder(T->Left());
	PostOrder(T->Right());
	printf("%c ", T->RootData());
}

Tree *T1, *T2, *T;	
Stack S;

int main( int argc, char** argv ){//get filename from arguments
	char digit;
	char oper;
	char expression[100];
	ifstream input_file;
	if(argc == 2) input_file.open(argv[1]);
	else {printf("The program needs a filename as argument \n");exit(0);}
	/* both operator and digits are of type char */
	while(input_file >> expression){
		if(isdigit(expression[0])){
			sscanf(expression,"%c",&digit);
			//modify here to deal with the Stack
			S.Push(new Tree(expression[0], NULL, NULL));
		}
		else {
			sscanf(expression,"%c",&oper);
			//modify here to deal with the Stack
			T1 = S.Top(); S.Pop();
			T2 = S.Top(); S.Pop();
			S.Push(new Tree(expression[0], T2, T1));
		}
	}
	T = S.Top();
		
	//in-order with parenthesis
	cout << "In-fix:" << endl;
	InOrder(T);

	//post-order
	cout << "\nPost-fix:" << endl;
	PostOrder(T);
	cout << endl;
}
