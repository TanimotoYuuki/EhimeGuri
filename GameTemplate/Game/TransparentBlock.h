#pragma once
/// <summary>
/// 透明ブロック
/// </summary>
class Player;
class TransparentBlock : public IGameObject
{
public:
	bool Start();  //開始処理
	void Update();  //更新処理
	void Render(RenderContext& rc);  //描画処理

	Vector3 m_position;		 //座標
	Vector3 m_firstposition; //初期位置

public:
	ModelRender m_transparentBlockModel;			 //モデル
	Quaternion m_rotation = Quaternion::Identity;	 //回転
	Vector3 m_scale = Vector3::One;					 //大きさ
	Vector3 m_blockTouchDistanceX = Vector3::Zero;	 //透明ブロック叩く用距離(X軸)
	Vector3 m_blockTouchDistanceY = Vector3::Zero;	 //透明ブロック叩く用距離(Y軸)
	Vector3 m_blockTouchDistance = Vector3::Zero;	 //ブロック叩く用距離
	bool m_blockTouchFlag = false;					 //ブロック叩いたか？
	bool m_collisionCreatFlag = false;				 //当たり判定が作られたか？
	PhysicsStaticObject m_physicsStaticObject;		 //静的物理オブジェクト
	Player* m_player = nullptr;						 //プレイヤー用インスタンス

};

