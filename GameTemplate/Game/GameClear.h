#pragma once
class Fade;
class GameClear : public IGameObject
{
public:
	~GameClear();

	bool Start();
	void Update();

	void Render(RenderContext& rc);

	/// <summary>
	/// 収集したアイテムの数を設定する
	/// </summary>
	/// <param name="gatheringItemNum">収集したアイテムの数</param>
	void SetGatheringItemNum(int gatheringItemNum)
	{
		m_gatheringItemNum = gatheringItemNum;
	}

	/// <summary>
	/// アイテムの総数を設定する
	/// </summary>
	/// <param name="totalItemNum">アイテムの総数</param>
	void SetTotalItemNum(int totalItemNum)
	{
		m_totalItemNum = totalItemNum;
	}

	/// <summary>
	/// 収集率の計算
	/// </summary>
	/// <param name="num">収集したアイテムの数</param>
	/// <param name="totalNum">アイテムの総数</param>
	void GatheringRate(int gatheringItemNum, int totalItemNum);

private:
	/// <summary>
	/// カメラの初期化
	/// </summary>
	void InitCamera();

	/// <summary>
	/// スプライトの初期化
	/// </summary>
	void InitSprite();

	/// <summary>
	/// モデルの初期化
	/// </summary>
	void InitModel();

	/// <summary>
	/// ランクを設定する
	/// </summary>
	void SetRank()
	{
		//収集率が100%なら
		if (m_gatheringRate >= 100)
		{
			//Sランク
			m_rankSpriteFilePath = "Assets/result/rank/s.dds";
			m_rankSpriteColor = { 0.7f,0.0f,0.7f,0.0f };	//紫色
			m_rankState = enRank_S;
		}
		//収集率が80%以上なら
		else if (m_gatheringRate >= 80)
		{
			//Aランク
			m_rankSpriteFilePath = "Assets/result/rank/a.dds";
			m_rankSpriteColor = { 1.0f,1.0f,0.0f,0.0f };	//黄色
			m_rankState = enRank_A;
		}
		//収集率が60%以上なら
		else if (m_gatheringRate >= 60)
		{
			//Bランク
			m_rankSpriteFilePath = "Assets/result/rank/b.dds";
			m_rankSpriteColor = { 1.0f,0.0f,0.0f,0.0f };	//赤色
			m_rankState = enRank_B;
		}
		//収集率が40%以上なら
		else if (m_gatheringRate >= 40)
		{
			//Cランク
			m_rankSpriteFilePath = "Assets/result/rank/c.dds";
			m_rankSpriteColor = { 0.0f,0.7f,0.0f,0.0f };	//緑色
			m_rankState = enRank_C;
		}
		//収集率が20%以上なら
		else if (m_gatheringRate >= 20)
		{
			//Dランク
			m_rankSpriteFilePath = "Assets/result/rank/d.dds";
			m_rankSpriteColor = { 0.5f,0.9f,0.9f,0.0f };	//水色
			m_rankState = enRank_D;
		}
		//収集率が20%未満なら
		else
		{
			//Eランク
			m_rankSpriteFilePath = "Assets/result/rank/e.dds";
			m_rankSpriteColor = { 0.5f,0.5f,0.5f,0.0f };	//灰色
			m_rankState = enRank_E;
		}
	}

	/// <summary>
	/// 順位を設定する
	/// </summary>
	void SetRanking()
	{
		//順位
		int rank = m_totalItemNum - m_gatheringItemNum;

		//順位を計算結果が0以下の場合
		if (rank <= 0)
		{
			//1位を描画する
			m_hundredPlace[enNumberDraw_Ranking] = enNumver_Zero;
			m_tenPlace[enNumberDraw_Ranking] = enNumver_Zero;
			m_onePlace[enNumberDraw_Ranking] = enNumver_One;
			return;
		}

		//UIを表示するための計算
		//百の位
		m_hundredPlace[enNumberDraw_Ranking] = rank / 100;

		//十の位
		m_tenPlace[enNumberDraw_Ranking] = rank / 10;

		//一の位
		m_onePlace[enNumberDraw_Ranking] = rank % 10;
	}

