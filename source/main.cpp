
// only support single thread new, delete and etc..?
#include <iostream>
#include <string>

#include "WrapPointer.h"

using namespace wiz;

class Node;
class Item {
public:
	int x = 0;
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
 	int val = 0;
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

inline WrapPointer<Node> func_return() {
	return WrapPointer<Node>::NewWithName("x", 3);
}

int main(void)
{
	FileManager::fileName = "output.txt";
	FileManager::ClearFile();

	{
		WrapPointer<int> z;
		z = WrapPointer<int>::New(5);

		{
			int x = 5;
			WrapPointer<int> y;
			WrapPointer<int>::NewLocal(&y, &x);

			*z = *y;

			*y = *z;

			z = y;
		}

		//z.Delete();
	}



	// Test
	WrapPointer<int> i = WrapPointer<int>::New(1234);
	WrapPointer<int> j = WrapPointer<int>::New(222);

	{
		WrapPointer<WrapPointer<int>> T;
		
		WrapPointer<WrapPointer<int>>::NewLocalWithName(&T, "chk"); 

		*T = i; // T = &i; 

		std::cout << (**T) << "\n";


		i = *T;

		//T->Delete();
	}

	i.Delete();
	j.Delete();


	WrapPointer<Node> x;
	x = func_return(); // WrapPointer<Node>::NewWithName("x", 3);
	WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);

	WrapPointer<Node> z = WrapPointer<Node>::NewArray("z", 10);
	WrapPointer<Node> zz = z + 4;

	//zz[5].parent = WrapPointer<Node>::NewWithName("zz[5]", 6);

	WrapPointer<Node> a;
	{
		// no need!! - remove Local~~
		WrapPointer<Node> k;
		WrapPointer<Node>::NewLocalWithName(&k, "k", Node(3));
		WrapPointer<Node> k2 = k;

		a = k; // group <- add "local", "global"?
		
		//k2.Delete();
	}
	
	//a->parent = x;

	x->parent = y;
	y->parent = x;

	x.Delete();
	y.Delete();
	//x.Delete();

	x = WrapPointer<Node>::NewWithName("a", Node(3));
	y = WrapPointer<Node>::NewWithName("b", Node(5));

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

	return 0;
}
