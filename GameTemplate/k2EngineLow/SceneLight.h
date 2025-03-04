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

	struct Light
	{
		DirectionLight directionLight; //ディレクションライト
		Vector3 eyePos; //カメラの位置
		float pad0;
		Vector3 ambientLight; //環境光
		float pad1;
		PointLight pointLight[10]; //ポイントライト
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

