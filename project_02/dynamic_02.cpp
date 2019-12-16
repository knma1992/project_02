#include <iostream>
using namespace std;

struct node {
	int data;
	node* next;
};

node* node_creation(node* head)
{
	node* temp;
	int N;

	cout << "How many nodes do you want to create?\n\n Amount of nodes: ";
	cin >> N;
	cout << endl;


	temp = head;
	for (int ii = 1; ii <= N - 1; ii++)
	{
		head = new node;		//Creating the node, head points to that node
		head->data = ii;
		temp->next = head;
		head->next = NULL;		//Pointer of the last node contains NULL
		temp = head;
	}
	return(head);
}

void node_print(node* root)
{
	node* temp;
	temp = root;
	cout << "\t";
	while (temp != NULL)
	{
		cout << temp->data << ", ";
		temp = temp->next;
	}
}

node* node_prepend(node* root)
{
	node* temp;
	int N;
	cout << "\nHow many nodes do you want to prepend?\n\n Amount of nodes: ";
	cin >> N;
	cout << endl;

	for (int ii = 0; ii < N; ii++)
	{
		temp = new node;
		temp->data = root->data - 1;
		temp->next = root;
		root = temp;
	}
	return root;
}

node* node_append(node* head)
{
	node* temp;
	int N;
	cout << "\nHow many nodes do you want to append?\n\n Amount of nodes: ";
	cin >> N;
	cout << endl;

	for (int ii = 0; ii < N; ii++)
	{
		temp = new node;
		temp->data = head->data + 1;
		head->next = temp;
		head = temp;
		head->next = NULL;
	}
	return head;
}

void node_insert(node* root)
{
	node* temp, * temp0, * temp1;
	int N, loc;
	cout << "\nAfter which node do you want to insert nodes?\n\n Node location: ";
	cin >> loc;
	cout << endl;
	cout << "\nHow many nodes do you want to insert?\n\n Amount of nodes: ";
	cin >> N;
	cout << endl;

	temp = root;

	for (int ii = 0; ii < loc; ii++)
	{
		temp = temp->next;

	}

	temp0 = temp;
	temp1 = temp->next;

	for (int ii = 0; ii < N; ii++)
	{
		temp = new node;
		temp->data = 20;
		temp0->next = temp;
		temp0 = temp;
	}
	temp->next = temp1;
}

void node_delete(node* root)
{
	node* temp;
	int i=0;
	temp = root->next;
	while (temp != NULL)
	{
		delete root;
		root = temp;
		temp = root->next;
		i++;
	}
	delete root;
	cout << "\n\nAmount of deleted nodes:" << i << "\n";
}

void main(void)
{
	//head: head pointer, root: root pointer, temp: temporary pointer
	node* head, *root;

	//Initialize the first node
	head = new node;
	head->data = 0;
	root = head;

	//Node creation
	(head) = node_creation(head);
		
	//Print nodes
	node_print(root);

	//Prepend nodes
	root = node_prepend(root);

	//Print nodes
	node_print(root);

	//Append nodes
	head = node_append(head);

	//Print the nodes
	node_print(root);

	//Insert nodes
	node_insert(root);

	//Print nodes
	node_print(root);

	//Delete nodes
	node_delete(root);
}