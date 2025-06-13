#pragma once
/// <summary>
/// ゲームタイマー
/// </summary>

class Fade;
class GameTimer : public IGameObject
{
public:
	~GameTimer();	//デストラクタ
	bool Start();	//開始処理
	void Update();	//更新処理
	void Render(RenderContext& rc);  //描画処理

	/// <summary>
	/// タイマーの更新処理
	/// </summary>
	void UpdateTimer();

	/// <summary>
	/// スプライトの動作
	/// </summary>
	void SpriteMove();

	/// <summary>
	/// 制限時間の設定
	/// </summary>
	/// <param name="time">制限時間</param>
	void SetTimeLimit(float time)
	{
		m_time = time; 
		m_isTimeUIDrawing = true;
	}

	/// <summary>
	/// 時間切れかどうか？
	/// </summary>
	/// <returns>trueなら時間切れ</returns>
	bool IsTimeUp() const
	{
		return m_timeUpFlag;
	}

	/// <summary>
	/// タイマーUIを描画しない
	/// </summary>
	/// <returns></returns>
	void NotTimeUIDrawing()
	{
		m_isTimeUIDrawing = false;
	}

private:
	//数字
	enum enNumber
	{
		enNumber_Zero,		//0
		enNumber_One,		//1
		enNumber_Two,		//2
		enNumber_Three,		//3
		enNumber_Four,		//4
		enNumber_Five,		//5
		enNumber_Six,		//6
		enNumber_Seven,		//7
		enNumber_Eight,		//8
		enNumber_Nine,		//9
		enNumber_Num		//数字の数
	};

	SpriteRender m_timerUI;								//タイマーUI
	SpriteRender m_hundredPlaceNumberUI[enNumber_Num];  //数字UI(百の位)
	SpriteRender m_tenPlaceNumberUI[enNumber_Num];		//数字UI(十の位)
	SpriteRender m_onePlaceNumberUI[enNumber_Num];		//数字UI(一の位)
	int m_hundredPlace = 0.0f;							//百の位
	int m_tenPlace = 0.0f;								//十の位
	int m_onePlace = 0.0f;								//一の位
	float m_time = 0.0f;								//経過時間
	float m_colorChange = 0.0f;							//色の変化									
	bool m_timeUpFlag = false;							//時間切れフラグ
	bool m_isTimeUIDrawing = false;						//タイマーUIを描画するか?
	Fade* m_fade = nullptr;								//フェード用インスタンス
};

