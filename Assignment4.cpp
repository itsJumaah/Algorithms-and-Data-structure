//Bilal Jumaah 12232659

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

template <class T>
class List {
	public:
		List();
		~List();
		void AddtoFront(T newthing);
		bool FirstItem(T & item);
		bool NextItem(T & item);
		void Print();
		void PrintReversed();
	private:
		struct Node {
		T data;
		Node *next;
		Node *prev;
	};
	Node *front, *rear, *current;
};

template <class T>
List<T>::List(): front(NULL), rear(NULL), current(NULL) {
}

template <class T>
List<T>::~List() {
}

template <class T>
void List<T>::AddtoFront(T newthing) {
	Node *temp;
	temp = new Node;
	temp->data = newthing;
	temp->next = front;
	temp->prev = NULL;
	if(front != NULL) front->prev = temp;
	front = temp;
	if(rear == NULL) rear = temp;
}

template <class T>
bool List<T>::FirstItem(T & item) {
	if(front == NULL) { return false; }
	item = front->data;
	current = front;
	return true;
}

template <class T>
bool List<T>::NextItem(T & item) {
	if(current == NULL) { return false; }
	current = current->next;
	if(current == NULL) { return false; }
	item = current->data;
	return true;
}

template <class T>
void List<T>::Print(){
	Node *temp = front;
	while(temp != NULL){
		cout << temp->data;
		temp = temp->next;
	}
	cout << endl;
}

template <class T>
void List<T>::PrintReversed(){
	Node *temp = rear;
	while(temp != NULL){
		cout << temp->data;
		temp = temp->prev;
	}
	cout << endl;
}

class BigNumber {
private:
	List <int> L;
public:  
  BigNumber();
  ~BigNumber();
  void ReadFromString (string decstring);
  void PrintBigNumber (int x);
  void AddBigNumbers(BigNumber B1,BigNumber B2);
};

BigNumber::BigNumber(){
}

BigNumber::~BigNumber(){
}

void BigNumber::ReadFromString (string decstring) {
   for(int i = 0; i < decstring.size(); i++) {
     if(decstring[i] != '\n' && decstring[i] != '\r'){
         int temp = decstring[i] - 48;
		   L.AddtoFront(temp); 
      }
   } 
}

void BigNumber::PrintBigNumber (int x) {
	if(x == 3) L.Print();
	else L.PrintReversed();
}

void BigNumber::AddBigNumbers(BigNumber B1,BigNumber B2) {
	bool ok1, ok2;
	int sum, num1, num2, carry = 0;
	
   ok1 = B1.L.FirstItem(num1);
	ok2 = B2.L.FirstItem(num2);
	
	while(ok1 || ok2){ 
		if(!ok1) num1 = 0;
		if(!ok2) num2 = 0;
		sum = num1 + num2;
		sum = sum + carry;
		L.AddtoFront(sum % 10);
		carry = sum / 10;
		if(ok1) ok1 = B1.L.NextItem(num1);
		if(ok2) ok2 = B2.L.NextItem(num2); 
	}
	if(carry > 0) L.AddtoFront(carry);
}

BigNumber B1,B2,RES;

int main(int argc, char ** argv){
  string numberstring;
  int stringseq = 0;
  ifstream input_file;
  if(argc == 2) input_file.open(argv[1]);
  else{cout << "cannot read the file " << argv[1] << endl; exit(0);}
  while(!input_file.eof()){
    getline(input_file,numberstring);
    if(!input_file.eof()){
      if(stringseq == 0){
        B1.ReadFromString(numberstring);
        stringseq = 1;
      }
      else B2.ReadFromString(numberstring);
    }
  }
  B1.PrintBigNumber(1);
  cout << "+" << endl;
  B2.PrintBigNumber(2);
  cout << "=" << endl;
  RES.AddBigNumbers(B1,B2);
  RES.PrintBigNumber(3);
}
