#include "stdafx.h"
#include "FallingRocks.h"
#include "Config.h"
using namespace std;

//FallingRocks::FallingRocks() : position(0.0f, 0.0f, 0.0f), velocity(0.0f, 0.0f, 0.0f), gravity(0.0f, -9.8f, 0.0f)
//{
//
//}

bool FallingRocks::Start()
{
	string modelPath = m_config->GetFullPath_3DModel("FallingRocks");// ファイルパスを読み込む。
	m_modelRender.Init(modelPath.c_str());// モデルをセットする。

	m_modelRender.Update(); // モデルを更新する。
	return true;
}

// 更新処理。
void FallingRocks::Update()
{
	// 時間を取得する(1フレームあたりの固定値)。
	float deltaTime = 1.0f / 60.0f;

	// 重力による速度の更新
	velocity += gravity * deltaTime;

	// 座標の更新。
	position += velocity * deltaTime;

	//関数の更新。
	Move();

	m_modelRender.Update();
}

// 動作処理。
void FallingRocks::Move()
{

}

// 描画処理。
void FallingRocks::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}