#pragma once
namespace nsK2EngineLow
{
	//ディレクションライト
	struct DirectionLight
	{
		Vector3 direction; //ライトの方向
		float pad0;
		Vector3 color; //ライトのカラー
		float pad1;
	};

	//ポイントライト
	struct PointLight
	{
		Vector3 position; //ライトの位置
		float pad0;
		Vector3 color; //ライトのカラー
		float range; //ライトの影響範囲
	};

	//スポットライト
	struct SpotLight
	{
		Vector3 position; //ライトの位置
		float pad0;
		Vector3 color; //ライトのカラー
		float range; //ライトの影響範囲
		Vector3 direction; //ライトの放射方向
		float angle; //ライトの放射角度
	};

	//半球ライト
	struct HemLight
	{
		Vector3 groundColor; //地面色
		float pad0;
		Vector3 skyColor; //天球色
		float pad1;
		Vector3 groundNormal; //地面の法線
	};

	//ライト
	struct Light
	{
		DirectionLight directionLight; //ディレクションライト
		Vector3 eyePos; //カメラの位置
		float pad0;
		Vector3 ambientLight; //環境光
		float pad1;
		PointLight pointLight[10]; //ポイントライト
		SpotLight spotLight[10]; //スポットライト
		HemLight hemLight; //半球ライト
	};

	class SceneLight : public Noncopyable
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// ディレクションライトを設定する
		/// </summary>
		/// <param name="direction">ライトの方向</param>
		/// <param name="color">ライトの色</param>
		void SetDirectionLight(const Vector3 direction, const Vector3 color)
		{
			m_light.directionLight.direction = direction;
			m_light.directionLight.direction.Normalize();
			m_light.directionLight.color = color;
		}

		/// <summary>
		/// 環境光を設定する
		/// </summary>
		/// <param name="ambient">環境光</param>
		void SetAmbient(const Vector3 ambient)
		{
			m_light.ambientLight = ambient;
		}

		/// <summary>
		/// ポイントライトを設定する
		/// </summary>
		/// <param name="num">ライト番号</param>
		/// <param name="position">ライトの位置</param>
		/// <param name="color">ライトのカラー</param>
		/// <param name="range">ライトの影響範囲</param>
		void SetPointLight(int num, Vector3 position, Vector3 color, float range)
		{
			m_light.pointLight[num].position = position;
			m_light.pointLight[num].color = color;
			m_light.pointLight[num].range = range;
		}

		/// <summary>
		/// スポットライトを設定する
		/// </summary>
		/// <param name="num">ライト番号</param>
		/// <param name="position">ライトの位置</param>
		/// <param name="color">ライトのカラー</param>
		/// <param name="range">ライトの影響範囲</param>
		/// <param name="direction">ライトの放射方向</param>
		/// <param name="angle">ライトの放射角度</param>
		void SetSpotLight(int num, Vector3 position, Vector3 color, float range, Vector3 direction, float angle)
		{
			m_light.spotLight[num].position = position;
			m_light.spotLight[num].color = color;
			m_light.spotLight[num].range = range;
			m_light.spotLight[num].direction = direction;
			m_light.spotLight[num].direction.Normalize();
			m_light.spotLight[num].angle = angle;
		}

		/// <summary>
		/// 半球ライトを設定する
		/// </summary>
		/// <param name="groundColor">地面色</param>
		/// <param name="skyColor">天球色</param>
		/// <param name="groundNormal">地面の法線</param>
		void SetHemLight(Vector3 groundColor, Vector3 skyColor, Vector3 groundNormal)
		{
			m_light.hemLight.groundColor = groundColor;
			m_light.hemLight.skyColor = skyColor;
			m_light.hemLight.groundNormal = groundNormal;
		}

		/// <summary>
		/// シーンライトを取得
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_light;
		}
	private:
		Light m_light;
	};
}

