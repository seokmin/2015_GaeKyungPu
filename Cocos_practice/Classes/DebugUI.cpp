#include "pch.h"
#include "DebugUI.h"

cocos2d::Scene* DebugUI::scene()
{
	cocos2d::Scene *scene = Scene::create();
	DebugUI* layer = DebugUI::create();

	scene->addChild(layer);
	return scene;
}

bool DebugUI::init()
{
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))  //투명하게
	{
		return false;
	}

	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();

	//backLayer추가
	backLayer = LayerColor::create(ccc4(0, 0, 0, 50), visibleSize.width, visibleSize.height);
	backLayer->setAnchorPoint(Vec2(0, 0));
	backLayer->setPosition(Vec2(0, 0));
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer = LayerColor::create(ccc4(92, 92, 92, 255), visibleSize.width / 2, visibleSize.height / 2);
	popUpLayer->setAnchorPoint(Vec2(0, 0));
	popUpLayer->setPosition(Vec2((visibleSize.width - popUpLayer->getContentSize().width) / 2, (visibleSize.height - popUpLayer->getContentSize().height) / 2));

	float width = popUpLayer->getContentSize().width;
	float height = popUpLayer->getContentSize().height;

	cocos2d::Label* label_title = Label::createWithTTF("Testudo::Debug", "fonts/Marker Felt.ttf", 20);
	label_title->setPosition(Vec2(100, height - 20));

	popUpLayer->addChild(label_title);
	this->addChild(popUpLayer);

	return true;
}

const void DebugUI::SetValue(PlayerData* pData1, PlayerData* pData2) const
{
	int pData1Food = pData1->getFood();
	int pData2Food = pData2->getFood();
	
	auto p1Food = Label::createWithTTF(std::to_string(pData1Food), "fonts/Marker Felt.ttf", 20);
	auto p2Food = Label::createWithTTF(std::to_string(pData2Food), "fonts/Marker Felt.ttf", 20);

	float width = popUpLayer->getContentSize().width;
	float height = popUpLayer->getContentSize().height;

	p1Food->setPosition(Vec2(100, height - 120));
	p2Food->setPosition(Vec2(100 + width / 2, height - 120));

	popUpLayer->addChild(p1Food);
	popUpLayer->addChild(p2Food);
}