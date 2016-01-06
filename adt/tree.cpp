struct  PathNode
{
	Vec2Ex vex;
	PathNode* child;
	PathNode* sibling;

	PathNode(const Vec2Ex& v) : vex(v), child(nullptr), sibling(nullptr)
	{

	}
};

void DropPath::deleteTree(Tree t)
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