#pragma once
class ScaffoldBlock : public IGameObject
{
public:
	ScaffoldBlock();
	~ScaffoldBlock();

//	bool Start();
	void Update();
	void Render(RenderContext & rc);


	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
	Vector3		m_position;
	Vector3		firstposition;
private:
	PhysicsStaticObject	m_physicsStaticObject;
	ModelRender			m_modelRender;
	Quaternion			m_Rot;

};

