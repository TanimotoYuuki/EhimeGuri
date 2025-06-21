#pragma once
#include "MovingFloor.h"
using namespace std;

class Player;
class MovingFloor;
class GameOver;
class Config;
class FallingBlock : public IGameObject
{
	/// <summary>
	/// 落下する床
	/// </summary>
public:
	FallingBlock() {};
	~FallingBlock() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();


	/// <summary>
	/// 座標のセット
	/// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// 座標を取得
	/// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Config* m_config = nullptr;
	Vector3 m_position;
	Vector3	m_firstposition;
	Vector3	fallingSpeed;
	Vector3 m_initPosition;
	Vector3 distanceX;
	Vector3 distanceY;



	FontRender m_fontRender;
	ModelRender m_modelRender;
	ModelRender	m_HightSpeedFallingBlock_Render;
	PhysicsStaticObject	m_physicsStaticObject;
	Player* m_player = nullptr;
	MovingFloor* m_movingFloor = nullptr;
	GameOver* m_gameOver = nullptr;


private:
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject* m_collisionObject = nullptr;
};

