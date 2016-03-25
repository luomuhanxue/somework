#include "tools/MapConvert.h"
#include "cocos2d.h"

USING_NS_CC;

namespace terrain{
	namespace tools{

		TerrainMapConvertor::TerrainMapConvertor(){

		}

		TerrainMapConvertor::~TerrainMapConvertor(){

		}

		bool TerrainMapConvertor::initWithFile(const std::string& tmxFile){
			//std::string filename = FileUtils::getInstance()->fullPathForFilename(tmxFile);
			TMXMapInfo *mapInfo = TMXMapInfo::create(tmxFile);
			Size mapSize = mapInfo->getMapSize();
			Size tileSize = mapInfo->getTileSize();
			int mapOrientation = mapInfo->getOrientation();

			Vector<TMXObjectGroup*> objectGroups = mapInfo->getObjectGroups();

			ValueMap properties = mapInfo->getProperties();

			ValueMapIntKey tileProperties = mapInfo->getTileProperties();

			uint16_t map_width = (uint16_t)mapSize.width;
			uint16_t map_height = (uint16_t)mapSize.height;
			uint16_t title_width = (uint16_t)tileSize.width;

			int idx = 0;

			auto& layers = mapInfo->getLayers();
			size_t data_size = sizeof(uint16_t)*map_width*map_height + sizeof(uint16_t)*3;
			uint16_t * data = (uint16_t*)malloc(data_size);
			memset(data, 0, data_size);

			*data = title_width;
			*(data + 1) = map_width;
			*(data + 2) = map_height;
			uint16_t *map_data = data + 3;
			char outString[512];
			for (const auto &layerInfo : layers) {
				CCLOG("-------------------------");
				if (layerInfo->_visible)
				{
					Size s = layerInfo->_layerSize;
					uint32_t* tiles = layerInfo->_tiles;
					for (int i = 0; i < s.height; ++i){
						memset(outString, ' ', sizeof(char) * 512);
						outString[511] = 0;
						for (int j = 0; j < s.width; ++j){
							uint16_t o = *(tiles + int( i * s.width) + j);
							uint16_t d = *(map_data + int(i * s.width) + j);
							if (d == 0 && o != 0){
								*(map_data + int(i * s.width) + j) = o;
							}
							sprintf(outString+j*5, "%4d,",o );
						}
						CCLOG("%s", outString);
					}
					idx++;
				}
			}
			
			//Êä³ö
			CCLOG("=======================\n\n");
			for (int i = 0; i < mapSize.height; ++i){
				memset(outString, ' ', sizeof(char) * 512);
				outString[511] = 0;
				for (int j = 0; j < mapSize.width; ++j){
					uint16_t d = *(data + int(i * mapSize.width) + j);
					sprintf(outString + j * 5, "%4d,", d);
				}
				CCLOG("%s", outString);
			}

			Data out_data;
			out_data.fastSet((unsigned char*)data, data_size);
			FileUtils::getInstance()->writeDataToFile(out_data, "res/map_data");

			return false;
		}

	}
}