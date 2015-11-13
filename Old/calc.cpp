#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


using namespace std;


//Tree node structure
struct Node
{
    Node(const std::string& s,Node *l,Node *r):str(s),pLeft(l),pRight(r) {}
    ~Node() {}

    std::string str; //node content - id value or op
    Node *pLeft,*pRight; //pointers to subtrees
};


//Stack class holder
class Stack
{
    private:
        //stack element structure
        struct Element
	{
	    Node *pNode; //storage for th enode
	    Element *pNext; //next element on the stack
	};
	Element *pHead;
    public:
        Stack():pHead(NULL)
	{
	}
	~Stack()
	{
	    while(pHead)
	    {
	        Element *p=pHead->pNext;
		delete pHead;
		pHead=p;
	    }
	}
	//push new tree node to the stack
	void push(Node *p)
	{
	    Element *pEl=new Element; //create new stack element
	    pEl->pNode=p; 
	    pEl->pNext=pHead; //link to the current head
	    pHead=pEl; //advance head
	}
	//Pop stack element - returns NULL if stack is empty
	Node *pop()
	{
	    Node *p;

	    if(!pHead)
	        return NULL;
	    p=pHead->pNode;
	    Element *pp=pHead->pNext;
	    delete pHead;
	    pHead=pp;
	    return p;
	}

};


//Read epxression from the file and return tree root if success or NULL if read fails
Node *SetUp(FILE *f)
{
    char str[4096];
    char *p=str;
    Stack st;

// Read string until we get non-empty one
    while(fgets(str,4095,f))
    {
        str[strlen(str)-1]=0;
	p=str;
	//skip blanks
	while(*p && *p<=' ') p++;
	if(*p)
	    break;
    }
    //go char by char and single out string elements
    while(*p)
    {
        //skip blanks
	while(*p && *p<=' ') p++;
        char *tmp=p;
	switch(*p)
	{
	    case '+':
	    case '-':
	    case '*':
	    case '/':
	        //This is an operation
		{
		    Node *n1=st.pop();
		    Node *n2=st.pop();
		    if(!n1 || !n2)
		    {
		        printf("Expression has a problem - not valid\n");
			return NULL;
		    }
		    st.push(new Node(string(p,1),n1,n2));
		}
		p++;
		break;
	    default://this is a number or id
	        //find the boundary of the next element
	        while(*tmp && isalnum(*tmp)) tmp++;     
	        st.push(new Node(string(p,tmp-p),NULL,NULL));
		p=tmp;
		break;
	}
    }
    return st.pop();
}

//Infix traversal - recursive
void TraverseInfix(Node *pRoot)
{
    bool brack=false;

    if(!pRoot)
        return;
    //Check if we need brackets
    if(pRoot->pLeft && (pRoot->str[0]=='+' || pRoot->str[0]=='-'))
    {
        brack=true;
	printf("( ");
    }
    TraverseInfix(pRoot->pLeft);
    printf(" %s ",pRoot->str.c_str());
    TraverseInfix(pRoot->pRight);
    if(brack)
    {
        printf(" ) ");
    }
}

void TraversePostorder(Node *pRoot)
{
    if(!pRoot)
        return;
    TraversePostorder(pRoot->pLeft);
    TraversePostorder(pRoot->pRight);
    printf(" %s ",pRoot->str.c_str());
}

int main(int argc,char *argv[])
{
    FILE *f=stdin;
    Node *pRoot;
 
    if(argc>1)
    {
        f=fopen(argv[1],"rt");
	if(!f)
	{
	    printf("Unable to open input file %s\n",argv[1]);
	    return -1;
	}
    }
    pRoot=SetUp(f);
    if(argc<2)
        fclose(f);

    printf("Infix traversing:\n");
    TraverseInfix(pRoot);
    printf("\n");
    printf("Postorder traversing:\n");
    TraversePostorder(pRoot);
    printf("\n");
    return 0;
}

