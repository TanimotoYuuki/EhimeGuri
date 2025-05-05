#pragma once
#include "GameOver.h"

class Player;
class MovingFloor;
class GameOver;
class Fade;
class Needle : public IGameObject
{
	/// <summary>
	/// 針。
	/// </summary>
public:
	Needle();
	~Needle();

	bool Start();
	void Update();
	void DisplayModel();
	void Render(RenderContext& rc);

	Vector3	firstposition;
	Vector3	m_needlePosition;
	ModelRender m_modelRender;
	Quaternion m_rotation;
	SpriteRender m_spriteRender;
	MovingFloor* m_movingFloor;
	GameOver* m_gameOver;
	Fade* m_fade;
	Player* m_player;
	PhysicsStaticObject physicsStaticObject;
	int m_needleCount = 0;
	bool flag = true;
	bool m_gameOverFlag = false;
private:
	CollisionObject* m_collisionObject = nullptr;

	// 移動方向を決めるステート
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,// 左。
		enMovingFloorState_MovingLeft// 右。
	};

	// ステートの初期化。
	enMovingFloorState	m_movingFloorState = enMovingFloorState_MovingRight;
};

