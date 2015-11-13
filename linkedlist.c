#include <stdio.h>
#include <string.h>

struct Node {
	char name[40];
	int num;
	Node *next;
};

void addNode(int inputNum, char *inputName, Node **head);
void delNode(char *name, Node **head);
int searchNode(char *name, Node *head);
void display(Node *head);

int main(int argc, char *argv[]) {
	Node *head;
	head = NULL;
	char choice, name[40];
	int num=0, number=0;
	while(true) {
		printf("Choose one:\n");
		printf("A. Add number.\nB. Delete number.\nC. Search for number.\nD. Print the list.\n");
		scanf("%c", &choice);
		getchar();
		if(choice == 'A' || choice == 'a') {
			printf("Please enter the name: ");
			gets(name);
			printf("Please enter the number: ");
			scanf("%d", &num);
			getchar();
			addNode(num, name, &head);
		}
		if(choice == 'B' || choice == 'b') {
			printf("Please enter the name you want to delete: ");
			gets(name);
			delNode(name, &head);
			printf("%s has been deleted!\n", name);
		}
		if(choice == 'C' || choice == 'c') {
			printf("Please enter the name: ");
			gets(name);
			number = searchNode(name, head);
			printf("The number of %s is %d\n", name, number);
		}
		if(choice == 'D' || choice == 'd') {
			display(head);
		}
		printf("\n");
	}
}

void addNode(int inputNum, char *inputName, Node **head) {
	Node *temp;
	temp = new Node;
	temp -> num = inputNum;
	//printf("havnt crachsed yet!");
	strcpy(temp -> name, inputName); //temp -> name = inputName;
	temp -> next = *head;
	*head = temp;
}
void delNode(char *name, Node **head) {
	Node *temp, *temp2;
	temp2 = new Node;
	temp = new Node;
	temp = *head;
	while(temp != NULL) {
		if( strcmp(temp -> name, name) == 0) {
			break;
		}
		temp = temp -> next;
	}
	temp2 = *head;
	temp2 -> next = temp -> next;
	delete temp;
}
int searchNode(char *name, Node *head) {
	Node *temp;
	temp = new Node;
	temp = head;
	while(temp != NULL) {
		if( strcmp(temp -> name, name) == 0) {
			break;
		}
		temp = temp -> next;
	}
	return temp -> num;
}
void display(Node *head) {
	Node *temp;
	temp = new Node;
	temp = head;
	while(temp != NULL) {
		printf("%s : %d\n", temp -> name, temp -> num);
		temp = temp -> next;
	}
}
