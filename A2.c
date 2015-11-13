//aassignment 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
 
struct Node {
  int number;
  char oper;
  Node *next;
};
 
class Stack {
private:                        
  Node *listpointer;
public:                        
  Stack();
  ~Stack();
  void Push(int nextnum);
  void Pop();
  int Top();
};
 
Stack::Stack() {
// constructor
  listpointer = NULL;
}
 
Stack::~Stack() {
// destructor
 
}
 
int result = 0;
 
int calc(int a, int b, char e);
 
 
int main(int argc, char** argv ){//get arguments from command line, i.e., yourexec filename
        int op1, op2, number;
        char oper;
        char file_name[100];
        char expression[100];
        Stack A;
        FILE *input;
        if(argc==2){
                strcpy(file_name, argv[1]);
        }
        else exit(0);
        input = fopen(file_name, "r");
        if(input == NULL){
          printf("Cannot open file %s. Exiting.\n", file_name);
          exit(0);
        }
 
        while(!(feof(input)) ){
                fgets(expression,90,input);
                if(feof(input)) break;
                if(isdigit(expression[0])){
                        sscanf(expression,"%d",&number);
                        printf("reading number %d \n",number);
                       
                        A.Push(number);
                        //modify here to deal with the Stack
                        //PUSH number
                }
                else {
                        if(expression[0]=='+' || expression[0]=='-'|| expression[0]=='/'||expression[0]=='*') {
                        sscanf(expression,"%c",&oper);
                        printf("reading operator %c \n",oper);
 
                        op2 = A.Top();
                                //looks at top of the stack and puts it in op2
                        A.Pop();
 
                        op1 = A.Top();
                                //looks at top of the stack and puts it in op1
                        A.Pop();
                        calc(op2, op1, oper);
                        //compute result
                        A.Push(result);
                        //PUSH result
                        }
                }
        }
        printf("Result: %d\n", A.Top());
       
        //the last element of the stack should be the final answer...
}
 
 
void Stack::Push(int nextnum) {
// place the new thing on top of the stack
Node *temp;
  temp = new Node;             //same as add node to front of linked-list
  temp->number = nextnum;
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
 
int Stack::Top() {
// return the value of the top item
        if (listpointer == NULL) {
                printf("The stack is empty");
     return -1;
  }
  return listpointer->number;  //WARNING: what if listpointer is NULL?
}
 
 
//BILAL please change this function
int calc(int a, int b, char e) {
  if(e =='+') {
          result = a + b;
          return result;
  }
  if (e =='-') {
          result = a - b;
          return result;
  }
  if (e =='/') {
          result = a/b;
          return result;
  }
  if (e =='*') {
          result = a*b;
          return result;
  }
  printf("No operation");
  exit(0);
}