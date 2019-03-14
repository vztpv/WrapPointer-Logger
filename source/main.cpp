
// only support single thread new, delete and etc..?
#include <iostream>
#include <string>

#include "WrapPointer.h"

using namespace wiz;

class Node;
class Item {
public:
	int x;
	WrapPointer<Node> next;
public:
	Item() { }
	Item(const int _x, const WrapPointer<Node> _next)
	{
		this->x = _x;
		this->next = _next;
	}
};

class Node2
{
public:
	WrapPointer<Node2> next;
};

class Node {
public:
	int val;
	WrapPointer<Node> parent;
	WrapPointer<Node> child;
	WrapPointer<Node2> next;
public:
	Node() {
		next = WrapPointer<Node2>::New();

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

void memory_leak_test() {
	//
}
void double_delete_test() {
	//
}
void array_test() {
	//
}


int main(void)
{
	FileManager::fileName = "output.txt"; 
	FileManager::ClearFile();

	// Test
	WrapPointer<Node> x = WrapPointer<Node>::NewWithName("x", 3);
	WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);

	WrapPointer<Node> z = WrapPointer<Node>::NewArray("z", 10);
	//WrapPointer<WrapPointer<Node>> z = WrapPointer<WrapPointer<Node>>::NewArray("z", 10);

	x->parent = y;
	y->parent = x;

	x.Delete();
	y.Delete();
	//x.Delete();

	x = WrapPointer<Node>::NewWithName("a", 3); 
	y = WrapPointer<Node>::NewWithName("b", 5);

	x->parent = y;
	y->parent = x;
	z[0].parent = y + 1;
	
	//y.Delete();
	
	z[1].parent = z[0].parent - 1;
	//z[10] = z[1];
	x.Delete();
	z[1].parent.Delete();
	z.DeleteArray();

	return 0;
}
