#include <stdio.h>

//Set supporting class
//Support sets with numbers ranging 0..31
class Set
{
    private:
        unsigned int m_Set; //Set bitmask
    public:
        Set():m_Set(0) 
	{
	}
	~Set()
	{
	}
	//Insert number into the set
	void Insert(unsigned int num)
	{
	    if(num<32) //make sure the number falls into the range
	        m_Set|=(1<<num);
	}
	//Remove one number from the set
	void Remove(unsigned int num)
	{
	    if(num<32)
	        m_Set&=~(1<<num);
	}
	//Returns true if number is the member of the set
	bool Member(unsigned int num)
	{
	    return (m_Set&(1<<num)!=0);
	}
	//returns set power
	int Size()
	{
	    int c=0;
	    unsigned int x=m_Set;
	    //Rather than storing the size of the set
	    //we count the number of bits set
	    while(x)
	    {
	        c++;
		x&=x-1;
	    }
	    return c;
	}
	//Display set in { x, x, x} format
	void Display()
	{
	    bool bSeen=false; //true if the set is not emptu

	    printf("{ ");
	    //display every number that has corresponding bit set
	    for(int i=0;i<32;i++)
	    {
	        if((m_Set&(1<<i))!=0)
		{
		     if(bSeen) //if we have already printed out a number, add ','
		         printf(", ");
	             printf("%d",i);
		     bSeen=true;
		}
	    }
	    printf(" }\n");
	}
	//make the set contain all elements of set X and all elements of set Y (OR)
	void Union(Set& x, Set& y)
	{
	    m_Set=x.m_Set|y.m_Set;
	}
	//make the set contain only elements which appear in set X and in set Y
	void Intersection(Set& x,Set& y)
        {
	    m_Set=x.m_Set&y.m_Set;
	}
};


int main()
{
    Set A,B,C;

    A.Insert(1);A.Insert(2);A.Insert(4);A.Insert(7);
    A.Remove(1);
    printf("A[%d]=",A.Size()); A.Display();
    B.Insert(1);B.Insert(2);B.Insert(6);B.Insert(7);
    B.Remove(7);
    printf("B[%d]=",B.Size()); B.Display();
    A.Member(1);
    B.Member(6);
    C.Union(A,B);
    printf("C[%d]=",C.Size()); C.Display();
    C.Intersection(A,B);
    printf("C[%d]=",C.Size()); C.Display();
    return 0;
}

