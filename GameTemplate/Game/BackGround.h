#pragma once
class BackGround : public IGameObject
{
public:
	BackGround() {};
	~BackGround() {};

	bool Start();
	void Render(RenderContext& rc);// 描画処理。

	ModelRender m_backGroundRender;// モデル描画。
	PhysicsStaticObject m_physicsSraricObject;// 静的物理オブジェクト。
};

