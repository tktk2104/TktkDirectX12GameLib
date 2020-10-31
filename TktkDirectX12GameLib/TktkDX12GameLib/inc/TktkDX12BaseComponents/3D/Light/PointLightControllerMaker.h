#ifndef POINT_LIGHT_CONTROLLER_MAKER_H_
#define POINT_LIGHT_CONTROLLER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PointLightController.h"

namespace tktk
{
	// �uPointLightController�v�����w���p�[�N���X
	class PointLightControllerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		PointLightControllerMaker() = default;
		PointLightControllerMaker(const PointLightControllerMaker& other) = default;
		PointLightControllerMaker& operator = (const PointLightControllerMaker& other) = default;

	public:

		// �쐬�J�n
		static PointLightControllerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static PointLightControllerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<PointLightController> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p���鏉�����C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		PointLightControllerMaker& initLightHandle(unsigned int value);

		// �g�p���鏉�����C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		template<class IdType, is_idType<IdType> = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { return initLightIdImpl(static_cast<int>(value)); }

		// ����������ݒ肷��
		PointLightControllerMaker& initAmbient(const tktkMath::Color& value);

		// �����g�U���ˌ���ݒ肷��
		PointLightControllerMaker& initDiffuse(const tktkMath::Color& value);

		// �������ʔ��ˌ���ݒ肷��
		PointLightControllerMaker& initSpeqular(const tktkMath::Color& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		PointLightControllerMaker& initLightIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static PointLightControllerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user				{  };
		std::vector<int>	m_targetState		{  };
		unsigned int		m_initLightHandle	{ 0U };
		tktkMath::Color		m_initAmbient		{ 0.1f, 1.0f };
		tktkMath::Color		m_initDiffuse		{ 1.0f, 1.0f };
		tktkMath::Color		m_initSpeqular		{ 1.0f, 1.0f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PointLightControllerMaker& initLightId(IdType value) { static_assert(false, "LightId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline PointLightControllerMaker& PointLightControllerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !POINT_LIGHT_CONTROLLER_MAKER_H_