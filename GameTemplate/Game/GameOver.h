#pragma once
class Player;
class Fade;
class Game;
class GameOver : public IGameObject
{
	/// <summary>
	/// ゲームオーバー。
    /// </summary>

public:
	~GameOver();  //デストラクタ。
	bool Start();  //開始処理。
	void Update();  //更新処理。
	void Render(RenderContext& rc);  //描画処理。

private:
	/// <summary>
	/// スプライトの初期化。
	/// </summary>
	void InitSprite();

	/// <summary>
	/// プレイヤー側の操作。
	/// </summary>
	void Action();

	/// <summary>
	/// スプライトの動作
	/// </summary>
	void SpriteMove();

	/// <summary>
	/// ゲームオーバースプライト用のイージング(位置)を設定。
	/// </summary>
	void SetGameOverSpriteEasingPosition();
	
	/// <summary>
	/// ゲームオーバースプライト用のイージング(位置)の更新処理。
	/// </summary>
	void UpdateGameOverSpriteEasingPosition();

	/// <summary>
	/// ゲームオーバースプライト用のイージング(回転)を設定。
	/// </summary>
	/// <param name="angle">角度</param>
	void SetGameOverSpriteEasingRotation(float angle);

	/// <summary>
	/// ゲームオーバースプライト用のイージング(回転)の更新処理。
	/// </summary>
	void UpdateGameOverSpriteEasingRotation();

	/// <summary>
	/// ゲームオーバースプライト用の弾力性の更新処理。
	/// </summary>
	void UpdateGameOverSpriteElasticity();

	/// <summary>
	/// 反発係数を設定する。
	/// </summary>
	/// <param name="beforeSpeed">衝突直前の速度</param>
	/// <param name="afterSpeed">衝突直後の速度</param>
	void SetCoefficientOfRestitution(float beforeSpeed, float afterSpeed)
	{
		m_coefficientOfRestitution = afterSpeed / beforeSpeed;
	}

	/// <summary>
	/// ゲームオーバー。
	/// </summary>
	void SetGameOver();

	/// <summary>
	/// ゲームオーバー時の選択UI。
	/// </summary>
	void SetChoiceUI();

	/// <summary>
	/// タイトルへ戻る処理。
	/// </summary>
	void SetReturnTitle();

	/// <summary>
	/// Lスティック。
	/// </summary>
	void SetLStick();

	/// <summary>
	/// 十字キー。
	/// </summary>
	void SetDpadUI();

	/// <summary>
	/// AボタンUI。
	/// </summary>
	void SetAbuttonUI();

	/// <summary>
	/// 選択UI。
	/// </summary>
	void SetSelectUI();

	/// <summary>
	/// 決定UI。
	/// </summary>
	void SetDecisionUI();

	//選択。
	enum EnSelect
	{
		enSelect_Continue,			//コンティニュー。
		enSelect_ReturnTitle,		//タイトルへ戻る。
		enSelect_Num				//選択数。
	};

	//ゲームオーバー演出
	enum EnGameOverDirection
	{
		enGameOverDirection_GameOver,	//ゲームオーバー。
		enGameOverDirection_Select,		//選択。
		enGameOverDirection_Num			//ゲームオーバー演出数。
	};

	int	NeedleCount = 0;												//針用のカウント。
	SpriteRender m_gameOverUI;											//ゲームオーバーUI。
	SpriteRender m_gameOverSelectUI[enSelect_Num];						//ゲームオーバー時の選択UI。
	SpriteRender m_lStickUI;											//LスティックUI。
	SpriteRender m_dPadUI;												//十字キーUI。
	SpriteRender m_aButtonUI;											//AボタンUI。
	SpriteRender m_selectUI;											//選択UI。
	SpriteRender m_decisionUI;											//決定UI。
	Vector3 m_gameOverUIPosition = Vector3(15.0f, 500.0f, 0.0f);		//ゲームオーバーUI用の位置。
	Vector3	m_gameOverUIFarstHeight = Vector3::Zero;					//ゲームオーバーUI用の最初の高さ。
	Quaternion m_gameOverUIRotation;									//ゲームオーバーUI用の回転。
	Vector3 m_beforeEasingPosition = Vector3::Zero;						//イージング前の位置。
	Vector3	m_afterEasingPosition = Vector3::Zero;						//イージング後の位置。
	Quaternion m_beforeEasingRotation = Quaternion::Identity;			//イージング前の回転。
	Quaternion m_afterEasingRotation = Quaternion::Identity;			//イージング後の回転。
	Vector3 m_gameOverSelectUIScale[enSelect_Num];						//ゲームオーバー時の選択UI用の大きさ。
	Vector4 m_gameOverSelectUIColor[enSelect_Num];						//ゲームオーバー時の選択UI用のカラー。
	Vector3 m_gameOverSelectUIScaleChange;								//ゲームオーバー時の選択UIの大きさ変化用変数。
	int m_gameOverDirectionState = enGameOverDirection_GameOver;		//ゲームオーバー演出ステート。
	int m_gameOverSelect = enSelect_Continue;							//ゲームオーバー時の選択。
	int m_exponentiation = 2;											//累乗。
	int m_gameOverUIHitCount = 1;										//ゲームオーバーUIが何回跳ねたか。
	float m_easingTime = 0.0f;											//割合。
	float m_coefficientOfRestitution = 0.0f;							//反発係数。
	float m_angle = -10.0f;												//角度。
	float m_gameOverSelectUIAlphaColor = 0.0f;							//ゲームオーバー時の選択UI透明度。
	bool m_easingFinishFlag = false;									//イージングが終わったか?
	bool m_pressButtonFlag = false;										//ボタンを押したか?
	bool m_pressButtonActionFlag = false;								//ボタンを押したときの動作をしたか?
	bool m_gameOverUIFallFlag = false;									//ゲームオーバーUIが落下するか?
	bool m_gameOverDirectionFlag = false;								//ゲームオーバー演出フラグ。
	bool m_transitionFlag = false;										//遷移フラグ。
	bool m_gameOverSelectUIScaleDownFlag = false;						//ゲームオーバー時の選択UIの大きさを小さくするか？
	Player* m_player = nullptr;											//プレイヤー用のインスタンス。
	Fade* m_fade = nullptr;												//フェード用のインスタンス。
	Game* m_game = nullptr;												//ゲーム用のインスタンス。
};

