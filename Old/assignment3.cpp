#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


//Queue processing
class Queue
{
    public:
        Queue():pRoot(NULL),pLast(NULL),nCount(0) {}
	~Queue() { Empty(); }

        //Remove all elements from the queue
	void Empty()
	{
	    //loop while list is not empty
            while(pRoot)
	    {
	         Node *p=pRoot->next;
		 delete pRoot;
		 pRoot=p;
	    }
	    pRoot=NULL;
	    pLast=NULL;
	    nCount=0;
	}
 
        //add one element to the end of the list
	void push(int id)
	{
	    Node *p=new Node; //create new node
	    p->id=id;
	    p->next=NULL; //no more nodes after
	    //Check if we need to link the existing last node to
	    //the newly created one
            if(pLast)
	        pLast->next=p;
	    //advance last node
            pLast=p;
	    //check if the queue was empty - set the first node if it was
	    if(!pRoot)
	        pRoot=p;
	    nCount++; //increase elements count
	}

	//remove one element from the queue and return its id
	int pop()
	{
	    int ret=-1;

	    //if queue is not empty
	    if(pRoot)
	    {
	        ret=pRoot->id; //id to return
		Node *p=pRoot->next; //advance to the next node
		if(pLast==pRoot)
		    pLast=NULL; //the only case when pRoot=pLast is when there is 1 element only
		delete pRoot; 
		pRoot=p; //advance root
		nCount--; //decrease number of elements
	    }
	    return ret;
	}

        //return queue length
	int count() { return nCount; }

    private:
        struct Node //Queue node structure
	{
	    int id; 
	    Node *next; //pointer to the next element/node
	};
	Node *pRoot; //head of the queue
	Node *pLast; //tail of the queue
	int nCount; //Number of elements
};


//Number of queues for the intersection
#define QUEUES 2

//Intersection handling class
class Intersection
{
    public:
        Intersection():CarLeaveTick(10),CurrentTime(0),id(1),CurrentGreenQueue(0)
	{
	    CarAdd[0]=18;
	    CarAdd[1]=22;
	    Phasing[0]=40;
	    Phasing[1]=30;
	}
	~Intersection() {}

        //Process next timer tick
	void Tick()
	{
	    int i;

            //First add new cars to the queues if required
	    for(i=0;i<QUEUES;i++)
	    {
	        if(!(CurrentTime%CarAdd[i]))
		    q[i].push(id++);
	    }
	    //Now check if a car has to leave the green queue
	    if(CurrentTime && !(CurrentTime%CarLeaveTick) && q[CurrentGreenQueue].count()>0)
	    {
	        int p=q[CurrentGreenQueue].pop();
	    }
            //Check if phasing is to change
	    if(CurrentTime && !(CurrentTime%Phasing[CurrentGreenQueue]))
	        CurrentGreenQueue=(CurrentGreenQueue+1)%QUEUES;
	    CurrentTime++; //increase time
	}
	//returns current time
	int time() const { return CurrentTime; }

	//returns queue lenght for queue n
	int QueueLength(int n) { return (n>=0 && n<QUEUES?q[n].count():0); }

	//set phasing for the requested queue n
	void SetPhasing(int q,int phas) { Phasing[q]=phas; }

	//set car addition rate for the requested queue n
	void SetCarAdd(int q,int val) { CarAdd[q]=val; }

    private:
        int CarLeaveTick; //Car leave rate
        int CarAdd[QUEUES]; //Car addition rate
        Queue q[QUEUES]; //Queues for the intersection
	int Phasing[QUEUES]; //Phasing values
	int CurrentTime;
	int id; //next car id
	int CurrentGreenQueue; //Current queue in green state
};


int Q1phase = 30;//initial attempt
int Q2phase = 40;//initial attempt
const int Q1arrive = 18;//fixed 
const int Q2arrive = 22;//fixed
const int leave_rate = 10;//fixed, one car leaves either queue every 10 seconds

int main(int argc, char **argv) 
{
    Intersection isec;

    if(argc!=3) 
    {
        printf("needs: Q1phase Q2phase\n"); 
	exit(0); 
    }
    Q1phase=atoi(argv[1]);
    Q2phase=atoi(argv[2]);
    if(Q1phase < 30 || Q2phase < 30) 
    {
        printf("Minimum time for each queue to be closed is 30 seconds\n"); 
	exit(0);
    }
    isec.SetPhasing(0,Q1phase);
    isec.SetPhasing(1,Q2phase);
    isec.SetCarAdd(0,Q1arrive);
    isec.SetCarAdd(1,Q1arrive);
    while(isec.time()<=7200)
    {
        isec.Tick();
    }

    printf("Queue 1 length: %d\n",isec.QueueLength(0));
    printf("Queue 2 length: %d\n",isec.QueueLength(1));
    return 0;
}
