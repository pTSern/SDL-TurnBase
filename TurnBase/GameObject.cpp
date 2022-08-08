#include "GameObject.h"

//void GameObject::Load(const Properties* pProperties)
GameObject::GameObject(const Properties* pProperties) : AGameObject(pProperties)
{
	m_textureID = pProperties->getTextureID();
	m_width = pProperties->getWidth();
	m_height = pProperties->getHeight();
	m_flip = pProperties->getFlip();
	m_frameCount = pProperties->getFrameCount();
	m_pTransform = new Transform(pProperties->getX(), pProperties->getY());

	m_pAnimation = new Animation();
	m_pRigidBody = new RigidBody();

	m_currentRow = pProperties->getCurrentRow();;
	m_currentFrame = pProperties->getCurrentFrame();
	m_animationSpeed = 80;

	m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip, m_currentFrame);
};
//void GameObject::Draw(Animation* pAnimation)
//{
//	m_pAnimation = pAnimation;
//	m_pAnimation->Draw(m_pTransform->X, m_pTransform->Y, m_Width, m_Height);
//}
void GameObject::Draw()
{	
	m_pAnimation->Draw(m_pTransform->X, m_pTransform->Y, m_width, m_height);
}
void GameObject::Update(float dt)
{
	m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);
	m_pAnimation->Update();
}
void GameObject::Clean()
{
	delete m_pAnimation;
	delete m_pRigidBody;
	delete m_pTransform;
	TextureManager::GetInstance()->Clean();
}