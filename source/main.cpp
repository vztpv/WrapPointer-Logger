
// only support single thread new, delete and etc..?
#include <iostream>
#include <string>

#include "WrapPointer.h"


class Node {
public:
	int val;
	WrapPointer<Node> next;
public:
	Node() {
		//
	}
	Node(int _val) {
		this->val = val;
	}
};


int main(void)
{
	Manager::fileName = "output.txt";
	Manager::Clear();

	// Test
	WrapPointer<Node> x = WrapPointer<Node>::New(3);
	WrapPointer<Node> y = WrapPointer<Node>::New(5);
	
	x->next = y;
	y->next = x;

	x.Delete();
	y.Delete();

	return 0;
}
