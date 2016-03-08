#include "AstarLayer.h"
#include <chrono>
#include <thread>
using namespace cocos2d;

static AStar* _instance = nullptr;

ANode* ANode::create()
{
	ANode* node = new ANode();
	if (node && node->init()) {
		node->autorelease();
		return node;
	}
	else {
		CC_SAFE_DELETE(node);
		return nullptr;
	}
}

bool ANode::init()
{
	if (!Node::init()) {
		return false;
	}
	drawNode = DrawNode::create();
	setType(Type::kNormal);
	this->addChild(drawNode);
	this->setContentSize(Size(aWidth, aWidth));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	return true;
}

bool ANode::setType(Type type)
{
	Color4F color;
	switch (type)
	{
	case ANode::Type::kNormal:
		color = Color4F::MAGENTA;
		break;
	case ANode::Type::kWall:
		color = Color4F(0x8b / 255.0f, 0x57 / 255.0f, 0x42 / 255.0f, 1);
		break;
	case ANode::Type::kSrc:
		color = Color4F(0x41 / 255.0f, 0x69 / 255.0f, 0xE1 / 255.0f, 0.8);
		break;
	case ANode::Type::kDst:
		color = color = Color4F(0x22 / 255.0f, 0x8B / 255.0f, 0x22 / 255.0f, 0.8);
		break;
	case ANode::Type::kAddOpen:
		color = Color4F::BLUE;
		break;
	case ANode::Type::kAddClose:
		color = Color4F(0x89 / 255.0f, 0x68 / 255.0f, 0xCD / 255.0f, 1);
		break;
	case ANode::Type::kPath:
		color = Color4F::GREEN;
		break;
	default:
		color = Color4F::MAGENTA;
		break;
	}
	aType = type;
	drawNode->clear();
	drawNode->drawSolidRect(Vec2(0, 0), Vec2(aWidth, aWidth), color);
	drawNode->drawRect(Vec2(0, 0), Vec2(aWidth, aWidth), Color4F::ORANGE);
	return true;
}

/////////////////////////////////////////////////

void AstarNode::calcValue(AstarNode* dst)
{
	int v = abs(parent->row - row) + abs(parent->col - col);
	if (v == 1) {
		gValue = parent->gValue + 10;
	}
	else {
		gValue = parent->gValue + 14;
	}
	hValue = abs(dst->col - col) + abs(dst->row - row);
}

////////////////////////////////////////////////

Scene* AstarLayer::createScene()
{
	Scene* scene = Scene::create();
	AstarLayer* layer = AstarLayer::create();
	scene->addChild(layer);
	return scene;
}

AstarLayer* AstarLayer::create()
{
	AstarLayer* layer = new (std::nothrow) AstarLayer();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	else {
		delete layer;
		layer = nullptr;
		return nullptr;
	}
}

bool AstarLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto winSize = Director::getInstance()->getVisibleSize();

	auto bgLayer = LayerColor::create(Color4B(0x12, 0x12, 0x12, 0xff));
	bgLayer->setPosition(Vec2(0, 0));
	this->addChild(bgLayer);
	ANode* temp = ANode::create();
	float startx = (winSize.width - maxcol * temp->getContentSize().width) / 2;
	float starty = (winSize.height - maxrow * temp->getContentSize().height) / 2;
	auto nsize = temp->getContentSize();

	AstarNode nodes[maxrow][maxcol];

	for (int i = 0; i < maxcol; i++) {
		for (int j = 0; j < maxrow; j++) {
			auto node = ANode::create();
			node->setPosition(startx + (i + 0.5)*nsize.width, starty + (j + 0.5)*nsize.height);
			this->addChild(node);
			mNodes[j][i] = node;

			nodes[j][i].row = j;
			nodes[j][i].col = i;
		}
	}

	src = AstarNode(10, 3);
	dst = AstarNode(3, 21);

	mNodes[src.row][src.col]->setType(ANode::Type::kSrc);
	mNodes[dst.row][dst.col]->setType(ANode::Type::kDst);

	for (int row = 4; row < maxrow; row++) {
		mNodes[row][5]->setType(ANode::Type::kWall);
	}

	for (int row = 3; row < maxrow - 3; row++) {
		mNodes[row][10]->setType(ANode::Type::kWall);
	}

	for (int row = 0; row < maxrow - 4; row++) {
		mNodes[row][18]->setType(ANode::Type::kWall);
	}

	auto astar = AStar::getInstance();
	astar->init(nodes, this);

	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this, astar](Touch* touch, Event* e)->bool {
		
		std::thread t(std::bind(&AStar::find, astar, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), src, dst, std::ref(list));
		t.detach();
		//AStar::getInstance()->find(src, dst, list);
		return true;
	};
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
////////////////////////////

AStar* AStar::getInstance()
{
	if (_instance == nullptr) {
		_instance = new AStar();
	}
	return _instance;
}

void AStar::init(AstarNode(&astarNodes)[maxrow][maxcol], AstarLayer* astar)
{
	std::swap(nodes, astarNodes);
	layer = astar;
}

bool AStar::find(AstarNode src, AstarNode dst, std::vector<AstarNode*> &list)
{
	using namespace std::literals;
	std::vector<AstarNode*> queue;

	memset(openlist, 0, sizeof(openlist));
	memset(closelist, 0, sizeof(closelist));

	queue.push_back(&nodes[src.row][src.col]);

	while (!queue.empty()) {
		auto it = queue.begin();
		for (auto iter = queue.begin(); iter != queue.end(); iter++) {
			if ((*it)->getFValue() > (*iter)->getFValue()) {
				it = iter;
			}
		}
		auto node = *it;
		queue.erase(it);
		closelist[node->row*maxcol + node->col] = true;

		if (!(src.row == node->row && src.col == node->col)) {
			this->layer->getNode(node->row, node->col)->setType(ANode::Type::kAddClose);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		int r = node->row;
		int c = node->col;

		Vec2Ex twds[8]{ 
			{ r + 1, c },
			{ r - 1, c },
			{ r, c + 1},
			{ r, c - 1 },
			{ r + 1, c + 1 },
			{ r + 1, c - 1},
			{ r - 1, c + 1},
			{ r - 1, c - 1},
		};

		for (int i = 0; i < 8; i++) {
			int row = twds[i].x;
			int col = twds[i].y;

			//std::this_thread::sleep_for(1s);

			if (row == dst.row && col == dst.col) {
				list.push_back(&nodes[row][col]);
				auto p = node;
				while (p != nullptr) {
					list.push_back(p);

					if (p->row != src.row || p->col != src.col) {
						this->layer->getNode(p->row, p->col)->setType(ANode::Type::kPath);
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					p = p->parent;
				}
				return true;
			}

			if (isValid(row, col) && !isUnwalkable(row, col)) {
				if (openlist[row*maxcol + col]) {
					if (nodes[row][col].gValue > node->gValue + 10)
					{
						nodes[row][col].parent = node;
						nodes[row][col].calcValue(&dst);
					}
				}
				else {
					nodes[row][col].parent = node;
					nodes[row][col].calcValue(&dst);
					queue.push_back(&nodes[row][col]);
					openlist[row*maxcol + col] = true;

					this->layer->getNode(row, col)->setType(ANode::Type::kAddOpen);
				}
			}
		}
	}

	return false;
}

bool AStar::isUnwalkable(int row, int col)
{
	return layer->getNode(row, col)->getType() == ANode::Type::kWall;
}

bool AStar::isValid(int row, int col)
{
	if (row >= 0 && row < maxrow && col >= 0 && col < maxcol) {
		return !closelist[row * maxcol + col];
	}
	return false;
}