#ifndef ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_
#define ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "OrthographicCameraController.h"

namespace tktk
{
	// �uOrthographicCameraController�v�����w���p�[�N���X
	class OrthographicCameraControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		OrthographicCameraControllerMaker() = default;
		OrthographicCameraControllerMaker(const OrthographicCameraControllerMaker& other) = default;
		OrthographicCameraControllerMaker& operator = (const OrthographicCameraControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static OrthographicCameraControllerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static OrthographicCameraControllerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<OrthographicCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		OrthographicCameraControllerMaker& initCameraHandle(size_t value);

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		OrthographicCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// �����J�������͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraWidth(float value);

		// �����J�����c�͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraHeight(float value);

		// �����߃N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraFar(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static OrthographicCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		StateTypeHierarchy	m_targetState		{  };
		size_t				m_initCameraHandle	{ 0U };
		float				m_initCameraWidth	{ 100.0f };
		float				m_initCameraHeight	{ 100.0f };
		float				m_initCameraNear	{ 1.0f };
		float				m_initCameraFar		{ 100.0f };
	};
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_