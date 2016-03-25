#ifndef __TERRAINLAYER_H__
#define __TERRAINLAYER_H__
#include "cocos2d.h"

using namespace cocos2d;

class TerrainLayer :public Node
{

	//static TerrainLayer * create();

	/**
	* @js ctor
	*/
	TerrainLayer();
	/**
	* @js NA
	* @lua NA
	*/
	virtual ~TerrainLayer();


	bool initLayerInfo();

protected:
	void tileToNodeTransform();

	void updateTotalQuads();
	void updateVertexBuffer();

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;

	//void updateIndexBuffer();
	//void updatePrimitives();


	Texture2D *_texture;

	std::string _layerName;

	Size _layerSize;
	
	unsigned short * _tiles;

	Mat4 _tileToNodeTransform;

	bool _quadsDirty;

	std::vector<int> _tileToQuadIndex;
	std::vector<V3F_C4B_T2F_Quad> _totalQuads;
	std::vector<GLushort> _indices;
	std::map<int/*vertexZ*/, int/*offset to _indices by quads*/> _indicesVertexZOffsets;
	std::unordered_map<int/*vertexZ*/, int/*number to quads*/> _indicesVertexZNumber;
	std::vector<PrimitiveCommand> _renderCommands;


	VertexBuffer* _vertexBuffer;

	VertexData* _vData;

	IndexBuffer* _indexBuffer;

	Map<int, Primitive*> _primitives;
};

/*
	层名字
	层大小
	层地图信息

	瓦片大小
	原点位置

	图层偏移量

	设置变换矩阵



*/


#endif