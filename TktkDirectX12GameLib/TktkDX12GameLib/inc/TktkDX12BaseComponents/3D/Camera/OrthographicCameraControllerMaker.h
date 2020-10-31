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
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static OrthographicCameraControllerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<OrthographicCameraController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉���J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		OrthographicCameraControllerMaker& initCameraHandle(unsigned int value);

		// �g�p���鏉���J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value) { return initCameraIdImpl(static_cast<int>(value)); }

		// �����J�������͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraWidth(float value);

		// �����J�����c�͈͂�ݒ肷��
		OrthographicCameraControllerMaker& initCameraHeight(float value);

		// �����߃N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraNear(float value);

		// �������N���b�v�l��ݒ肷��
		OrthographicCameraControllerMaker& initCameraFar(float value);

	private: /* �e��id�w��n�̊֐��̎��� */

		OrthographicCameraControllerMaker& initCameraIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static OrthographicCameraControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		unsigned int		m_initCameraHandle	{ 0U };
		float				m_initCameraWidth	{ 100.0f };
		float				m_initCameraHeight	{ 100.0f };
		float				m_initCameraNear	{ 1.0f };
		float				m_initCameraFar		{ 100.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		OrthographicCameraControllerMaker& initCameraId(IdType value) { static_assert(false, "CameraId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// �쐬�J�n�������s��
		auto& result = makeStart(user);

		// �������q���X�g��z��ɕϊ�
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// �Ώۂ̃X�e�[�g�̊K�w�����̃��������m��
		result.m_targetState.reserve(targetStateArray.size());

		// �Ώۂ̃X�e�[�g�̊K�w��ݒ肷��
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// ���g�̎Q�Ƃ�Ԃ�
		return result;
	}
}
#endif // !ORTHOGRAPHIC_CAMERA_CONTROLLER_MAKER_H_