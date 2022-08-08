#include "MenuButton.h"
static Register<MenuButton> s_register("MENUBUTTON");
MenuButton::MenuButton(const Properties* pProperties ) :GameObject(pProperties)
{
	m_currentFrame = MOUSE_OUT;
	m_isPicked = false;
	m_callBackID = pProperties->getCallBackID();
	m_index = pProperties->getIndex();
}
void MenuButton::Draw()
{
	GameObject::Draw();
}

void MenuButton::Update(float dt)
{
	m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);

	Transform* pMousePos = Input::GetInstance()->GetMousePosition();
	if (pMousePos->X < (m_pTransform->X + m_width) 
		&& pMousePos->X > m_pTransform->X
		&& pMousePos->Y < (m_pTransform->Y + m_height)
		&& pMousePos->Y > m_pTransform->Y)
	{
		m_currentFrame = MOUSE_OVER;
		if (Input::GetInstance()->GetMouseButtonState(LEFT) && m_bReleased && !m_isPicked)
		{
			m_currentFrame = CLICKED;
			m_pCallBack(m_index);
			m_bReleased = false;
			m_currentRow = 99;
			m_isPicked = true;
		}
		else if (Input::GetInstance()->GetMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;

		}
		else
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OUT;
		}
	}
	
	m_pAnimation->Update();
	//delete pMousePos;
}

void MenuButton::Clean()
{
	GameObject::Clean();
}