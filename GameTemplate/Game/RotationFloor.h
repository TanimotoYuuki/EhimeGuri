#pragma once
class Config;
class Player;
class RotationFloor : public IGameObject
{
public:
	RotationFloor() {};
	~RotationFloor() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();
	/// <summary>
    /// 座標のセット。
    /// </summary>
	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	/// <summary>
	/// 座標を取得。
	/// </summary>
	const Vector3& GetPosition()const
	{
		return m_position;
	}

	Config* m_filePathConfig;
	CollisionObject* m_collisionObject;
	Player* m_player = nullptr;
	Vector3 m_position;
	Vector3 m_distance;//距離
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Quaternion m_Rot;
};

