#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Config.h"
#include "GameOver.h"
#include "Enemy.h"
#include "Towel.h"
#include "ItemEnemy.h"
#include "Fade.h"
using namespace std;

namespace 
{
	// スタミナの最大値。
	const float SUTAMINA_MAX = 300.0f;

	// キャラコンの定数。
	const float RADIUS = 25.0f;
	const float HEIGHT = 100.0f;

	// モデルの回転度数。
	const float ROTATIONDEG = 90.0f;
	const float ROTATIONDEG2 = 180.0f;

	// モデルにかかる重力。
	const float GLAVITY = 15.0f;

	// モデルの大きさ。
	const Vector3 SCALE(0.5f, 0.5f, 0.5f);

	// モデルの初期座標。
	const Vector3 FIRSTPOSITION(0.0f, 94.0f, 0.0f);
//  const Vector3 FIRSTPOSITION(-600.0f, 0.0f, 0.0f);
}

// アニメーションメソッド。
const std:: string Player::GetFullPath_PlayerAnimation(EnAnimationClip enAnimationClip, const std::string& animationName, bool flag)
{
    std::string Animation = PLAYER_ANIMATION + animationName + ANIMATION_FILE_EXTENSION;

	// アニメーションのロード。
	m_animationClip[enAnimationClip].Load(Animation.c_str());
	m_animationClip[enAnimationClip].SetLoopFlag(flag);

	return Animation;
};

// 初期化処理。
bool Player::Start()
{
	// アニメーションをセットするメソッド。
	SetPlayAnimation();
	
	// モデルをセット。
	m_modelRender.Init("Assets/modelData/player/player.tkm", m_animationClip,
		enAnimationClip_num, enModelUpAxisZ, true);

	// 大きさをセット。
	m_modelRender.SetScale(SCALE);

	// 初期座標。
	//m_position = { FIRSTPOSITION };

	m_position = { 17300.0f, 700.0f, 0.0f };

	m_initPosition = m_position;

	m_characterController.Init(RADIUS, HEIGHT, m_position);
	m_rotation.SetRotationDegY(ROTATIONDEG);
	m_respawnRotation.SetRotationDegY(ROTATIONDEG);

	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.Update();

	//アニメーションイベント
	m_modelRender.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);
		});

	m_game = FindGO<Game>("game");
	m_fade = FindGO<Fade>("fade");

	return true;
}

// 更新処理。
void Player::Update()
{
	//フェード用のインスタンスがnullptrだったら
	if (m_fade == nullptr)
	{
		//Fadeクラスの検索。
		FadeFindGO();
	}

	//ItemEnemyクラスの検索が終わっていないときに処理する。
	if (m_itemEnemyFindGoCompleteFlag != true)
	{
		//ItemEnemyクラスの検索。
		ItemEnemyFindGO();
	}

	if (checcount == 0) 
	{
		//現在ステージ1をプレイしていたら
		if (m_game->GetStageState() == m_game->enStageState_Stage1)
		{
			//リスポーン地点の設定。
			SetRespawnPositon(Vector3{ 0.0f,94.0f,0.0f });
		}
		//現在ステージ2をプレイしていたら
		else if (m_game->GetStageState() == m_game->enStageState_Stage2)
		{
			//リスポーン地点の設定。
			SetRespawnPositon(Vector3{ 0.0f,160.0f,0.0f });
		}

	}

	else if (checcount == 1) 
	{
		//現在ステージ1をプレイしていたら
		if (m_game->GetStageState() == m_game->enStageState_Stage1)
		{
			//リスポーン地点の設定。
			SetRespawnPositon(Vector3{ 0.0f,94.0f,0.0f });
		}
		//現在ステージ2をプレイしていたら
		else if (m_game->GetStageState() == m_game->enStageState_Stage2)
		{
			//リスポーン地点の設定。
			SetRespawnPositon(Vector3{ 0.0f,160.0f,0.0f });
		}

	}

	if (m_playernowsutamina == 0) {
		m_sutaminaZeroFlag = true;
	}

	if (m_sutaminaZeroFlag == true) {
		Derei();
	}

	// 動作処理。
	Move();

	// 回転処理。
	Rotation();

	// ステート。
	ManageState();

	// アニメーション。
	PlayAnimation();

	// 更新処理。
	m_modelRender.Update();

}

//Fadeクラスの検索。
void Player::FadeFindGO()
{
	m_fade = FindGO<Fade>("fade");
}


//ItemEnemyクラスの検索。
void Player::ItemEnemyFindGO()
{
	m_itemEnemy = FindGO<ItemEnemy>("itemenemy");
	m_itemEnemyFindGoCompleteFlag = true;
}

