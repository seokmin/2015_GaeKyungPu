#include "pch.h"
#include "GameMaster.h"
#include "Character.h"


Character* Character::create(PlayerInfo cPInfo)
{
	Character* sprite = new Character();
	std::string fileName = std::string("Character/spear_");

	if (cPInfo == PLAYER_RED)
	{
		fileName += std::string("red");
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		fileName += std::string("blue");
	}
	fileName += std::string("_00.png");

	if (sprite && (sprite->initWithFile(fileName)))
	{
		sprite->autorelease();
		sprite->setcurrentPlayerInfo(cPInfo);
		sprite->setcurrentAngle(ANGLE_DOWN_LEFT);
		//��Ÿ �ʿ��Ѱ�
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Character::isOnTile(TileKind tileTypeToCheck)
{
	if (currentTile->getTypeOfTile() == tileTypeToCheck)
	{
		return true;
	}
	else return false;
}

void Character::rotateToDirection(RotateDirection rotateDirection, Character* character)
{
	std::string fileName = std::string("Character/spear_");
	if (character->getcurrentPlayerInfo() == PLAYER_RED)
	{
		fileName += std::string("red");
	}
	else if (character->getcurrentPlayerInfo() == PLAYER_BLUE)
	{
		fileName += std::string("blue");
	}

	int cAngle = character->getcurrentAngle();
	if (rotateDirection == ROTATE_LEFT)
	{
		if (cAngle == 5) cAngle = 0;
		else cAngle++;

		std::ostringstream ostr;
		ostr << cAngle;
		fileName += std::string("_0");
		fileName += std::string(ostr.str());
		fileName += std::string(".png");
	}
	else if (rotateDirection == ROTATE_RIGHT)
	{
		if (cAngle == 0) cAngle = 5;
		else cAngle--;

		std::ostringstream ostr;
		ostr << cAngle;
		fileName += std::string("_0");
		fileName += std::string(ostr.str());
		fileName += std::string(".png");
	}
	character->setcurrentAngle(CharacterAngle(cAngle));

	character->initWithFile(fileName);
	character->setAnchorPoint(Point(0.5, 0.13));
}