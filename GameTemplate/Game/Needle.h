#pragma once
#include "GameOver.h"

class Player;
class MovingFloor;
class GameOver;
class Needle : public IGameObject
{
public:
	Needle();
	~Needle();

	bool Start();
	void Update();
	void DisplayModel();
	void Render(RenderContext& rc);

	int					m_needleCount = 0;
	bool				flag = true;
 
	
	
	Player			   *m_player;

	Vector3				firstposition;
	Vector3				m_needlePosition;
	ModelRender			m_modelRender;
	Quaternion			m_rotation;
	SpriteRender		m_spriteRender;
	MovingFloor       * m_movingFloor;
	GameOver          * m_gameOver;
	PhysicsStaticObject physicsStaticObject;
private:
	CollisionObject* m_collisionObject = nullptr;
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState	m_movingFloorState = enMovingFloorState_MovingRight;
	

};

