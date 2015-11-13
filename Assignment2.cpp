// Bilal Jumaah 12232659

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

struct Node {
	int data;
	Node *next;
};

class Stack {
	private:
		Node *listpointer;
	public:
		Stack();
		~Stack();
	void push(int newthing);
	void pop();
	int top();
	bool isEmpty();
};

Stack::Stack() {
	listpointer = NULL;
}

Stack::~Stack() {
	
}

//--------------------------------
void Stack::push(int newthing) {
	Node *temp;
	temp = new Node;
	temp -> data = newthing;
	temp -> next = listpointer;
	listpointer = temp;
}

void Stack::pop() {
	Node *p;
	p = listpointer;
	if (listpointer != NULL) {
		listpointer = listpointer -> next;
		delete p;
	}
}

int Stack::top() {
	return listpointer -> data;
}

bool Stack::isEmpty() {
	if (listpointer == NULL) {
		return true;
	}
	return false;
}

//--------------------------------------------------------
int main (int argc, char** argv) {
	Stack S;
	string e;
	int op1 = 0, op2 = 0, number = 0, result = 0; 
	char op;
	
	ifstream input_file;
	if (argc != 2) {
		cout<< "needs a filename as argument  " << endl;
		exit(0);
	}
	input_file.open (argv[1]);
	if (!input_file.good()) {
		cout<< "cannot read file " << argv[1] << endl; 
		exit(1);
	}
	while (!input_file.eof()) {
		getline (input_file, e);
		//if (expr[0] == ' ') continue;
		if (isdigit (e[0])){
			stringstream line (e);
			line >> number;
			cout << "reading number " << number << endl;
			S.push (number);
		}
		if (e[0]=='+'||e[0]=='-'||e[0]=='*'||e[0]=='/') {
			stringstream line(e);
			line >> op;
			cout << "reading operator " << op << endl;
			if (S.isEmpty() == false) {
				op2 = S.top();
				S.pop();
			}
			if (S.isEmpty() == false) {
				op1 = S.top(); 
				S.pop();
			}
			else {
				cout << "too many operators" << endl;
				exit(2);
			}
			if (op == '+') { result = (op1 + op2); }
			if (op == '*') { result = (op1 * op2); }
			if (op == '-') { result = (op1 - op2); }
			if (op == '/') { result = (op1 / op2); }
			S.push (result);
		}
	}
	result = S.top();
	S.pop();	
	if (!S.isEmpty()) { cout << "too many numbers" << endl; }
	else { cout << "The result is " << result << endl; }
}

