
// only support single thread new, delete and etc..?
#include <iostream>
#include <string>

#include "WrapPointer.h"


class Node {
public:
	int val;
	WrapPointer<Node> parent;
	WrapPointer<Node> child;
	WrapPointer<Node> next;
public:
	Node() {
		parent.SetName("parent");
		child.SetName("child");
		next.SetName("next");
	}
	Node(int _val) {
		parent.SetName("parent");
		child.SetName("child");
		next.SetName("next");
		this->val = val;
	}
};


int main(void)
{
	FileManager::fileName = "output.txt";
	FileManager::ClearFile();

	// Test
	WrapPointer<Node> x = WrapPointer<Node>::NewWithName("x", 3);
	WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);
	
	//x->next = y;
	//y->next = x;

	x.Delete();
	y.Delete();

	x = WrapPointer<Node>::NewWithName("a", 3);
	y = WrapPointer<Node>::NewWithName("b", 5);

	//x->next = y;
	//y->next = x;

	x.Delete();
	y.Delete();

	return 0;
}
