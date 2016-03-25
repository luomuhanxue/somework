#ifndef __TERRARIN_MAP_INFO_H__
#define __TERRARIN_MAP_INFO_H__

#include <string>
#include "cocos2d.h"

USING_NS_CC;

namespace terrain{

class TerrainMapInfo {
public:
	TerrainMapInfo();
	~TerrainMapInfo();

	bool initWithFile(const std::string& tmxFile);
	Size getTileSize();
	Size getMapSize();
	uint16_t * getGIDData();
private:
	uint16_t *_data;
	size_t _total_size;
	uint16_t _map_height;
	uint16_t _map_width;
	Size _tile_size;
};

}


#endif