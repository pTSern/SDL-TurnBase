#pragma once
#include "GameState.h"
#include <vector>
class MenuState : public GameState
{
protected:
	//typedef std::vector<std::vector<Champion*>> (*Callback)();
	typedef void(*Callback)(int index);
	virtual void setCallbacks(const std::vector<Callback>& callbacks)= 0;
	std::vector<Callback> m_callbacks;
	//std::vector<std::string> m_textureIDList;
	
};