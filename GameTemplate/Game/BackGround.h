#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender m_backGroundRender;
	PhysicsStaticObject m_physicsSraricObject;
};

