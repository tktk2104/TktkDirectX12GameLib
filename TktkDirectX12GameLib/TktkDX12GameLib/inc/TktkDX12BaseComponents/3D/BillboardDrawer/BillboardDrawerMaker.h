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

		// �`��D��x��ݒ肷��
		BillboardDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BillboardDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardDrawerMaker& billboardMaterialHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardDrawerMaker& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardDrawerMaker& cameraId(ResourceIdCarrier value);

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BillboardDrawerMaker& billboardMaterialId(ResourceIdCarrier value);

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		BillboardDrawerMaker& centerRate(const tktkMath::Vector2 & value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardDrawerMaker& blendRate(const tktkMath::Color& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_cameraHandle				{ 0U };
		size_t				m_billboardMaterialHandle	{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
	};
}
#endif // !BILLBOARD_DRAWER_MAKER_H_