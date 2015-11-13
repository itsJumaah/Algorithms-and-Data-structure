////////////////   159201   ///////////////////////////////////
//SAMPLE CODE FOR ASSIGNMENT 4 - Big Numbers
//2012 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

/////// PART A
template <class T>
class List 
{
private:
  struct Node {
	 T data;
	 Node *next;
  };
  Node *front, *current;
  int size; //number of elements on the list

public:
  List();
  ~List();
  void AddtoFront(T newthing); //add a digit to the front
  void AddtoBack(T newthing); //add a digit to the back of the list
  bool FirstItem(T& item); //retrieve first digit, returns false if empty
  bool NextItem(T& item); //retrive next digit, returns false if no more digits availanle
  int length() const { return size; } //return size of the list
  void clear(); //clear out list
  void assign(List<T>& l); //copy elements from another list
};


template <class T>
List<T>::List():size(0) 
{
  front = NULL;  current = NULL;
}

template <class T>
List<T>::~List() 
{
    clear();
}

//copy elements form another list
template<class T>
void List<T>::assign(List<T>& l)
{
    T val;

    clear();
    if(!l.length()) //if the other list is empty, leave our list empty
        return;
    l.FirstItem(val); //get the first foreign item
    do
    {
        //Rather than using slow AddtoBack we duplicate its functionality by using current as a temporary
	//pointer to the last element added
        Node *temp=new Node;
        temp->next=NULL;
	temp->data=val;
	if(!front)
	{
	    //list is empty, simply set the head of the list to the new elements
	    front=temp;
	}
	else
	{
	    current->next=temp; //link last element with the new one
	}
	current=temp;
	size++;
    }
    while(l.NextItem(val)); //traverse until all elements are seen
    current=NULL;
}

//remove all elements from the list and free memory
template<class T>
void List<T>::clear()
{
    while(front)
    {
        Node *t=front->next;
	delete front;
	front=t;
    }
    front=NULL;
    current=NULL;
    size=0;
}

template <class T>
void List<T>::AddtoFront(T newthing) 
{
  Node *temp;
  temp = new Node;
  temp->data = newthing;
  temp->next = front;
  front = temp;
  size++;
}

template <class T>
void List<T>::AddtoBack(T newthing) 
{
  Node *temp;
  temp = new Node;
  temp->data = newthing;
  temp->next = NULL;
  if(!front)
  {
      front=temp;
  }
  else
  {
      Node *p=front;
      while(p->next)
          p=p->next;
      p->next=temp;
  }
  size++;
}


template <class T>
bool List<T>::FirstItem(T & item) 
{
  if (!front) 
  { 
      return false; 
  }
  current = front;
  item = front->data;
  return true;
}



template <class T>
bool List<T>::NextItem (T & item) 
{
  if (current != NULL) 
      current = current->next;
  if (current == NULL) 
      return false;
  item = current->data;
  return true;
}

/////// PART B
class BigNumber 
{
private:
    List<int> list;

public:
    BigNumber();
    ~BigNumber();
    void ReadFromString(char * decstring );
    void PrintBigNumber();
    void AddBigNumber(BigNumber& b1); //Add another big number to the current one
    void AddBigNumbers(BigNumber& b1,BigNumber& b2); //add two big numbers, store the result in the current one
    void Assign(BigNumber& b); //Assign all digits from another big number
};

BigNumber::BigNumber()
{
}

BigNumber::~BigNumber()
{
}

void BigNumber::ReadFromString(char * decstring ) 
{
    list.clear();

    //remove leading zeroes
    while(*decstring && *decstring=='0')
        decstring++;

    while(*decstring)
    {
        if(*decstring<'0' || *decstring>'9')
	     break;  //non-digit character, stop processing
	list.AddtoFront(*decstring-48); //add another digit
	decstring++;
    }
}

void BigNumber::PrintBigNumber () 
{
    char *str=new char[list.length()+1]; //create a string to hold the output since we have to reverse the string
    int i=list.length()-1;

    if(list.length()>0)
    {
        str[list.length()]=0;
        int val;
	list.FirstItem(val);
	do
	{
	    str[i--]=val+48;
	}
	while(i>=0 && list.NextItem(val));
	cout << str;
    }
    else
    {
        cout << "0";
    }
    delete [] str;
}

void BigNumber::AddBigNumber(BigNumber& b)
{
    int t=0; //carry value
    int v1=0,v2=0;
    List<int> ltmp;

    //We will traverse both lists for as long as there is something in one of the lists
    bool b1=list.FirstItem(v1);
    bool b2=b.list.FirstItem(v2);

    while(b1 || b2)
    {
        v1+=t+v2; //new value, including carry value from the previous operation
        ltmp.AddtoBack(v1%10);
	t=v1/10; //calculate carry value
	v1=v2=0;
        b1=list.NextItem(v1);
        b2=b.list.NextItem(v2);
    }
    if(t)
        ltmp.AddtoBack(t);
    list.assign(ltmp);
}


void BigNumber::AddBigNumbers(BigNumber& b1,BigNumber& b2)
{
    Assign(b1);
    AddBigNumber(b2);
}

void BigNumber::Assign(BigNumber& b)
{
    list.assign(b.list);
}

/////// PART C

BigNumber B1,B2,RES;

int main (int argc, char ** argv) 
{
  //use command line arguments
  if(argc!=3){printf("usage: executable number1 number2\n");exit(0);}
  B1.ReadFromString(argv[1]);
  B2.ReadFromString(argv[2]);
  //print
  cout << endl<< "Add the following numbers " << endl;
  B1.PrintBigNumber();
  cout << " + ";
  B2.PrintBigNumber();
  cout << " = " << endl;
  //compute the addition
  RES.AddBigNumbers(B1,B2);
  //print the result
  RES.PrintBigNumber();
  cout << endl;
  return 0;
}
