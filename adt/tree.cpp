#include <iostream>

using namespace std;

class C {
public:
	int v;
	C():v(0){}
	C(int val) { v = val; }
	~C() {
		std::cout << "C::~C(), v=" << v << std::endl;
	}

};

struct  PathNode
{
	C c;
	PathNode* child;
	PathNode* sibling;

	PathNode(const C& v) : c(v), child(nullptr), sibling(nullptr)
	{

	}
};

typedef PathNode *Tree;

void deleteTree(Tree t)
{
	if (t == nullptr)
		return;
	PathNode* child = t->child;
	PathNode* sib = t->sibling;
	delete t;
	if (child) {
		deleteTree(child);
	}
	while (sib) {
		PathNode* tmp = sib;
		sib = sib->sibling;
		deleteTree(tmp);
	}
}

void mainTree()
{
	Tree t = new PathNode(C(2));

	PathNode* t2 = new PathNode(C(3));
	t->child = t2;

	PathNode* t3 = new PathNode(C(4));

	t2->sibling = t3;

	PathNode* t4 = new PathNode(C(5));
	t3->sibling = t4;

	PathNode* t5 = new PathNode(C(6));
	t2->child = t5;

	PathNode* t6 = new PathNode(C(7));
	t5->child = t6;

	PathNode* t7 = new PathNode(C(8));
	t4->child = t7;

	deleteTree(t);
}