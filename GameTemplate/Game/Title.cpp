#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	//m_titleBackGround.Init("Assets/Sprite/Title.DDS", 1920, 1080);

	//アニメーションの初期化
	InitAnimation();

	//モデルの初期化
	InitModel();

	//スプライトの初期化
	InitSprite();

	//カメラの初期化
	InitCamera();
}

Title::~Title()
{

}

void Title::Update()
{
	//プレイヤー側の操作
	if (g_gameTime->StopWatch(0.8f) == true)
	{
		m_startFadeFinishFlag = true;
	}
	else if (m_startFadeFinishFlag == true)
	{
		Action();
	}

	//ゲームスタートフラグが立っているとき
	if (m_gameStartFlag == true)
	{
		//プレイヤーモデルの動作
		PlayerModelMove();
	}

	//カメラの更新
	UpdateCamera();

	//アニメーション管理
	AnimationManage();

	//アニメーション再生
	PlayAnimation();

	m_playerModel.Update();
	m_fade.Update();
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	NewGO<Game>(0, "game");
	//	DeleteGO(this);
	//}
}

void Title::Render(RenderContext& rc)
{
	//m_titleBackGround.Draw(rc);
	m_playerModel.Draw(rc);
	m_fade.Draw(rc);
}

void Title::Action()
{
	if (m_gameStartFlag != true)
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_gameStartFlag = true;
		}
	}
	else
	{
		//画面端に行ったら
		if (m_playerModelPosition.x > FRAME_BUFFER_W / 2)
		{
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}
}

void Title::InitAnimation()
{
	//0.歩くアニメーション
	m_animationClip[enAnimationClip_walk].Load("Assets/animData/playerwalk.tka");
	m_animationClip[enAnimationClip_walk].SetLoopFlag(true);
	//1.走るアニメーション
	m_animationClip[enAnimationClip_run].Load("Assets/animData/playerrun.tka");
	m_animationClip[enAnimationClip_run].SetLoopFlag(true);
}

void Title::InitModel()
{
	//0. プレイヤーモデルの初期化
	m_playerModel.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);
	//0.1 位置を設定
	m_playerModel.SetPosition(m_playerModelPosition);

	//0.2 回転を設定
	m_playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(m_playerModelRotation);

	//0.3 大きさを設定
	m_playerModel.SetScale(m_playerModelScale);
	Quaternion playerModelRotation;
	playerModelRotation.SetRotationDegY(90.0f);
	m_playerModel.SetRotation(playerModelRotation);
	m_playerModel.Update();
}

void Title::InitSprite()
{
	m_fade.Init("Assets/title/screen/startfade.dds", 1600, 900);
	m_fade.SetLinearWipeDrawingMode(LinearWipeDrawingMode_Round);
	m_fade.SetWipeScrollSpeed(20.0f);
}

void Title::InitCamera()
{
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);
}

void Title::PlayerModelMove()
{
	m_playerModelPosition.x += 7.5f;
	m_playerModel.SetPosition(m_playerModelPosition);
}

void Title::UpdateCamera()
{
	if (m_gameStartFlag != true)
	{
		//カメラの位置
		Vector3 CameraPosition = m_playerModelPosition + Vector3(0.0f, 100.0f, -500.0f);
		//カメラの注視点
		Vector3 CameraTarget = m_playerModelPosition;
		CameraTarget.y += 100.0f;

		//カメラの位置を設定
		g_camera3D->SetPosition(CameraPosition);
		//カメラの注視点を設定
		g_camera3D->SetTarget(CameraTarget);
	}
}

void Title::AnimationManage()
{
	//プレイヤーモデル
	PlayerModelAnimationManage();
}

void Title::PlayAnimation()
{
	//プレイヤーモデル
	PlayerModelPlayAnimation();
}

void Title::PlayerModelAnimationManage()
{
	if (m_gameStartFlag == true)
	{
		m_playerModelAnimationState = enPlayerModelAnimationState_run;
	}
	else
	{
		m_playerModelAnimationState = enPlayerModelAnimationState_walk;
	}
}

void Title::PlayerModelPlayAnimation()
{
	switch (m_playerModelAnimationState)
	{
	case enPlayerModelAnimationState_walk:	//歩くアニメーション
		m_playerModel.PlayAnimation(enAnimationClip_walk);
		break;
	case enPlayerModelAnimationState_run:	//走るアニメーション
		m_playerModel.PlayAnimation(enAnimationClip_run);
		break;
	default:
		break;
	}
}