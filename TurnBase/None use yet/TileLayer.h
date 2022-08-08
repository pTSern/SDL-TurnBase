#pragma once
#include "Layer.h"
#include <string>
#include <vector>
struct TileSet
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string Name, Source;
};
using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<int> >;
class TileLayer: public Layer
{
public:
	TileLayer(int tileSize, int rowCount, int colCount, TileMap tileMap, TileSetList tileSet);
	virtual void Render();
	virtual void Update();
	inline TileMap GetTitleMap() { return m_TileMap; };
private:
	int m_TileSize;
	int m_NumRos, m_NumCol;
	TileMap m_TileMap;
	TileSetList m_TileSetList;
};

