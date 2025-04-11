#pragma once
class Player;
class Game;
class GameOver;
class Needle;
class MovingFloor;
class FallingBlock;
class ScaffoldBlock;
class GameCamera;
class Enemy:public IGameObject
{
public:
	//Enemy();
	//~Enemy();
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
	Player* m_player;
	Game* m_game;
	GameOver* m_gameover;
	Needle* m_needle;
	MovingFloor* m_movingfloor;
	FallingBlock* m_fallingblock;
	ScaffoldBlock* m_scaffolblock;
	GameCamera* m_gamecamera;
	Vector3 m_enemyDeathDistanceX = Vector3::Zero;//xŽ²‚Ì”»’è
	Vector3 m_enemyDeathDistanceY = Vector3::Zero;//yŽ²‚Ì”»’è
};

