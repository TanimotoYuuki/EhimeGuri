#pragma once
class Player;
class FallingBlock : public IGameObject
{
public:
	FallingBlock();
	~FallingBlock();

	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();

	void SetPosition(const Vector3 position)
	{
		f_position = position;
	}

	Vector3										f_position;
	Vector3										firstposition;

	ModelRender									m_modelRender;
	PhysicsStaticObject							m_physicsStaticObject;
	Player    * m_player;
private:
	CharacterController	charactercontroller;
};

