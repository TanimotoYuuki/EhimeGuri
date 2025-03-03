#pragma once
namespace nsK2EngineLow
{
	struct DirectionLight
	{
		Vector3 direction; //ライトの方向
		float pad0;
		Vector4 color; //ライトのカラー
	};

	struct Light
	{
		DirectionLight directionLight; //ディレクションライト
		Vector3 eyePos; //カメラの位置
		float pad1;
		Vector3 ambientLight; //環境光
	};
	class SceneLight : public Noncopyable
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// シーンライトを取得
		/// </summary>
		/// <returns></returns>
		Light& GetLight()
		{
			return m_light;
		}

		/// <summary>
		/// ディレクションライトを設定する
		/// </summary>
		/// <param name="lightNo">ライト番号</param>
		/// <param name="direction">ライトの方向</param>
		/// <param name="color">ライトの色</param>
		void SetDirectionLight(const int lightNo, const Vector3 direction, const Vector4 color)
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
	private:
		Light m_light;
	};
}

