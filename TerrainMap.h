#ifndef __TERRAINMAP_H__
#define __TERRAINMAP_H__

#include "cocos2d.h"
#include "map/TerrainMapInfo.h"

USING_NS_CC;

namespace terrain{

	class TerrainMap : public Node
	{
	public:
		TerrainMap();
		~TerrainMap();
		bool initWithMapInfo(TerrainMapInfo *info);

		void setScale(float f);

	private:

		void updateTiles();

		Sprite* createSpriteByGID(uint16_t gid,uint16_t x,uint16_t y);
		void loadMapTextrue();
		Size _tile_size;
		uint16_t _map_width;
		uint16_t _map_height;
		TerrainMapInfo* _map_info;
	};
}

#endif