#pragma once
#include "MovingFloor.h"

class Player;
class MovingFloor;
class GameOver;
class FallingBlock : public IGameObject
{
public:
	FallingBlock();
	~FallingBlock();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();



	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Vector3										m_position;
	Vector3										m_firstposition;
	Vector3										fallingSpeed;
	Vector3										m_initPosition;

	FontRender									m_fontRender;
	ModelRender									m_modelRender;
	ModelRender									m_HightSpeedFallingBlock_Render;
	PhysicsStaticObject							m_physicsStaticObject;
	Player									  * m_player;
	MovingFloor								  * m_movingFloor;
	GameOver								  * m_gameOver;


private:
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState							m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject							  * m_collisionObject = nullptr;
};

