#pragma once
#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "Vender/tinyxml.h"

class MapParser
{
public:
	inline static MapParser* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new MapParser();
	}

	bool Load();
	void Clean();

	inline GameMap* GetMaps(std::string id) { return m_MapDict[id]; };
	
private:
	MapParser() {};
	static MapParser* s_pInstance;
	std::map<std::string, GameMap*> m_MapDict;

	TileLayer* PareTileLayer(TiXmlElement* xmlLayer, TileSetList tileSet, int tileSize, int rowCount, int colCount);
	bool Pare(std::string id, std::string source);
	TileSet PareTileSet(TiXmlElement* xmlTileSet);
};

