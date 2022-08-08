#pragma once
#include "AGameObject.h"
#include "Transform.h"
#include "Animation.h"
#include "RigidBody.h"
#include "TextureManager.h"

class GameObject : public AGameObject
{
public:
	GameObject(const Properties* pProperties);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	
protected:
	Transform* m_pTransform;
	int m_width, m_height;
	std::string m_textureID;
	SDL_RendererFlip m_flip;
	int m_currentRow;
	
	int m_animationSpeed;
	int m_frameCount;
	int m_currentFrame;
	Animation* m_pAnimation;
	RigidBody* m_pRigidBody;
};