	/// <summary>
	/// 数字スプライトのファイルパスの取得
	/// </summary>
	/// <param name="num">数字</param>
	void GetNumberSpriteFilePaht(int num)
	{
		//数字
		switch (num)
		{
		case enNumver_Zero:				//0
			m_numberSpriteFilePath = "Assets/result/number/0.dds";
			break;
		case enNumver_One:				//1
			m_numberSpriteFilePath = "Assets/result/number/1.dds";
			break;
		case enNumver_Two:				//2
			m_numberSpriteFilePath = "Assets/result/number/2.dds";
			break;
		case enNumver_Three:			//3
			m_numberSpriteFilePath = "Assets/result/number/3.dds";
			break;
		case enNumver_Four:				//4
			m_numberSpriteFilePath = "Assets/result/number/4.dds";
			break;
		case enNumver_Five:				//5
			m_numberSpriteFilePath = "Assets/result/number/5.dds";
			break;
		case enNumver_Six:				//6
			m_numberSpriteFilePath = "Assets/result/number/6.dds";
			break;
		case enNumver_Seven:			//7
			m_numberSpriteFilePath = "Assets/result/number/7.dds";
			break;
		case enNumver_Eight:			//8
			m_numberSpriteFilePath = "Assets/result/number/8.dds";
			break;
		case enNumver_Nine:				//9
			m_numberSpriteFilePath = "Assets/result/number/9.dds";
			break;
		default:						//10～
			m_numberSpriteFilePath = "Assets/result/number/0.dds";
			break;
		}
	}

	/// <summary>
	/// スプライトの動作
	/// </summary>
	void SpriteMove();

	/// <summary>
	/// プレイヤー側の操作
	/// </summary>
	void Action();
	
	/// <summary>
	/// プレイヤーモデルのアニメーション管理
	/// </summary>
	void PlayerModelAnimationManage();

	/// <summary>
	/// プレイヤーモデルのアニメーション再生
	/// </summary>
	void PlayerModelPlayAnimation();

	//数字UI描画
	enum enNumberDraw
	{
		enNumberDraw_GatheringRate,		//収集率
		enNumberDraw_Ranking,			//順位
		enNumberDraw_Num				//数字UI描画数
	};

	//数字
	enum enNumber
	{
		enNumver_Zero,		//0
		enNumver_One,		//1
		enNumver_Two,		//2
		enNumver_Three,		//3
		enNumver_Four,		//4
		enNumver_Five,		//5
		enNumver_Six,		//6
		enNumver_Seven,		//7
		enNumver_Eight,		//8
		enNumver_Nine,		//9
		enNumver_TenOver,   //10～
		enNumver_Num		//数字数
	};

	//〇の位
	enum enNumberPlace
	{
		enNumberPlace_Hundred,		//百の位
		enNumberPlace_Ten,			//十の位
		enNumberPlace_One,			//一の位
		enNumberPlace_Num			//〇の位数
	};

	//ランク
	enum enRank
	{
		enRank_S,			//Sランク
		enRank_A,			//Aランク
		enRank_B,			//Bランク
		enRank_C,			//Cランク
		enRank_D,			//Dランク
		enRank_E,			//Eランク
		enRank_Num			//ランク数
	};

	//アニメーションクリップ
	enum EnAnimationClip {
		enAnimationClip_Idle,		//待機
		enAnimationClip_Defeat,		//悔しい
		enAnimationClip_FistPump,	//ガッツ
		enAnimationClip_Victory,	//嬉しい
		enAnimationClip_Num			//アニメーション数
	};

