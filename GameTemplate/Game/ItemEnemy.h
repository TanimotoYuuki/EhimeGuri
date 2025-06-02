#pragma once
using namespace std;

class Player;
class Game;
class GameOver;
class Mikan;
class ItemEnemy:public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void EnemyAnimation();

	ModelRender m_modelrender;
	Vector3 m_position;
	Quaternion rotation;
	Vector3 firstposition;
	enum Enannimation {
		enAnimationclip_idle,
		enAnimationclip_walk,
		enAnimationclip_death,
		enAnimationclip_num
	};
	AnimationClip animationclip[enAnimationclip_num];
	CharacterController charactercontroller;
	SphereCollider m_sphereColl;
	Vector3 movespeed;
	int Enemystate = 0;
	int Enemyanimationstate = 0;
	Player* m_player = nullptr;
	Game* m_game  =nullptr;
	GameOver* m_gameover = nullptr;
	Mikan* m_mikan = nullptr;
	Vector3 m_enemyDeathDistanceX = Vector3::Zero;//x軸の判定。
	Vector3 m_enemyDeathDistanceY = Vector3::Zero;//y軸の判定。
	bool m_touchPlayerFlag = false;//プレイヤーに触れたか？
};

