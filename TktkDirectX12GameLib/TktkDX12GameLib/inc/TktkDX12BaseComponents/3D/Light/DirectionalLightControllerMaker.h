#ifndef DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_
#define DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "DirectionalLightController.h"

namespace tktk
{
	class DirectionalLightControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		DirectionalLightControllerMaker() = default;
		DirectionalLightControllerMaker(const DirectionalLightControllerMaker& other) = default;
		DirectionalLightControllerMaker& operator = (const DirectionalLightControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static DirectionalLightControllerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static DirectionalLightControllerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<DirectionalLightController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		DirectionalLightControllerMaker& initLightHandle(unsigned int value);

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { return initLightIdImpl(static_cast<int>(value)); }

		// ����������ݒ肷��
		DirectionalLightControllerMaker& initAmbient(const tktkMath::Color & value);

		// �����g�U���ˌ���ݒ肷��
		DirectionalLightControllerMaker& initDiffuse(const tktkMath::Color & value);

		// �������ʔ��ˌ���ݒ肷��
		DirectionalLightControllerMaker& initSpeqular(const tktkMath::Color & value);

	private: /* �e��id�w��n�̊֐��̎��� */

		DirectionalLightControllerMaker& initLightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static DirectionalLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		unsigned int		m_initLightHandle	{ 0U };
		tktkMath::Color		m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 1.0f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		DirectionalLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline DirectionalLightControllerMaker& DirectionalLightControllerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !DIRECTIONAL_LIGHT_CONTROLLER_MAKER_H_