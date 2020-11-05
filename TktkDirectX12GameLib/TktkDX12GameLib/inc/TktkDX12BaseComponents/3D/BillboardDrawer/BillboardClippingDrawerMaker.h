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
		static BillboardClippingDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardClippingDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		BillboardClippingDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BillboardClippingDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardClippingDrawerMaker& billboardMaterialHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardClippingDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardClippingDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������
		BillboardClippingDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		BillboardClippingDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardClippingDrawerMaker& blendRate(const tktkMath::Color& value);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		BillboardClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		BillboardClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardClippingDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user						{  };
		StateTypeHierarchy		m_targetState				{  };
		float					m_drawPriority				{ 0.0f };
		size_t					m_useRtvDescriptorHeapHandle{  };
		size_t					m_cameraHandle				{ 0U };
		size_t					m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2		m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color			m_blendRate					{ tktkMath::Color_v::white };
		BillboardClippingParam	m_clippingParam				{  };
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_MAKER_H_