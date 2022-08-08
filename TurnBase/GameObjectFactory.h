#pragma once
#include "GameObject.h"
#include <string>
#include <map>
#include <functional>
class GameObjectFactory
{
public:
	static GameObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameObjectFactory(); }
	bool RegisterType(std::string typeID, std::function<GameObject* (Properties* pProperties)> pCreator);
	GameObject* Create(std::string typeID, Properties* pProperties);
private:
	GameObjectFactory() {};
	std::map<std::string, std::function<GameObject*(Properties* pProperties)>> m_creators;
	static GameObjectFactory* s_Instance;
};

template<class Type>
class Register
{
public:
	Register(std::string className) 
	{
		GameObjectFactory::GetInstance()->RegisterType(className, [](Properties* pProperties)->GameObject* {return new Type(pProperties); });
	};

};
