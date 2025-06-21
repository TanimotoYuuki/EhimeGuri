#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"

namespace
{
	const Vector3 CAMERA_POS(0.0f, 200.0f, -800.0f);
	const float CAMERA_NEAR(1.0f);
	const float CAMERA_FAR(10000.0f);
}

GameCamera::GameCamera() {

}

GameCamera::~GameCamera() {

}

bool GameCamera::Start() {
	//注視点から視点までのベクトルを設定。
	SetToCameraPos(CAMERA_POS);

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(CAMERA_NEAR);
	g_camera3D->SetFar(CAMERA_FAR);

	//注視点の初期化
	m_cameraTarget.x = m_player->m_position.x;
	m_cameraTarget.y = m_player->m_position.y;
	m_cameraTarget.z = m_player->m_position.z;
	g_camera3D->SetTarget(m_cameraTarget);

	//ライトカメラの更新
	g_renderingEngine->SetLightCameraTarget(Vector3(m_player->m_position.x, m_cameraTarget.y, m_cameraTarget.z));

	return true;
}
void GameCamera::Update() {
	if (m_player == nullptr) {
		return;
	}

	//カメラを更新。
	//注視点を計算する。
	//左スティックを右に倒しているとき注視点(X軸)を動かす
	if (g_pad[0]->GetLStickXF() >= 0.0f)
	{
		//プレイヤーが注視点の現在位置より移動していたら注視点を動かす
		if (m_player->m_position.x >= m_cameraTarget.x)
		{
			//注視点(X軸)
			m_cameraTarget.x = m_player->m_position.x;
		}
	}

	//プレイヤーがリスポーンしたら注視点(X軸)を動かす　または
	//ステージ遷移フラグがtrueになっていたら注視点(X軸)を動かす
	if (m_player->IsPlayerRespawn() || m_stageTransitionFlag == true)
	{
		//注視点(X軸)
		m_cameraTarget.x = m_player->m_position.x;
		m_stageTransitionFlag = false;
	}

	//注視点(Y軸)
	m_cameraTarget.y = m_player->m_position.y;

	//一定の高さまで落ちたら注視点を動かさない
	if (m_cameraTarget.y <= m_player->m_initPosition.y)
	{
		//注視点(Y軸)
		m_cameraTarget.y = m_player->m_initPosition.y;
	}

	//注視点(Z軸)
	m_cameraTarget.z = m_player->m_position.z;

	//左画面端の計算
	m_leftScreenEdge = m_cameraTarget;
	m_leftScreenEdge.x = m_cameraTarget.x - (((FRAME_BUFFER_H / 2) + 50.0f) * m_toCameraPosmultiplier);

	//左スティックを左に倒しているときに左画面端まで行ったらプレイヤーを移動できないようにする
	if (g_pad[0]->GetLStickXF() < 0.0f)
	{
		//左画面端に行ったら
		if (m_player->m_position.x <= m_leftScreenEdge.x)
		{
			//プレイヤーの現在位置を固定する
			m_player->m_characterController.SetPosition(Vector3(m_leftScreenEdge.x, m_player->m_position.y, m_player->m_position.z));
			m_player->m_modelRender.SetPosition(Vector3(m_leftScreenEdge.x, m_player->m_position.y, m_player->m_position.z));
			m_player->m_modelRender.Update();
		}
	}
	//プレイヤの足元からちょっと上を注視点とする。
	m_cameraTarget.y += 80.0f;

	//視点を計算する。
	Vector3 pos = m_cameraTarget + m_toCameraPos;
	m_cameraTarget.Lerp(0.05f, m_cameraTarget, pos);

	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(m_cameraTarget);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();

	//ライトカメラの更新
	g_renderingEngine->SetLightCameraTarget(Vector3(m_player->m_position.x, m_cameraTarget.y, m_cameraTarget.z));
}