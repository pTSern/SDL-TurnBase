#pragma once
#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1

class RigidBody
{
public:
	RigidBody()
	{
		m_Gravity = GRAVITY;
		m_Mass = UNI_MASS;
	};

	inline void SetGravity(float gravity) { m_Gravity = gravity; };
	inline void SetMass(float mass) { m_Mass = mass; };

	inline void SetForce(Vector2D force) { m_Force = force; };
	inline void SetXForce(float Fx) { m_Force.setX(Fx); };
	inline void SetYForce(float Fy) { m_Force.setY(Fy); };
	inline void UnSetForce(){m_Force = Vector2D(0,0);}

	inline void SetFriction(Vector2D friction) { m_Friction = friction; };
	inline void UnSetFrictions() { m_Friction = Vector2D(0, 0); };

	inline float GetMass() {return m_Mass; };
	inline Vector2D GetVelocity() {return m_Velocity; };
	inline Vector2D GetAcceleration() {return m_Acceleration; };
	inline Vector2D GetPosition() {return m_Position; };


	void Update(float dt)
	{
		m_Acceleration.setX((m_Force.getX() + m_Friction.getX()) / m_Mass);
		m_Acceleration.setY(m_Gravity + m_Force.getY() / m_Mass);

		m_Velocity = m_Acceleration * dt;
		m_Position = m_Velocity * dt;
	}

private:
	float m_Mass, m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Velocity;
	Vector2D m_Position;
	Vector2D m_Acceleration;

};
