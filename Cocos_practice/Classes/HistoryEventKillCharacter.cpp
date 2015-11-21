#include "pch.h"
#include "HistoryEventKillCharacter.h"
#include "CharacterAnimation.h"
#include "Character.h"
#include "GameSceneManager.h"
#include "EventManager.h"
#include "SimpleAudioEngine.h"
HistoryEventKillCharacter::HistoryEventKillCharacter()
{
}


std::shared_ptr<HistoryEventKillCharacter> HistoryEventKillCharacter::Create(std::shared_ptr<Character> characterToKill)
{
	std::shared_ptr<HistoryEventKillCharacter> newInst = std::make_shared<HistoryEventKillCharacter>();
	newInst->_CharacterToKill = characterToKill;

	return newInst;
}

HistoryEventKillCharacter::~HistoryEventKillCharacter()	
{
}

void HistoryEventKillCharacter::Run()
{	
	/*auto removeCall = CallFunc::create(CC_CALLBACK_0(TileMap::removeChild, TileMap::getInstance(), _CharacterToKill.get(), true));
	auto nextCall = CallFunc::create(CC_CALLBACK_0(AnimationManager::PlayHistory, AnimationManager::getInstance()));
	

	FiniteTimeAction* seq = Sequence::create(removeCall,nextCall, nullptr);
	//seq->startWithTarget(AnimationManager::getInstance()->getNode());
	
	//_CharacterToKill->runAction(seq);
	AnimationManager::getInstance()->getNode()->runAction(seq);
*/

	TileMap::getInstance()->removeChild(_CharacterToKill.get());
	//AnimationManager::getInstance()->PlayHistory();
	_Done = true;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Hit_03.wav");
}

bool HistoryEventKillCharacter::IsDone()
{
	return true;
}