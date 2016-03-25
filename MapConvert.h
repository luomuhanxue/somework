#ifndef __TERRARIN_MAP_CONVERTOR_H__
#define __TERRARIN_MAP_CONVERTOR_H__

#include <string>
#include "cocos2d.h"

USING_NS_CC;

namespace terrain{
	namespace tools{

class TerrainMapConvertor {
public:
	TerrainMapConvertor();
	~TerrainMapConvertor();

	bool initWithFile(const std::string& tmxFile);

private:
	
	typedef std::unordered_map<std::string, Value> ValueMap;

};

	}

}


#endif