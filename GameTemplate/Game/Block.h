#pragma once
using namespace std;

class Player;
class Config;
class Block : public IGameObject
{
public:
	Block() {};
	~Block() {};

	bool Start();// 初期化処理。
	void Update();// 更新処理。
	void Render(RenderContext& rc);// 描画処理。

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Config* m_config = nullptr;
	CollisionObject* m_collisionObject;
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

	Vector3 m_firstposition;
	Vector3 m_position;
	Vector3 m_scale = Vector3::One;
	Vector3 m_blockTouchDistanceX = Vector3::Zero;	 //ブロック叩く用距離(X軸)
	Player* m_player = nullptr;
};

