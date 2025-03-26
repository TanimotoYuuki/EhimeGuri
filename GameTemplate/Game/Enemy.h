#pragma once
class Player;
class Game;
class GameOver;
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
		enAnimationclip_num,
	};
	AnimationClip animationclip[enAnimationclip_num];
	CharacterController charactercontroller;
	Vector3 movespeed;
	int Enemystate = 0;
	Player* m_player;
	Game* m_game;
	GameOver* m_gameover;
};

