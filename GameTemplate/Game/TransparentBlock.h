#pragma once
/// <summary>
/// 透明ブロック
/// </summary>
using namespace std;

class Player;
class Config;
class TransparentBlock : public IGameObject
{
public:
	bool Start();  //開始処理。
	void Update(); //更新処理。
	void Render(RenderContext& rc);  //描画処理。

	/// <summary>
	/// ブロックの表面のコリジョン衝突判定
	/// </summary>
	void BlockSurfaceCollisionHitDetection();

	Vector3 m_position;		 //座標。
	Vector3 m_firstposition; //初期位置。

public:
	Config* m_config = nullptr;
	ModelRender m_transparentBlockModel;						 //モデル。
	Quaternion m_rotation = Quaternion::Identity;				 //回転。
	Vector3 m_scale = Vector3::One;								 //大きさ。
	Vector3 m_blockTouchDistanceX = Vector3::Zero;				 //透明ブロック叩く用距離(X軸)。
	bool m_blockTouchFlag = false;								 //ブロック叩いたか？
	bool m_collisionCreatFlag = false;							 //当たり判定が作られたか？
	bool m_blockSurfaceCollisionHitFlag = false;				 //ブロックの表面のコリジョンを衝突したか?
	PhysicsStaticObject m_physicsStaticObject;					 //静的物理オブジェクト。
	CollisionObject* m_blockSurfaceCollision = nullptr;			 //コリジョンオブジェクト(透明ブロックの表面)用のインスタンス。
	CollisionObject* m_blockBottomCollision = nullptr;			 //コリジョンオブジェクト(透明ブロックの底面)用のインスタンス。
	Player* m_player = nullptr;									 //プレイヤー用インスタンス。
};

