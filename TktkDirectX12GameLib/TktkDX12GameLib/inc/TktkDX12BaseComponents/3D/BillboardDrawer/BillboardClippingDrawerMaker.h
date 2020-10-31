#ifndef BILLBOARD_CLIPPING_DRAWER_MAKER_H_
#define BILLBOARD_CLIPPING_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "BillboardClippingDrawer.h"

namespace tktk
{
	// �uBillboardClippingDrawer�v�����w���p�[�N���X
	class BillboardClippingDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BillboardClippingDrawerMaker() = default;
		BillboardClippingDrawerMaker(const BillboardClippingDrawerMaker& other) = default;
		BillboardClippingDrawerMaker& operator = (const BillboardClippingDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BillboardClippingDrawerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class StateIdType>
		static BillboardClippingDrawerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardClippingDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BillboardClippingDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BillboardClippingDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardClippingDrawerMaker& billboardMaterialHandle(unsigned int value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardClippingDrawerMaker& cameraHandle(unsigned int value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		template<class IdType, is_idType<IdType> = nullptr>
		BillboardClippingDrawerMaker& cameraId(IdType value) { return cameraIdImpl(static_cast<int>(value)); }

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		BillboardClippingDrawerMaker& billboardMaterialId(IdType value) { return billboardMaterialIdImpl(static_cast<int>(value)); }

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		BillboardClippingDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardClippingDrawerMaker& blendRate(const tktkMath::Color& value);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		BillboardClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		BillboardClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		BillboardClippingDrawerMaker& billboardMaterialIdImpl(int value);
		BillboardClippingDrawerMaker& cameraIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardClippingDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user						{  };
		std::vector<int>		m_targetState				{  };
		float					m_drawPriority				{ 0.0f };
		unsigned int			m_useRtvDescriptorHeapHandle{  };
		unsigned int			m_cameraHandle				{ 0U };
		unsigned int			m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2		m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color			m_blendRate					{ tktkMath::Color_v::white };
		BillboardClippingParam	m_clippingParam				{  };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		BillboardClippingDrawerMaker& billboardMaterialId(IdType value) { static_assert(false, "BillboardMaterialId Fraud Type"); }
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �X�e�[�g���w�肵�A�쐬���J�n����
	// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class StateIdType>
	inline BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !BILLBOARD_CLIPPING_DRAWER_MAKER_H_