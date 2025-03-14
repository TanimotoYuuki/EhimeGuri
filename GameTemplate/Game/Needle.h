#pragma once

class Player;
class Needle : public IGameObject
{
public:
	Needle();
	~Needle();

	void Update();
	void Render(RenderContext& rc);

	int					m_needleCount = 0;

	Player				*m_player;

	Vector3				firstposition;
	Vector3				m_needlePosition;
	ModelRender			m_modelRender;
	Quaternion			m_rotation;
	SpriteRender		m_spriteRender;
private:
	PhysicsStaticObject physicsStaticObject;
	

};

