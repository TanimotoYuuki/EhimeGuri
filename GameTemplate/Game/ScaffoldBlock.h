#pragma once
class ScaffoldBlock : public IGameObject
{
public:
	ScaffoldBlock();
	~ScaffoldBlock();

	void Update();
	void Render(RenderContext & rc);

	Vector3		m_position;
	Vector3		firstposition;
private:
	
	ModelRender	m_modelRender;
	Quaternion	m_Rot;

};

