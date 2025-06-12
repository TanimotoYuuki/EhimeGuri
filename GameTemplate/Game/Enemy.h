#pragma once
class Player;
class Game;
class GameOver;
class Enemy :public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void EnemyAnimation();

	enum EnAnimationClip
	{
		enAnimationclip_idle,
		enAnimationclip_walk,
		enAnimationclip_death,
		enAnimationclip_num
	};
	CharacterController charactercontroller;
	SphereCollider m_sphereColl;
	Vector3 movespeed;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameOver* m_gameover = nullptr;
	Vector3 m_enemyDeathDistanceX = Vector3::Zero;//x軸の判定
	Vector3 m_enemyDeathDistanceY = Vector3::Zero;//y軸の判定
	Vector3 m_position;
	Vector3 firstposition;
	ModelRender m_modelrender;
	Quaternion rotation;

	int Enemystate = 0;
	int Enemyanimationstate = 0;

	bool m_touchPlayerFlag = false;//プレイヤーに触れたか？

private:

	AnimationClip m_animationclip[enAnimationclip_num];

	const char* ENEMY_ANIMATION = "Assets/modelData/YoshinagaAssets/SkeletonAnim/";// ファイルパス。
	const char* ANIMATION_FILE_EXTENSION = ".tka"; // 拡張子。

	/// <summary>
    /// アニメーションメソッド。
    /// </summary>
	const std::string GetFullPath_EnemyAnimation(EnAnimationClip enemyAnimation, const std::string& animationName, bool flag);
	/// <summary>
	/// アニメーションをセット。
	/// </summary>
	void SetEnemyAnimation();
};


