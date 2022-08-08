#pragma once
#include "Properties.h"
class AGameObject
{
public:
	AGameObject(const Properties* pProperties) {};
	//virtual ~AGameObject() = 0;
	virtual void Draw() = 0;
	virtual void Update(float dt) = 0;
	virtual void Clean() = 0;

	//virtual void Load(const Properties* prosperties) = 0;
protected:
	
};