	//アニメーションステート
	enum EnAnimationState
	{
		enAnimationState_Idle,		//待機
		enAnimationState_Defeat,	//悔しい
		enAnimationState_FistPump,	//ガッツ
		enAnimationState_Victory,	//嬉しい
		enAnimationState_Num		//アニメーションステート数
	};

	//ゲームクリア演出
	enum EnGameClearDirection
	{
		enGameClearDirection_GatheringRate,		//収集率
		enGameClearDirection_Ranking,			//順位
		enGameClearDirection_Rank,				//ランク
		enGameClearDirection_Num				//ゲームクリア演出数
	};

	SpriteRender		m_result;															//リザルト画面
	SpriteRender		m_gatheringRateNumberHundredPlaceUI[enNumver_Num];					//収集率用数字UI(百の位)
	SpriteRender		m_gatheringRateNumberTenPlaceUI[enNumver_Num];						//収集率用数字UI(十の位)
	SpriteRender		m_gatheringRateNumberOnePlaceUI[enNumver_Num];						//収集率用数字UI(一の位)	
	SpriteRender		m_rankingNumberHundredPlaceUI[enNumver_Num];						//順位用数字UI(百の位)
	SpriteRender		m_rankingNumberTenPlaceUI[enNumver_Num];							//順位用数字UI(十の位)
	SpriteRender		m_rankingNumberOnePlaceUI[enNumver_Num];							//順位用数字UI(一の位)
	SpriteRender        m_rankUI[enRank_Num];												//ランクUI
	SpriteRender        m_percentUI;														//パーセントUI
	SpriteRender        m_placeUI;															//位UI
	SpriteRender		m_aButtonUI;														//AボタンUI
	SpriteRender        m_returnTitleUI;													//タイトルへ戻るUI
	BackGroundRender    m_gameBackground;													//ゲーム背景
	AnimationClip		m_animationClip[enAnimationClip_Num];								//アニメーションクリップ
	ModelRender			m_playerModel;														//プレイヤーモデル
	Vector3				m_playerModelPosition = Vector3(-100.0f, 0.0f, -35.0f);				//プレイヤーモデルの位置
	Quaternion          m_playerModelRotation = Quaternion::Identity;						//プレイヤーモデルの回転
	Vector3				m_playerModelScale = Vector3(0.25f, 0.25f, 0.25f);					//プレイヤーモデルの大きさ
	Vector4				m_rankSpriteColor = Vector4{ 0.0f,0.0f,0.0f,1.0f };					//ランクスプライト用カラー
	int                 m_hundredPlace[enNumberDraw_Num] = { 0,0 };							//百の位
	int                 m_tenPlace[enNumberDraw_Num] = { 0,0 };								//十の位
	int                 m_onePlace[enNumberDraw_Num] = { 0,0 };								//一の位
	int                 m_gatheringItemNum = 0;												//収集したアイテムの数
	int                 m_totalItemNum = 1;													//アイテムの総数
	int					m_gatheringRate = 0;												//収集率
	int					m_animationState = enAnimationState_Idle;							//アニメーションステート
	int                 m_rankState = enRank_Num;											//ランクステート
	int                 m_gameClearDirectionState = enGameClearDirection_GatheringRate;		//ゲームクリア演出ステート
	float               m_gatheringRateUIAlphaColor = -0.5f;								//収集率UI用透明度
	float				m_rankingUIAlphaColor = -0.5f;										//順位UI用透明度
	float				m_rankUIAlphaColor = -0.5f;											//ランクUI用透明度
	bool				m_gameClearDirectionFlag = false;									//ゲームクリア演出フラグ
	bool				m_titleScreenTransitionFlag = false;								//タイトル画面遷移フラグ
	const char*			m_numberSpriteFilePath = nullptr;									//数字スプライト用ファイルパス
	const char*			m_rankSpriteFilePath = nullptr;										//ランクスプライト用ファイルパス
	Fade*				m_fade = nullptr;													//フェード用インスタンス
};

