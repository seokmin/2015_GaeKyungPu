#include "pch.h"
#include "GameScene.h"
#include "TileMap.h"

int GameScene::turn = 0;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto tilemap = TileMap::getInstance();
	tilemap->createMap();
	this->addChild(tilemap);

	auto unitLayer = Layer::create();
	unitLayer->setName("unitLayer");
	this->addChild(unitLayer);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto turn_ui = Label::createWithTTF("Turn Red", "fonts/Marker Felt.ttf", 40);
	turn_ui->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height * 1 / 4));
	turn_ui->setName("turn_ui");
	this->addChild(turn_ui);

//	Keyboard Event
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

//	Mouse Event
	auto clickListener = EventListenerMouse::create();
	clickListener->onMouseDown = CC_CALLBACK_1(GameScene::eventByClick, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this);

	return true;
}

void GameScene::eventByClick(Event* event)
{
	EventMouse* mouseEvent = nullptr;
	mouseEvent = dynamic_cast<EventMouse*>(event);

	switch (mouseEvent->getMouseButton())
	{
	case MOUSE_BUTTON_LEFT:
		setUnitByClick(event);
		break;

	case MOUSE_BUTTON_RIGHT:
		delUnitByClick(event);
		break;
	}
}

void GameScene::setUnitByClick(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto unit_layer = event->getCurrentTarget()->getChildByName("unitLayer");

	float xPos = mouseEvent->getCursorX();
	float yPos = mouseEvent->getCursorY();

	auto pinfo = AutoPolygon::generatePolygon("Character/spear_red_01.png");

//	�ϴ� turn ǥ�ø� ������... 0�� ��� red, 1�� ��� blue
	if (turn == 1)
	{
		pinfo = AutoPolygon::generatePolygon("Character/spear_blue_01.png");
	}

	auto unit_spear = Sprite::create(pinfo);
	unit_spear->setName("unit");
	unit_spear->setAnchorPoint(Point(0.5, 0.13));

	unit_spear->setPosition(Vec2(origin.x + xPos, visibleSize.height + yPos));
	unit_layer->addChild(unit_spear);
}

void GameScene::delUnitByClick(Event* event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto unit_layer = event->getCurrentTarget()->getChildByName("unitLayer");

	auto point = mouseEvent->getLocationInView();
	auto children = unit_layer->getChildren();

	for (auto iter = children.begin(); iter != children.end(); ++iter)
	{
		if ((*iter)->getName() != "unit")
		{
			continue;
		}

		auto sprite = dynamic_cast<Sprite*>(*iter);
		if (sprite->boundingBox().containsPoint(Vec2(point.x, visibleSize.height + point.y)))
		{
			unit_layer->removeChild(sprite);
		}
	}
}

void GameScene::rotateUnitByClick(Event* event)
{

}

void GameScene::menuClickCallback(cocos2d::Ref* pSender)
{
	
}

void GameScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::toggleTurn()
{

	turn = (turn + 1)%2;
	this->removeChild(this->getChildByName("turn_ui"));
	auto turn_ui = Label::createWithTTF("Turn Red", "fonts/Marker Felt.ttf", 40);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (turn == 1)
	{
		turn_ui = Label::createWithTTF("Turn Blue", "fonts/Marker Felt.ttf", 40);
	}

	turn_ui->setPosition(Vec2(visibleSize.width * 3 / 4, visibleSize.height * 1 / 4));
	turn_ui->setName("turn_ui");
	this->addChild(turn_ui);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ESCAPE:
		Director::getInstance()->end();
		break;

	case EventKeyboard::KeyCode::KEY_ENTER:
		toggleTurn();
		break;
	}
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode){

	case EventKeyboard::KeyCode::KEY_ENTER:
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	}
}