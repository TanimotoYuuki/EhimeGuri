#pragma once
namespace nsK2EngineLow
{
	//�f�B���N�V�������C�g
	struct DirectionLight
	{
		Vector3 direction; //���C�g�̕���
		float pad0;
		Vector3 color; //���C�g�̃J���[
		float pad1;
	};

	//�|�C���g���C�g
	struct PointLight
	{
		Vector3 position; //���C�g�̈ʒu
		float pad0;
		Vector3 color; //���C�g�̃J���[
		float range; //���C�g�̉e���͈�
	};

	struct Light
	{
		DirectionLight directionLight; //�f�B���N�V�������C�g
		Vector3 eyePos; //�J�����̈ʒu
		float pad0;
		Vector3 ambientLight; //����
		float pad1;
		PointLight pointLight[10]; //�|�C���g���C�g
	};

	class SceneLight : public Noncopyable
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		void Init();

		/// <summary>
		/// �f�B���N�V�������C�g��ݒ肷��
		/// </summary>
		/// <param name="direction">���C�g�̕���</param>
		/// <param name="color">���C�g�̐F</param>
		void SetDirectionLight(const Vector3 direction, const Vector3 color)
		{
			m_light.directionLight.direction = direction;
			m_light.directionLight.color = color;
		}

		/// <summary>
		/// ������ݒ肷��
		/// </summary>
		/// <param name="ambient">����</param>
		void SetAmbient(const Vector3 ambient)
		{
			m_light.ambientLight = ambient;
		}

		/// <summary>
		/// �|�C���g���C�g��ݒ肷��
		/// </summary>
		/// <param name="num">���C�g�ԍ�</param>
		/// <param name="position">���C�g�̈ʒu</param>
		/// <param name="color">���C�g�̃J���[</param>
		/// <param name="range">���C�g�̉e���͈�</param>
		void SetPointLight(int num, Vector3 position, Vector3 color, float range)
		{
			m_light.pointLight[num].position = position;
			m_light.pointLight[num].color = color;
			m_light.pointLight[num].range = range;
		}

		/// <summary>
		/// �V�[�����C�g���擾
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

