#pragma once
class Block : public IGameObject
{
public:
	Block();
	~Block();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}

	const Vector3& GetPosition()const
	{
		return m_position;
	}

	CollisionObject* m_collisionObject;
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

	Vector3 m_firstposition;
	Vector3 m_position;
};

