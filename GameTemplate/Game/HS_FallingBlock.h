#pragma once
using namespace std;

class GameOver;
class Player;
class Config;
class MovingFloor;
class HS_FallingBlock : public IGameObject
{
public:
	/// <summary>
    /// 落下速度の速い床
    /// </summary>

	HS_FallingBlock() {};
	~HS_FallingBlock() {};

	bool Start();
	void Update();// 更新作業。
	void Move();//動作処理
	void Render(RenderContext& rc);//描画処理。 
	
	Config* m_config;
	ModelRender	m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Vector3	m_firstposition;
	Vector3 m_position;

	MovingFloor* m_movingFloor;
	GameOver* m_gameOver;
	Player* m_player;

private:
	// 移動方向を切り替えるステート。
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,// 右。
		enMovingFloorState_MovingLeft// 左。
	};

	// ステートの初期化。 
	enMovingFloorState m_movingFloorState = enMovingFloorState_MovingRight;
	CollisionObject* m_collisionObject = nullptr;
};



