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
	/// プレイヤー側の操作
	/// </summary>
	void Action();

	/// <summary>
	/// スプライトの動作
	/// </summary>
	void SpriteMove();

	//選択
	enum EnSelect
	{
		enSelect_Continue,			//コンティニュー
		enSelect_ReturnTitle,		//タイトルへ戻る
		enSelect_Num				//選択数
	};

	int					NeedleCount = 0;											//針用のカウント
	SpriteRender		m_gameOverUI;												//ゲームオーバーUI
	SpriteRender		m_selectUI[enSelect_Num];									//選択UI
	SpriteRender		m_aButtonUI;												//AボタンUI
	SpriteRender		m_decisionUI;												//決定UI
	Vector3				m_gameOverPosition = Vector3(0.0f, 150.0f, 0.0f);			//ゲームオーバー用の位置
	Vector3				m_gameOverRotation;											//ゲームオーバー用の回転
	Vector4				m_selectUIColor[enSelect_Num];								//選択UI用のカラー
	int					m_select = enSelect_Continue;								//選択
	bool				m_pressButtonFlag = false;									//ボタンを押したか?
	bool				m_pressButtonActionFlag = false;							//ボタンを押したときの動作をしたか?
	bool				m_gameOverDirectionFlag = false;							//ゲームオーバー演出フラグ
	bool                m_transitionFlag = false;									//遷移フラグ
	Player*				m_player;													//プレイヤー用のインスタンス
	Fade*				m_fade;														//フェード用のインスタンス
};

