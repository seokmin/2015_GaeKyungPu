#include "pch.h"
#include "definition.h"
#include "Character.h"
#include "CharacterAnimation.h"

CharacterAnimation* CharacterAnimation::_Inst = nullptr;

void CharacterAnimation::Init()
{
	for (int i = 0; i < NUM_OF_PLAYER; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{	
			_AnimationArray[i * 24 + j * 4] = CreateAnimationDefault(PlayerInfo(i), DirectionKind(j));
			_AnimationArray[i * 24 + j * 4 + 1] = CreateAnimationMove(PlayerInfo(i), DirectionKind(j));
			_AnimationArray[i * 24 + j * 4 + 2] = CreateAnimationAttack(PlayerInfo(i), DirectionKind(j));
			_AnimationArray[i * 24 + j * 4 + 3] = CreateAnimationBeHit(PlayerInfo(i), DirectionKind(j));
		}
	}
}

//으씨 이거는 임시...
//왜 array에 저장된 값을 불러올 수 없는가?!
Animation* CharacterAnimation::getAnimationDefault(PlayerInfo cPInfo, DirectionKind dir)
{
	Animation* test = CreateAnimationDefault(cPInfo, dir);
	int index = static_cast<int>(cPInfo)* 24 + static_cast<int>(dir)* 4;

	//return _AnimationArray[index];
	return test;
}

Animation* CharacterAnimation::getAnimationMove(PlayerInfo cPInfo, DirectionKind dir)
{
	Animation* test = CreateAnimationMove(cPInfo, dir);
	int index = static_cast<int>(cPInfo)* 24 + static_cast<int>(dir)* 4 +1;
	
	//return _AnimationArray[index];
	return test;
}

Animation*  CharacterAnimation::getAnimationAttack(PlayerInfo cPInfo, DirectionKind dir)
{
	int index = static_cast<int>(cPInfo)* 24 + static_cast<int>(dir)* 4+2;
	return _AnimationArray[index];
}

Animation* CharacterAnimation::getAnimationBeHit(PlayerInfo cPInfo, DirectionKind dir)
{
	int index = static_cast<int>(cPInfo)* 24 + static_cast<int>(dir)* 4 +3;
	return _AnimationArray[index];
}

CharacterAnimation* CharacterAnimation::getInstance()
{
	if (_Inst == nullptr)
		_Inst = new CharacterAnimation();

	return _Inst;
}

Animation* CharacterAnimation::CreateAnimationDefault(PlayerInfo cPInfo, DirectionKind dir)
{
	std::string frameName = "spear_";
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	
	if (cPInfo == PLAYER_RED)
	{
		frameName += "R_";
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
	}

	std::string direction = GetDirectionName(dir);
	frameName += direction;

	std::array<SpriteFrame*, 4> frameArray =
	{
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_00.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_01.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_02.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_03.png")
	};

	animation->addSpriteFrame(frameArray[0]);
	animation->addSpriteFrame(frameArray[1]);
	animation->addSpriteFrame(frameArray[2]);
	animation->addSpriteFrame(frameArray[3]);
	animation->addSpriteFrame(frameArray[2]);
	animation->addSpriteFrame(frameArray[1]);
	animation->addSpriteFrame(frameArray[0]);

	animation->setLoops(-1);
	return animation;
}

Animation* CharacterAnimation::CreateAnimationMove(PlayerInfo cPInfo, DirectionKind dir)
{
	std::string frameName = "spear_";
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	
	if (cPInfo == PLAYER_RED)
	{
		frameName += "R_";
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
	}

	std::string direction = GetDirectionName(dir);
	frameName += direction;
	frameName += "_move";

	std::array<SpriteFrame*, 2> frameArray =
	{
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_00.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_01.png")
	};

	animation->addSpriteFrame(frameArray[0]);
	animation->addSpriteFrame(frameArray[1]);

	animation->setLoops(5);
	return animation;
}

Animation* CharacterAnimation::CreateAnimationAttack(PlayerInfo cPInfo, DirectionKind dir)
{
	std::string frameName = "spear_";
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3f);
	
	if (cPInfo == PLAYER_RED)
	{
		frameName += "R_";
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
	}

	std::string direction = GetDirectionName(dir);
	frameName += direction;
	frameName += "_attack";

	std::array<SpriteFrame*, 2> frameArray =
	{
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_00.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_01.png")
	};

	animation->addSpriteFrame(frameArray[0]);
	animation->addSpriteFrame(frameArray[1]);
	return animation;
}

Animation* CharacterAnimation::CreateAnimationBeHit(PlayerInfo cPInfo, DirectionKind dir)
{
	std::string frameName = "spear_";
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	
	if (cPInfo == PLAYER_RED)
	{
		frameName += "R_";
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
	}

	std::string direction = GetDirectionName(dir);
	frameName += direction;
	frameName += "_behit";

	std::array<SpriteFrame*, 2> frameArray =
	{
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_00.png"),
		SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName + "_01.png")
	};

	animation->addSpriteFrame(frameArray[0]);
	animation->addSpriteFrame(frameArray[1]);

	animation->setLoops(5);
	return animation;
}

void CharacterAnimation::setAnimationDefault(Character* targetCharacter)
{

	Animation* animationDefault = CharacterAnimation::CreateAnimationDefault(targetCharacter->GetOwnerPlayer(), targetCharacter->getCurrentDirection());

	ActionInterval* actionDefault = Animate::create(animationDefault);
	targetCharacter->runAction(actionDefault);
	targetCharacter->setAnimState(ANIM_DEFAULT);
}

std::string CharacterAnimation::LoadPlist(PlayerInfo cPInfo, std::string frameName)
{
	if (cPInfo == PLAYER_RED)
	{
		frameName += "R_";
	}
	else if (cPInfo == PLAYER_BLUE)
	{
		frameName += "B_";
	}

	return frameName;
}

std::string CharacterAnimation::GetDirectionName(int spriteNum)
{
	std::string direction = "";
	switch (spriteNum)
	{
	case 0:
		direction = "ld";
		break;
	case 1:
		direction = "d";
		break;
	case 2:
		direction = "rd";
		break;
	case 3:
		direction = "ru";
		break;
	case 4:
		direction = "u";
		break;
	case 5:
		direction = "lu";
		break;
	default:
		direction = "ld";
		break;
	}

	return direction;
}


