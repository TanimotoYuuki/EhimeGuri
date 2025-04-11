#pragma once
class Towel : public IGameObject
{
public:
	Towel();
	~Towel();

	bool Start();
	void Update();
	void Rotation();
	void Render(RenderContext& rc);

	void SetPosition(const Vector3 position)
	{
		m_position = position;
	}
		
	ModelRender m_modelRender;
	Vector3     m_position;
	Vector3     m_firstposition;
	Quaternion  m_Rot;
};

