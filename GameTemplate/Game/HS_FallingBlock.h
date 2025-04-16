#pragma once
class GameOver;
class Player;
class MovingFloor;
class HS_FallingBlock : public IGameObject
{
public:
	HS_FallingBlock();
	~HS_FallingBlock();

	bool Start();
	void Update();
	void Move();
	void Render(RenderContext& rc);
	
	ModelRender            m_modelRender;
	MovingFloor			 * m_movingFloor;
	GameOver	         * m_gameOver;
	Player				 * m_player;
	PhysicsStaticObject	   m_physicsStaticObject;
	Vector3				   m_firstposition;
	Vector3				   m_position;

private:
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState	  m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject     * m_collisionObject = nullptr;
};

