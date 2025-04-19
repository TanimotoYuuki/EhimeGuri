#pragma once
class Player;
class Fade;
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

	void Update();
	void Render(RenderContext& rc);

private:
	/// <summary>
	/// スプライトの初期化
	/// </summary>
	void InitSprite();

	/// <summary>
	/// スプライトの動作
	/// </summary>
	void SpriteMove();

	/// <summary>
	/// プレイヤー側の操作
	/// </summary>
	void Action();

	int					NeedleCount = 0;											//針用のカウント
	SpriteRender		m_gameOver;													//ゲームオーバーUI
	SpriteRender		m_continue;													//コンティニューUI
	SpriteRender		m_returnTitle;												//タイトルへ戻るUI
	SpriteRender		m_aButton;													//AボタンUI
	SpriteRender		m_decision;													//決定UI
	Vector3				m_gameOverPosition = Vector3(0.0f, 150.0f, 0.0f);			//ゲームオーバー用の位置
	Vector3				m_gameOverRotation;											//ゲームオーバー用の回転
	bool				m_gameOverDirectionFlag = false;							//ゲームオーバー演出フラグ
	Player*				m_player;													//プレイヤー用のインスタンス
	Fade*				m_fade;														//フェード用のインスタンス
};

