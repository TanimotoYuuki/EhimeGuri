#pragma once
class Scaffold : public IGameObject
{
public:
	Scaffold();
	~Scaffold();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	CollisionObject     *m_collisionObject;
	ModelRender			 m_modelRender;
	Vector3              m_position;
	Vector3              m_firstposition;
	PhysicsStaticObject  m_physicsStaticObject;
};

