#pragma once
#include "GameObject.h""
#include <SDL.h>
#include "Input.h"
#include "Champion.h"
#include "GameObjectFactory.h""
class MenuButton : public GameObject
{
public:
	MenuButton(const Properties* properties);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	void setCallback(void (*callback)(int index)) { m_pCallBack = callback; }
	int getCallbackID() { return m_callBackID; }
	bool getIsPicked() {return m_isPicked; }
private:
	void (*m_pCallBack) (int index);
	int m_callBackID, m_index;
	
	bool m_bReleased;
	bool m_isPicked;

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};
};

