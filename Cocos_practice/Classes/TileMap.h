#pragma once
#include <array>
USING_NS_CC;

#include "definition.h"
#include "Self_Tile.h"
#include "Character.h"

class TileMap : public Layer
{
public:
	static TileMap* getInstance();
	bool	create();
	void	setCharacterOnTile(Character* character, Self_Tile* tile, bool moveMode = false);
	void	KillCharacter(Character* target);

	void	Terminate();

private:

	static std::array<std::array<TileKind, MAP_MAX_WIDTH>, MAP_MAX_HEIGHT> _NewMapData;
	std::array<std::array<Self_Tile*, MAP_MAX_WIDTH>, MAP_MAX_HEIGHT> _TileSet;
	void SetTotalNearTile();

	TileMap();
	TileMap(const TileMap& other);
	TileMap& operator=(TileMap& other);
	static TileMap* inst; ///# 코딩 컨벤션
};
