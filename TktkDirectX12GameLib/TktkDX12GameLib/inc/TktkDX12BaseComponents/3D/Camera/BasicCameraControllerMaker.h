#ifndef BASIC_CAMERA_CONTROLLER_MAKER_H_
#define BASIC_CAMERA_CONTROLLER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "BasicCameraController.h"

namespace tktk
{
	// �uBasicCameraController�v�����w���p�[�N���X
	class BasicCameraControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BasicCameraControllerMaker() = default;
		BasicCameraControllerMaker(const BasicCameraControllerMaker& other) = default;
		BasicCameraControllerMaker& operator = (const BasicCameraControllerMaker& other) = default;
	
	public:

		// �쐬�J�n
		static BasicCameraControllerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BasicCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BasicCameraControllerMaker& initCameraHandle(size_t value);

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BasicCameraControllerMaker& initCameraId(ResourceIdCarrier value);

		// �����J�����ˊp��ݒ肷��
		BasicCameraControllerMaker& initCameraFov(float value);

		// �����J�����A�X�y�N�g���ݒ肷��
		BasicCameraControllerMaker& initCameraAspect(float value);

		// �����߃N���b�v�l��ݒ肷��
		BasicCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		BasicCameraControllerMaker& initCameraFar(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BasicCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		size_t				m_initCameraHandle	{ 0U };
		float				m_initCameraFov		{ 45.0f };
		float				m_initCameraAspect	{};	// �f�t�H���g�̓Q�[���X�N���[���̔䗦
		float				m_initCameraNear	{ 1.0f };
		float				m_initCameraFar		{ 100.0f };
	};
}
#endif // !BASIC_CAMERA_CONTROLLER_MAKER_H_