#include "map/TerrainLayer.h"

TerrainLayer::TerrainLayer()
{

}

TerrainLayer::~TerrainLayer()
{

}

bool TerrainLayer::initWithTilesetInfo()
{
	int map_width = 100;
	int map_height = 100;
	int tiles_count = map_width * map_height;
	int capacity = tiles_count * 0.36 + 1;

	return false;
}

/*
setupTiles()
	appendTileForGID()
		reusedTileWithRect()
		setupTileSprite()
		insertQuadFromSprite()
		ccCArrayInsertValueAtIndex()

*/