#pragma once
using namespace std;

class Config;
class Scaffold : public IGameObject
{
public:
	/// <summary>
	/// 看板。
	/// </summary>
	Scaffold() {};
	~Scaffold() {};

	bool Start();
	void Update();// 更新作業。
	void Render(RenderContext& rc);// 描画処理。

	Config* m_config;
	CollisionObject* m_collisionObject;
	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 m_firstposition;
	PhysicsStaticObject m_physicsStaticObject;
};

