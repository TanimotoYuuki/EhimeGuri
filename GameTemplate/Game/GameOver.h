#pragma once
class Player;
class Title;
class GameOver : public IGameObject
{
public:
	GameOver() { m_spriteRender.Init("Assets/Sprite/GameOver.DDS", 1920.0f, 1080.0f); };
	~GameOver() {};

	void Update();
	void Render(RenderContext& rc);
	int NeedleCount = 0;
	ModelRender	 m_modelRender;
	SpriteRender m_spriteRender;
	Vector3	     m_position;
	GameOver   * m_gameOver;
	Player	   * m_player;
};

