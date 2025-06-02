#pragma once

using namespace std;

class Config;
class Stage1 : public IGameObject
{
public:
	Stage1() {};
	~Stage1() {};

	bool Start();
	void Update();
	void Render(RenderContext& rc);// 描画処理。

	Config* m_config = nullptr;
	ModelRender m_backGroundRender;// モデル描画。
	PhysicsStaticObject m_physicsSraricObject;// 静的物理オブジェクト。


};