// 動作処理。
void Player::Move() {
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	Vector3 stickL;

	//以下の条件になっていたらプレイヤーを動かすことができる
	if ((m_stageClearFlag != true && m_gameOverFlag != true) &&		//ゲームクリアまたはゲームオーバーになっていないとき
		(m_fade->IsFadeInFinish())	//フェードインが終わったら
		)
	{
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();
	}
	
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	
	forward.y = 0.0f;
	right.y = 0.0f;

	right *= stickL.x * 480.0f;
	forward *= stickL.y * 0.0f;
	
	m_moveSpeed += right + forward;
	
	if (m_stageClearFlag != true && m_gameOverFlag != true)
	{
		if (g_pad[0]->IsPress(enButtonB) && m_playernowsutamina > 0 && m_sutaminaZeroFlag == false && m_characterController.IsOnGround()) {
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 0.0f;
		}
	}


	
	if (m_characterController.IsOnGround())
	{
		
		m_moveSpeed.y = 0.0f;	

		//以下の条件になっていたらプレイヤーを動かすことができる
		if ((m_stageClearFlag != true && m_gameOverFlag != true) &&		//ゲームクリアまたはゲームオーバーになっていないとき
			(m_fade->IsFadeInFinish())	//フェードインが終わったら
			)
		{
			if (g_pad[0]->IsTrigger(enButtonA)) {

				m_moveSpeed.y = 525.0f;

				//ジャンプした時の音の再生。
				g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_Jump, 2.0f);
			}
		}
	}
	
	m_moveSpeed.y -= GLAVITY;

	//ゲームクリアまたはゲームオーバーではないとき処理する。
	if (m_stageClearFlag != true && m_gameOverFlag != true)
	{
		//一定の高さまで落ちたらリスポーンする。
		if (m_position.y <= -500.0f) {
			PlayerRespawn();
			return;
		}
		
		//複数のEnemyクラスの検索。
		const auto& enemys = FindGOs<Enemy>("enemy");
		for (auto enemy : enemys)
		{
			//敵がプレイヤーに触れたらリスポーンする
			if (enemy->m_touchPlayerFlag == true)
			{
				PlayerRespawn();
				enemy->m_touchPlayerFlag = false;
				return;
			}
		}

		//アイテムをドロップする敵がプレイヤーに触れたらリスポーンする。
		if (m_itemEnemy->m_touchPlayerFlag == true)
		{
			PlayerRespawn();
			m_itemEnemy->m_touchPlayerFlag = false;
			return;
		}

		//プレイヤーのリスポーンが終わったらリスポーン用フラグをfalseにする。
		if (IsPlayerRespawn())
		{
			m_respawnFlag = false;
			
			//プレイヤーがミスした時の音の再生。
			g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_Miss, 1.0f);
		}
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	

	m_position.z = 0.0f;
	m_characterController.SetPosition(m_position);

	m_modelRender.SetPosition(m_position);


}

// 回転処理。
void Player::Rotation() {
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}
}

// ステート。
void Player::ManageState() {
	if (m_stageClearFlag == true)
	{
		m_playerState = enPlayer_stageclear;
		m_rotation.SetRotationDegY(ROTATIONDEG2);
		m_modelRender.SetRotation(m_rotation);
		return;
	}
	else if (m_gameOverFlag == true)
	{
		m_playerState = enPlayer_gameover;
		return;
	}

	if (m_characterController.IsOnGround() == false) {
		m_playerState = enPlayer_jump;
		PlayerhealSutamina();
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.001f|| fabsf(m_moveSpeed.z) >= 0.001f){
		if (g_pad[0]->IsPress(enButtonB)&&m_playernowsutamina>0&&m_sutaminaZeroFlag==false) {
			m_playerState = enPlayer_run;
			PlayerStamina();
		}
		else {
			m_playerState = enPlayer_walk;
			PlayerhealSutamina();
		}
	}
	else {
		m_playerState = enPlayer_idle;
		PlayerhealSutamina();
	}
}

// アニメーション再生する。
void Player::PlayAnimation() {
	switch (m_playerState) {
	case enPlayer_idle:
		m_modelRender.PlayAnimation(enAnimationClip_idle,0.1f);
		break;
	case enPlayer_walk:
		m_modelRender.PlayAnimation(enAnimationClip_walk,0.1f);
		m_moveSpeed.z *= 0.0f;
		break;
	case enPlayer_jump:
		m_modelRender.PlayAnimation(enAnimationClip_jump,0.1f);
		break;
	case enPlayer_run:
		m_modelRender.PlayAnimation(enAnimationClip_run,0.1f);
		m_moveSpeed.z *= 0.0f;
		break;
	case enPlayer_stageclear:
		m_modelRender.PlayAnimation(enAnimationClip_stageclear, 0.1f);
		break;
	case enPlayer_gameover:
		m_modelRender.PlayAnimation(enAnimationClip_gameover, 0.1f);
		break;
	}
}

// スタミナ。
void Player::PlayerStamina()
{
	m_playernowsutamina -=1;
	if (m_playernowsutamina < 0) {
		m_playernowsutamina = 0;
	}
}

// スタミナの減算描画。
void Player::PlayerhealSutamina() {
	m_playernowsutamina += 1;
	if (m_playernowsutamina > SUTAMINA_MAX) {
		m_playernowsutamina = SUTAMINA_MAX;
	}
}

// スタミナの減算処理。
void Player::Derei() {
	if (m_playermaxsutamina / 2.0f<m_playernowsutamina) {
		m_sutaminaZeroFlag = false;
	}
}

// Playerの足音コモン。
void Player::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	(void)clipName;
	if (wcscmp(eventName, L"footstep") == 0)
	{
		//プレイヤーの足音の再生。
		g_gameSoundEngine->PlaySE(GameSoundList_SE_Player_FootStep, 5.0f);
	}
}

// 描画処理。
void Player::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}

// アニメーションのセット。
void Player::SetPlayAnimation()
{
	// 待機モーション。
	GetFullPath_PlayerAnimation(enAnimationClip_idle, "playeridle", true);

	// 歩きモーション。	
	GetFullPath_PlayerAnimation(enAnimationClip_walk, "playerwalk", true);

	// 走りモーション。
	GetFullPath_PlayerAnimation(enAnimationClip_run, "playerrun", true);

	// ジャンプモーション。
	GetFullPath_PlayerAnimation(enAnimationClip_jump, "playerjump", false);

	// ステージクリア。
	GetFullPath_PlayerAnimation(enAnimationClip_stageclear, "stageclear", false);

	// ゲームオーバー。
	GetFullPath_PlayerAnimation(enAnimationClip_gameover, "gameover", true);

}