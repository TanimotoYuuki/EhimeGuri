#pragma once
class ScaffoldBlock : public IGameObject
{
public:
	ScaffoldBlock();
	~ScaffoldBlock();

	bool Start();
	void Update();
	void Render(RenderContext & rc);

	
	
	ScaffoldBlock	  * m_ScaffoldBlock;
	Vector3				m_ScaffoldBlock_position;
	Vector3				m_position;
	Vector3				firstposition;
	SpriteRender		m_spriteRender;
	ModelRender			m_modelRender;
	Quaternion			m_Rot;
private:
	PhysicsStaticObject	physicsStaticObject;
	
	
};

