//Bilal Jumaah 12232659

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

struct Node {
	int data;
	Node *next;
};
//-----------------------------
class Queue {
	private:
		Node *front, *rear;
		int counter;
	public:
		Queue();
	   ~Queue();
	void Join(int newthing);
	void Leave();
	int Front();
	bool isEmpty();
	void Print();
	int Length();
};
//-----------------------------
Queue::Queue(): counter(0) {
  front = NULL, rear = NULL;
}

Queue::~Queue() {
	
}
//-----------------------------
#define TIMEDELAY 3
#define N 128

int OutQueues_current[N];
int Congestion_Size[N];

Queue InputQueues[N];
Queue OutputQueues[N];
//-----------------------------
void init_simulation () {
	for (int a = 0; a < N; a++) {
		OutQueues_current[a] = 0;
		Congestion_Size[a] = 0;
	}
}

int sum_elements_array (int array[]) {
	int sum = 0;
	for (int a = 0; a < N; a++) {
		sum = sum + array[a];
	}
	return sum;
}

void Queue::Join(int newthing) {
	Node *temp;
	temp = new Node;
	temp -> data = newthing;
	temp -> next = NULL;
	if (rear != NULL) { 
		rear -> next = temp; 
	}
	rear = temp;
	if (front == NULL) { 
		front = temp; 
	}
	counter++;
}

void Queue::Leave() {
	Node *temp;
	if (front == NULL) {
		return; 
	}
	temp = front;
	front = front -> next;
	if (front == NULL) { 
		rear = NULL; 
	}
	delete temp;
	counter--;
}

int Queue::Front() {
  if (front != NULL) {
	  return front -> data;
	} 
	return 0;
}

bool Queue::isEmpty() {
  if (front == NULL) { 
	  return true; 
	}
	return false;
}

void Queue::Print() {
  if (front == NULL) { 
	  return;
  }
  Node *temp = front;
  printf ("Listing the queue:  ");
  while (temp != NULL){
    printf ("%d ", temp -> data);
    temp = temp -> next;
  }
  printf("\n");
}

int Queue::Length() {
	return counter;
}
//-----------------------------
int number_of_ports = 0;

int main (int argc, char** argv) {
	int portnumber = 0;
	int destination = 0;
	string expression;
	string geninput;
	ifstream input_file;
	if (argc != 2) { 
		cout<< "Type a file name. " << endl << argv[1] << endl; 
		exit (0);
	}
	input_file.open (argv[1]);
	if (input_file.is_open () == false) {
		cout << "Could not read file: " << endl << argv[1] << endl; 
		exit (0);
	}
	string token;
	while (!input_file.eof ()) {
		getline (input_file, expression);
		stringstream line (expression);
		if( input_file.eof ()) {
			break;
		}
		if (expression[0] == '#') {
			continue;
		}
		if (expression[0] == 'P') {
			getline(line, token,' ');
			getline(line, token,' ');
			number_of_ports = atoi (token.c_str ());
			continue; 
		}
		portnumber++;
		while (getline (line, token,' ')) {
			destination = atoi (token.c_str ());
			if (destination < 0 || destination > number_of_ports || number_of_ports < portnumber) {
				cout << "ERROR in the format of the text file" << endl; 
				exit (0);
			}
			InputQueues[portnumber-1].Join(destination);
		}
	}
	init_simulation ();
	unsigned long int clock = 0;
	unsigned long int currentsum = 99999999;
	portnumber = 0;
	while (currentsum > 0) {
		if (InputQueues[portnumber].isEmpty() == false) {
			OutputQueues[InputQueues[portnumber].Front()-1].Join(InputQueues[portnumber].Front()-1);
			InputQueues[portnumber].Leave();
		}
		portnumber++;
		if (portnumber > (number_of_ports - 1)) portnumber = 0;
		clock++;
		if (clock % (TIMEDELAY * number_of_ports) == 0 && clock != 0) { 
			for (int a = 0; a < number_of_ports; a++) {
				OutputQueues[a].Leave();
			}
		}
		int temp = 0;
		for (int a = 0; a < number_of_ports; a++) {
			temp = temp + OutputQueues[a].Length();
			OutQueues_current[a] = OutputQueues[a].Length();
		}
		currentsum = temp;
		if (currentsum > sum_elements_array (Congestion_Size)) {
			for (int a = 0; a < number_of_ports; a++) {
				Congestion_Size[a] = OutQueues_current[a];
			}
		}
	}
	for (int a = 0; a < number_of_ports; a++) {
		cout << "output port " << a+1 << ": " << Congestion_Size[a] << " packets" << endl; 
	}
}
