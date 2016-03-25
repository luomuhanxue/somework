#ifndef __TERRAINLAYER_H__
#define __TERRAINLAYER_H__
#include "cocos2d.h"

using namespace cocos2d;

class TerrainLayer :public Node
{
public:
	TerrainLayer();
	~TerrainLayer();

	bool initWithTilesetInfo();
	
};


#endif