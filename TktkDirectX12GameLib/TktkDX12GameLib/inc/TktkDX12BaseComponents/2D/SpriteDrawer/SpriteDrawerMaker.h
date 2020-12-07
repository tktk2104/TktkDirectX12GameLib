#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include "SpriteDrawer.h"

namespace tktk
{
	// �uSpriteDrawer�v�����w���p�[�N���X
	class SpriteDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SpriteDrawerMaker() = default;
		SpriteDrawerMaker(const SpriteDrawerMaker& other) = default;
		SpriteDrawerMaker& operator = (const SpriteDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SpriteDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteDrawerMaker& spriteMaterialHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SpriteDrawerMaker& spriteMaterialId(ResourceIdCarrier value);

		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		SpriteDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// �u�����h���[�g��ݒ肷��
		SpriteDrawerMaker& blendRate(const tktkMath::Color& value);

		// �؂���͈͂̍�����W��ݒ肷��i�e�N�X�`���T�C�Y���i1, 1�j�Ƃ������̊����j
		SpriteDrawerMaker& clippingLeftTopPosRate(const tktkMath::Vector2& value);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�X�`���T�C�Y���i1, 1�j�Ƃ������̊����j
		SpriteDrawerMaker& clippingSizeRate(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		tktkMath::Vector2	m_leftTopPosRate			{ tktkMath::Vector2_v::zero };
		tktkMath::Vector2	m_sizeRate					{ tktkMath::Vector2_v::one };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_