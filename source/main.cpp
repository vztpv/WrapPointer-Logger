
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
		next = WrapPointer<Node2>::NewWithName("test");

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
	~Node() {

		if (next.data()) {
			next.Delete();
		}
	}
};

void memory_leak_test() {
	FileManager::fileName = "output1.txt";
	FileManager::ClearFile();


}
void double_delete_test() {
	FileManager::fileName = "output2.txt";
	FileManager::ClearFile();


}
void array_test() {
	FileManager::fileName = "output3.txt";
	FileManager::ClearFile();


}


int main(void)
{
	FileManager::fileName = "output.txt";
	FileManager::ClearFile();

	// Test
	WrapPointer<Node> x = WrapPointer<Node>::NewWithName("x", 3);
	WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);

	WrapPointer<Node> z = WrapPointer<Node>::NewArray("z", 10);
	WrapPointer<Node> zz = z + 3;

	zz[6].parent = x;

	WrapPointer<Node> a;
	{
		// no need!! - remove Local~~
		WrapPointer<Node> k = WrapPointer<Node>::NewLocalWithName("k", 3); 

		a = k; // group <- add "local", "global"?
	}
	
	//a->parent = x;

	x->parent = y;
	y->parent = x;

	x.Delete();
	y.Delete();
	//x.Delete();

	x = WrapPointer<Node>::NewWithName("a", 3);
	y = WrapPointer<Node>::NewWithName("b", 5);

	x->parent = y;
	y->parent = x;
	z[1].parent = y;

	//y.Delete();

	z[0].parent = y;
	z[0].parent = z[1].parent;
	//z[10] = z[1];
	x.Delete();
	z[0].parent.Delete();
	z.DeleteArray();
	
	

	memory_leak_test();
	double_delete_test();
	array_test();

	return 0;
}
