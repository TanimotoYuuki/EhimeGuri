#pragma once

using namespace std;

class Config;
class BackGround : public IGameObject
{
public:
	BackGround() {};
	~BackGround() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);// 描画処理。

	Config* m_config;
	ModelRender m_backGroundRender;// モデル描画。
	PhysicsStaticObject m_physicsSraricObject;// 静的物理オブジェクト。
	PhysicsStaticObject m_physicsStaticObject;

};

