#pragma once
class Config;
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
	Vector3 m_position;
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

};

