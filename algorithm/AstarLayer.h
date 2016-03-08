#ifndef _ASTAR_LAYER_H_
#define _ASTAR_LAYER_H_
#include "cocos2d.h"

class ANode : public cocos2d::Node {
public:
	enum class Type {
		kNormal,
		kWall,
		kSrc,
		kDst,
		kAddOpen,
		kAddClose,
		kPath,
	};
	static ANode* create();
	virtual bool init() override;
	bool setType(Type type);
	Type getType() { return aType; }
private:
	cocos2d::DrawNode *drawNode;
	Type aType;
	int aWidth = 40;
};

struct AstarNode {
	AstarNode* parent;
	int hValue;
	int gValue;
	int row;
	int col;

	int getFValue() { return hValue + gValue; }
	void calcValue(AstarNode* dst);

	AstarNode() :AstarNode(0, 0) {

	}
	AstarNode(int r, int c) :
		row(r), col(c), parent(nullptr), hValue(0), gValue(0)
	{

	}
};

struct Vec2Ex {
	int x;
	int y;
	Vec2Ex() {
		x = 0;
		y = 0;
	}
	Vec2Ex(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

const int maxrow = 15;
const int maxcol = 23;

class AstarLayer : public cocos2d::Layer {
public:

	static AstarLayer* create();
	static cocos2d::Scene* createScene();
	virtual bool init() override;

	ANode* getNode(int row, int col) { return mNodes[row][col]; }
private:
	ANode* mNodes[maxrow][maxcol];
	AstarNode src;
	AstarNode dst;
	std::vector<AstarNode*> list;
};

class AStar {
public:
	static AStar* getInstance();

	bool find(AstarNode src, AstarNode dst, std::vector<AstarNode*> &list);

	void init(AstarNode(&astarNodes)[maxrow][maxcol], AstarLayer* astarLayer);

private:
	//void addOpenList(std::vector<AstarNode*>& q, )
	bool isValid(int row, int col);
	bool isUnwalkable(int row, int col);
	AstarLayer* layer = nullptr;
	AstarNode nodes[maxrow][maxcol];
	bool openlist[maxrow*maxcol];
	bool closelist[maxrow*maxcol];
};

#endif