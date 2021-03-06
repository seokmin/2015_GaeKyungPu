#include "pch.h"
#include "Phase_Harvest.h"
#include "UILayer.h"
#include "EventManager.h"
#include "HistoryEventHarvest.h"


Phase_Harvest::Phase_Harvest()
{
	_PhaseInfo = PHASE_HARVEST;
}


Phase_Harvest::~Phase_Harvest()
{
}

void Phase_Harvest::Tick()
{
	PlayerData* currentPlayerData = GameSceneManager::getInstance()->getCurrentPlayerData();
	currentPlayerData->setFood(1);

	//만약 옥토 타일 위에 턴주의 병사가 있다면 해당 병사 한명당 식량 1 ++해야함.
	auto characterList = currentPlayerData->getCharacterList();

	for (auto iter : *characterList)
	{
		if (iter->getCurrentTile()->getTypeOfTile() == TILE_RICH || iter->getCurrentTile()->getTypeOfTile() == TILE_RICH_SIDE)
		{
			//currentPlayerData->AddFood(1);
			EventManager::getInstance()->AddHistory(HistoryEventHarvest::Create(iter));
		}
	}
	_NextPhaseInfo = PHASE_OCCUPY;
}