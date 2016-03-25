#include "map/TerrainLayer.h"

TerrainLayer::TerrainLayer()
{

}

TerrainLayer::~TerrainLayer()
{

}

bool TerrainLayer::initLayerInfo()
{

	std::string path = FileUtils::getInstance()->fullPathForFilename("leveldata/tileseta.png");
	_texture = Director::getInstance()->getTextureCache()->addImage(path);
	_texture->retain();

	_layerSize = Size(100, 100);
	
	_tiles = (unsigned short*)malloc(sizeof(unsigned short) * 100 * 100);
	memset(_tiles, 0,100*100*sizeof(unsigned short));

	for (int i = 50 * 100; i < 10000; ++i){
		_tiles[i] = 1;
	}


	this->setContentSize(Size(100 * 32, 100 * 32));

	this->tileToNodeTransform();
	setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR));

	return true;
}

void TerrainLayer::tileToNodeTransform()
{

	float w = 32.0 / CC_CONTENT_SCALE_FACTOR();
	float h = 32.0 / CC_CONTENT_SCALE_FACTOR();
	float offY = (_layerSize.height - 1) * h;

	_tileToNodeTransform = Mat4
	(
		w, 0.0f, 0.0f, 0.0f,
		0.0f, -h, 0.0f, offY,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0, 0.0f, 1.0f
	);
}

void TerrainLayer::updateTotalQuads()
{
	if (_quadsDirty)
	{
		float factor = cocos2d::Director::getInstance()->getContentScaleFactor();
		float tile_width = 32 / factor;
		float tile_height = tile_width;
		float tex_width = 160.0;
		float tex_height = 160.0;
		int quad_count = 100 * 100; //方块数量

		_tileToQuadIndex.clear();
		_totalQuads.resize(quad_count);
		_indices.resize(6 * quad_count);
		_tileToQuadIndex.resize(quad_count, -1);
		_indicesVertexZOffsets.clear();

		int quadIndex = 0;
		for (int y = 0; y < 100; ++y)
		{
			for (int x = 0; x < 100; ++x)
			{
				int tiled_idx = x + y * 100;
				int tile_gid = _tiles[tiled_idx];
				if (tile_gid == 0) continue;
				_tileToQuadIndex[tiled_idx] = quadIndex;
				auto & quad = _totalQuads[quadIndex];
				Vec3 nodePos(float(x), float(y), 0);
				_tileToNodeTransform.transformPoint(&nodePos);

				float left, right, top, bottom, z;
				z = 0;

				_indicesVertexZOffsets[z] = 1;

				left = nodePos.x;
				right = nodePos.x + tile_width;
				bottom = nodePos.y + tile_height;
				top = nodePos.y;

				quad.bl.vertices.x = left;
				quad.bl.vertices.y = bottom;
				quad.bl.vertices.z = z;
				quad.br.vertices.x = right;
				quad.br.vertices.y = bottom;
				quad.br.vertices.z = z;
				quad.tl.vertices.x = left;
				quad.tl.vertices.y = top;
				quad.tl.vertices.z = z;
				quad.tr.vertices.x = right;
				quad.tr.vertices.y = top;
				quad.tr.vertices.z = z;

				//贴图坐标
				Rect tileTexture = Rect(64.0, 32.0, 32.0, 32.0);
				left = tileTexture.origin.x / tex_width;
				right = left + tileTexture.size.width / tex_width;
				bottom = tileTexture.origin.y / tex_height;
				top = bottom + tileTexture.size.height / tex_height;

				quad.bl.texCoords.u = left;
				quad.bl.texCoords.v = bottom;
				quad.br.texCoords.u = right;
				quad.br.texCoords.v = bottom;
				quad.tl.texCoords.u = left;
				quad.tl.texCoords.v = top;
				quad.tr.texCoords.u = right;
				quad.tr.texCoords.v = top;

				quad.bl.colors = Color4B::WHITE;
				quad.br.colors = Color4B::WHITE;
				quad.tl.colors = Color4B::WHITE;
				quad.tr.colors = Color4B::WHITE;

				++quadIndex;
			}
		}
		updateVertexBuffer();
		_quadsDirty = false;
	}
}

void TerrainLayer::updateVertexBuffer()
{
	GL::bindVAO(0);
	if (nullptr == _vData)
	{
		_vertexBuffer = VertexBuffer::create(sizeof(V3F_C4B_T2F), (int)_totalQuads.size() * 4);
		_vData = VertexData::create();
		_vData->setStream(_vertexBuffer, VertexStreamAttribute(0, GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 3));
		_vData->setStream(_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, colors), GLProgram::VERTEX_ATTRIB_COLOR, GL_UNSIGNED_BYTE, 4, true));
		_vData->setStream(_vertexBuffer, VertexStreamAttribute(offsetof(V3F_C4B_T2F, texCoords), GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
		CC_SAFE_RETAIN(_vData);
		CC_SAFE_RETAIN(_vertexBuffer);
	}
	if (_vertexBuffer)
	{
		_vertexBuffer->updateVertices((void*)&_totalQuads[0], (int)_totalQuads.size() * 4, 0);
	}
}

void TerrainLayer::draw(Renderer *render,const Mat4& transform, uint32_t flags)
{
	updateTotalQuads();
	bool isViewProjectionUpdated = true;

}