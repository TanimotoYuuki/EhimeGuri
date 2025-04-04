#pragma once

//ŠÅ”Â
class Signboard : public IGameObject
{
public:
	Signboard();
	~Signboard();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender          m_modelRender;
	Vector3			     m_position;
	Vector3				 m_firstposition;
	PhysicsStaticObject  m_physicsStaticObject;
	Quaternion			 m_Rot;
};

