#include "GameObjectFactory.h"
GameObjectFactory * GameObjectFactory::s_Instance = nullptr;
bool GameObjectFactory::RegisterType(std::string typeID, std::function<GameObject* (Properties* pProperties)> pCreator)
{
	auto it = m_creators.find(typeID);
	// if the type is already registered, do nothing
	if (it != m_creators.end())
	{
		return false;
	}
	m_creators[typeID] = pCreator;
}
GameObject* GameObjectFactory::Create(std::string typeID, Properties* pProperties)
{
	auto it = m_creators.find(typeID);
	if (it == m_creators.end())
	{
		return NULL;
	}
	return it->second(pProperties);
}