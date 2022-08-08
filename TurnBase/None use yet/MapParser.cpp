#include "MapParser.h"
bool MapParser::Load()
{
	return (Pare("battle", "assets/map.tmx"));
}

bool MapParser::Pare(std::string id, std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error())
	{
		std::cerr << "Failed to load: " << source << std::endl;
		return false;
	}

	TiXmlElement* root = xml.RootElement();

	int rowCount, colCount, tileSize = 0;

	root->Attribute("width", &colCount);
	root->Attribute("height", &rowCount);
	root->Attribute("tilewidth", &tileSize);

	TileSetList tileSet;
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("tileset"))
		{
			tileSet.push_back(PareTileSet(e));
			break;
		}
	}

	GameMap* gameMap = new GameMap();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("layer"))
		{
			TileLayer* tileLayer = PareTileLayer(e, tileSet, tileSize, rowCount, colCount);
			gameMap->m_MapLayers.push_back(tileLayer);
		}
	}

	m_MapDict[id] = gameMap;
	return true;
}

TileLayer* MapParser::PareTileLayer(TiXmlElement* xmlLayer, TileSetList tileSet, int tileSize, int rowCount, int colCount)
{
	TiXmlElement* data;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data")) 
		{
			data = e;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tileMap(rowCount, std::vector<int>(colCount, 0));

	for (int row = 0; row = rowCount; row++)
	{
		for (int col = 0; col = colCount; col++)
		{
			getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tileMap[row][col];

			if (!iss.good()) break;
		}
	}

	return (new TileLayer(tileSize, rowCount, colCount, tileMap, tileSet));
}
TileSet MapParser::PareTileSet(TiXmlElement* xmlTileSet)
{
	TileSet tileSet;
	xmlTileSet->Attribute("name");
	xmlTileSet->Attribute("firstgid", &tileSet.FirstID);
	xmlTileSet->Attribute("tilecount", &tileSet.TileCount);
	
	tileSet.LastID = (tileSet.FirstID + tileSet.TileCount) - 1;

	xmlTileSet->Attribute("columns", &tileSet.ColCount);
	tileSet.RowCount = (tileSet.TileCount / tileSet.ColCount);

	xmlTileSet->Attribute("tilewidth", &tileSet.TileSize);

	TiXmlElement* image = xmlTileSet->FirstChildElement();
	tileSet.Source = image->Attribute("source");

	return tileSet;
}
void MapParser::Clean()
{

}