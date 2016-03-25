#include "map/TerrainMapInfo.h"
#include "cocos2d.h"

USING_NS_CC;

namespace terrain{
	TerrainMapInfo::TerrainMapInfo(){

	}

	TerrainMapInfo::~TerrainMapInfo(){

	}

	bool TerrainMapInfo::initWithFile(const std::string& tmxFile){
		std::string filename = FileUtils::getInstance()->fullPathForFilename(tmxFile);
		Data file_data = FileUtils::getInstance()->getDataFromFile(filename);
		uint16_t* data_info = ( uint16_t * )file_data.getBytes();
		size_t total_size = file_data.getSize();
		/*
					*data = title_width;
			*(data + 1) = map_width;
			*(data + 2) = map_height;
		*/
		uint16_t tile_width = *data_info;
		_map_width = *(data_info + 1);
		_map_height = *(data_info + 2);
		
		size_t map_info_size = total_size - sizeof(uint16_t) * 3;
		_data = (uint16_t *)malloc(map_info_size);
		memcpy(_data, data_info + 3, map_info_size);
		//_data = data_info + 3;

		_tile_size = Size(tile_width, tile_width);
		return true;
	}

	Size TerrainMapInfo::getMapSize(){
		return Size(_map_width,_map_height);
	}

	Size TerrainMapInfo::getTileSize(){
		return _tile_size;
	}

	uint16_t * TerrainMapInfo::getGIDData(){
		return _data;
	}

}