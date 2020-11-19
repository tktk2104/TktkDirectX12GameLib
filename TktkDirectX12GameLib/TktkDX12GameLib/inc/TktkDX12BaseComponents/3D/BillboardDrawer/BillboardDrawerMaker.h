#ifndef BILLBOARD_DRAWER_MAKER_H_
#define BILLBOARD_DRAWER_MAKER_H_

#include "BillboardDrawer.h"

namespace tktk
{
	// �uBillboardDrawer�v�����w���p�[�N���X
	class BillboardDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BillboardDrawerMaker() = default;
		BillboardDrawerMaker(const BillboardDrawerMaker& other) = default;
		BillboardDrawerMaker& operator = (const BillboardDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static BillboardDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardDrawerMaker& billboardMaterialHandle(size_t value);

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BillboardDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		BillboardDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardDrawerMaker& blendRate(const tktkMath::Color& value);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		BillboardDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// �r���{�[�h�n���h�����g�p���A�N���b�s���O���s��Ȃ��ݒ������
		BillboardDrawerMaker& notClippingUseHandle(size_t billboarddMaterialHandle);

		// �r���{�[�hId���g�p���A�N���b�s���O���s��Ȃ��ݒ������i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BillboardDrawerMaker& notClippingUseId(ResourceIdCarrier billboarddMaterialId);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		BillboardDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		size_t				m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		tktkMath::Vector2	m_clippingLeftTopPos		{ 0.0f, 0.0f };
		tktkMath::Vector2	m_clippingSize				{ 64.0f, 64.0f };
	};
}
#endif // !BILLBOARD_DRAWER_MAKER_H_