#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

struct Node {
	int data;
	Node *next;
};
typedef Node *links;
Node *head = NULL;
void insert_at_beginning(int x)
{
	links temp = head;
	links newhead = new Node;
	newhead->data = x;
	newhead->next = temp;
	head = newhead;
}

void insert_at_ending(int x)
{
	links temp = head;
	if (!temp)
	{
		return;
	}
	while (temp->next)
	{
		temp = temp->next;
	}
	links newnode = new Node;
	newnode->data = x;
	newnode->next = NULL;
	temp->next = newnode;
}

void insert_after(int x, int y)
{
	links temp = head;
	if (!temp)
	{
		return;
	}
	if (temp->data == x)
	{
		links newnode = new Node;
		newnode->data = y;
		newnode->next = temp->next;
		temp->next = newnode;
		return;
	}
	if (!temp->next)
		return;
	while (temp->next->next&&temp->next->data != x)
	{
		temp = temp->next;
	}
	if (temp->next&&temp->next->data == x)
	{
		links newnode = new Node;
		newnode->data = y;
		newnode->next = temp->next->next;
		temp->next->next = newnode;
		return;
	}
	else
		return;
}

void delete_node(int x)
{
	links temp = head;
	if (!temp)
	{
		return;
	}
	if (temp->data == x)
	{
		head = temp->next;
		free(temp);
		return;
	}
	while (temp->next&&temp->next->data != x)
	{
		temp = temp->next;
	}
	if (temp->next&&temp->next->data==x)
	{
		links anode = temp->next;
		temp->next = temp->next->next;
		free(anode);
	}
	return;
}

void print(int n)
{
	links temp = head;
	if (!temp)
		return;
	if (n == -1)
	{
		while (temp->next)
		{
			cout << temp->data<<" ";
			temp = temp->next;
		}
		cout << temp->data << endl;
		return;
	}
	int a(1);
	while (a < n && temp->next)
	{
		cout << temp->data << " ";
		temp = temp->next;
		a++;
	}
	cout << temp->data << endl;
	return;
}

void reverse_print(Node *node,int n)
{
	if (n == -1)
	{
		if (node)
		{
			reverse_print(node->next, -1);
			if (node == head)
			{
				cout << node->data;
				cout << endl;
			}
			else
			{
				cout << node->data << " ";
			}
		}
	}
	if (n > 0)
	{
		links temp = node;
		int i(1);
		for (; i < n&&temp->next; i++)
		{
			temp = temp->next;
		}
		if (!temp->next)
			n = i;
		if (n==1)
		{
			cout << temp->data;
			cout << endl;
		}
		else
			cout << temp->data<<" ";
		reverse_print(node, n - 1);
	}
	return;
}

int equalstr(char*a, char *b)
{
	int flag(1);
	while (*a != '\0'&&*b != '\0')
	{
		if (*a != *b)
		{
			flag = 0;
			return flag;
		}
		a++;
		b++;
	}
	if (*a != *b)
	{
		flag = 0;
		return flag;
	}
	return flag;

}

int main() {
	char A[50];
	int x, y;
	char B[40] = "insert_at_beginning";
	char C[40] = "insert_at_ending";
	char D[40] = "insert_after";
	char E[40] = "delete";
	char F[40] = "print";
	char G[40] = "reverse_print";
	while (cin >> A) {
		if (equalstr(A, B)) {
			cin >> x;
			insert_at_beginning(x);
		}
		else if (equalstr(A, C)) {
			cin >> x;
			insert_at_ending(x);
		}
		else if (equalstr(A, D)) {
			cin >> x >> y;
			insert_after(x, y);
		}
		else if (equalstr(A, E)) {
			cin >> x;
			delete_node(x);
		}
		else if (equalstr(A, F)) {
			cin >> x;
			print(x);
		}
		else if (equalstr(A, G)) {
			cin >> x;
			reverse_print(head,x);
		}
	}
	links temp = head;
	while (temp)
	{
		temp = temp->next;
		delete head;
		head = temp;
	}
	return 0;
}
