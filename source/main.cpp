
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
		 WrapPointer<Node2>::NewWithName(&next, "test");

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
	FileManager::fileName = "output1.txt";
	FileManager::ClearFile();
	
	
	for (int tr = 0; tr < 1000; ++tr) {

		{/*
			{
				WrapPointer<WrapPointer<int>> k;
				WrapPointer<WrapPointer<int>>::NewArray(&k, 10);

				for (int i = 0; i < 10; ++i) {
					WrapPointer<int>::NewArray(&k[i], 10);
				}

				for (int i = 0; i < 10; ++i) {
					k[i].DeleteArray(); // line comment?
				}
				k.DeleteArray();
				//k[9].DeleteArray();
			}

			
			

			// Test
			WrapPointer<int> i;
			WrapPointer<int>::New(&i, 1234);
			WrapPointer<int> j;
			WrapPointer<int>::New(&j, 222);

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


			

			{
				WrapPointer<int> z;
				WrapPointer<int>::New(&z, 5);

				{
					int x = 5;
					WrapPointer<int> y;
					WrapPointer<int>::NewLocal(&y, &x);

					*z = *y;

					*y = *z;

					z.Delete();
					z = y;
				}

				//z.Delete();
			}
*/
		

			/*WrapPointer<Node> a;
			{
				// no need!! - remove Local~~
				WrapPointer<Node> k;
				WrapPointer<Node>::NewLocalWithName(&k, "k", Node(3));
				WrapPointer<Node> k2 = k;

				a = k; // group <- add "local", "global"?

				//k2.Delete();
			}

			//a->parent = x;
			*/
			/*
			WrapPointer<Node> x;
			WrapPointer<Node>::NewWithName(&x, "x", 3);
			WrapPointer<Node> y;
			WrapPointer<Node>::NewWithName(&y, "y", 5);

			x->parent = y;
			y->parent = x;

			x.Delete();
			y.Delete();
			//x.Delete();

			WrapPointer<Node>::NewWithName(&x, "a", Node(3));
			WrapPointer<Node>::NewWithName(&y, "b", Node(5));

			x->parent = y;
			y->parent = x;
			
			x.Delete();

			*/

			WrapPointer<Node> z;
			WrapPointer<Node>::NewArray(&z, "z", 10);
			//WrapPointer<Node> zz("", true);
			//WrapPointer<Node>::plus(&z, &zz, 4);


			z.DeleteArray();

			//zz[5].parent = WrapPointer<Node>::NewWithName("zz[5]", 6);
			///z[1].parent = y;

			//y.Delete();

			///z[0].parent = y;
			///z[0].parent = z[1].parent;
			//z[10] = z[1];
			///x.Delete();
			///z[0].parent.Delete();
			///z.DeleteArray();
			/// 
			std::cout << "chk " << removed_tids.size() << "\n";
			std::cout << "chk " << tids.size() << "\n";
			std::cout << "chk " << tid << "\n";
		}
		std::cout << ".................\n";
		std::cout << "chk " << removed_tids.size() << "\n";
		std::cout << "chk " << tids.size() << "\n";
		std::cout << "chk " << tid << "\n";
	}

	return 0;
}
