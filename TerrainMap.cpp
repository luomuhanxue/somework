#include "TerrainMap.h"

namespace terrain{

#define _2x2_BLACK_IMAGE_KEY "black_imag_png"

	static unsigned char _2x2_black_image[] = {
		// RGBA8888
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
	};

	TerrainMap::TerrainMap()
	{
	}

	TerrainMap::~TerrainMap()
	{
	}

	bool TerrainMap::initWithMapInfo(TerrainMapInfo * mapInfo){
		if (Node::init()){
			_tile_size = mapInfo->getTileSize();
			Size map_size = mapInfo->getMapSize();
			_map_width = map_size.width;
			_map_height = map_size.height;
			_map_info = mapInfo;
			loadMapTextrue();
			updateTiles();
			return true;
		}
		return false;
	}

	Sprite* TerrainMap::createSpriteByGID(uint16_t gid, uint16_t x, uint16_t y){
		uint16_t idx = (gid-1) / 25;
		uint16_t pos = (gid-1) % 25;
		uint16_t pos_y = pos / 5;
		uint16_t pos_x = pos % 5;
		std::string textrueName = "res/leveldata/tileset";
		std::string extName = ".png";
		char a = 'a' + idx;
		if (idx >= 5) a += 1;
		Node * node = this->getChildByTag(idx);
		if (!node){
			node = Node::create();
			node->setTag(idx);
			this->addChild(node);
		}
		Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(textrueName + a + extName);
		Sprite* sp = Sprite::createWithTexture(tex, Rect(
			pos_x*_tile_size.width,
			pos_y*_tile_size.height,
			_tile_size.width,
			_tile_size.height
			));
		sp->setTexture(tex);
		node->addChild(sp);
		return sp;
	}

	void TerrainMap::loadMapTextrue(){
		for (int i = 0; i < 8; ++i){
			char a = 'a' + i;
			if (i >= 5) a += 1;
			std::string textrueName = "res/leveldata/tileset";
			std::string extName =  ".png";
			Director::getInstance()->getTextureCache()->addImage(textrueName+a+extName);
		}
	}

	void TerrainMap::updateTiles(){
		//_transformUpdated = _transformDirty = _inverseDirty = true;
		uint16_t * data = _map_info->getGIDData();
		Size win_size = Director::getInstance()->getWinSizeInPixels();
		uint16_t show_width = (uint16_t)(win_size.width / _tile_size.width) + 1;
		uint16_t show_height = (uint16_t)(win_size.height / _tile_size.height) + 1;
		for (int i = 0; i < show_width; ++i){
			for (int j = 0; j < show_height; ++j){
				int pos_h = _map_height - j - 1;
				uint16_t gid = *(data + i + pos_h*_map_width);
				if (gid != 0){
					Sprite* sp = createSpriteByGID(gid, i, j);
					sp->setPosition((i + 0.5)*_tile_size.width, (j + 0.5)*_tile_size.height);
				}
				else{
					Texture2D* texture = _director->getTextureCache()->getTextureForKey(_2x2_BLACK_IMAGE_KEY);
					// If texture wasn't in cache, create it from RAW data.
					if (texture == nullptr)
					{
						Image* image = new (std::nothrow) Image();
						bool isOK = image->initWithRawData(_2x2_black_image, sizeof(_2x2_black_image), 2, 2, 8);
						CC_UNUSED_PARAM(isOK);
						CCASSERT(isOK, "The 2x2 empty texture was created unsuccessfully.");
						texture = _director->getTextureCache()->addImage(image, _2x2_BLACK_IMAGE_KEY);
						CC_SAFE_RELEASE(image);
					}
					Sprite* sp = Sprite::createWithTexture(texture,Rect(CCPoint::ZERO,_tile_size));
					sp->setPosition((i + 0.5)*_tile_size.width, (j + 0.5)*_tile_size.height);
					this->addChild(sp);
				}
			}
		}
	}

	void TerrainMap::setScale(float f){
		Node::setScale(f);
	}
}