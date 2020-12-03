#ifndef SPRITE_CLIPPING_DRAWER_MAKER_H_
#define SPRITE_CLIPPING_DRAWER_MAKER_H_

#include "SpriteClippingDrawer.h"

namespace tktk
{
	// �uSpriteClippingDrawer�v�����w���p�[�N���X
	class SpriteClippingDrawerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SpriteClippingDrawerMaker() = default;
		SpriteClippingDrawerMaker(const SpriteClippingDrawerMaker& other) = default;
		SpriteClippingDrawerMaker& operator = (const SpriteClippingDrawerMaker& other) = default;

	public:

		// �쐬�J�n
		static SpriteClippingDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteClippingDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SpriteClippingDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		SpriteClippingDrawerMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteClippingDrawerMaker& spriteMaterialHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SpriteClippingDrawerMaker& spriteMaterialId(ResourceIdCarrier value);

		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		SpriteClippingDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// �u�����h���[�g��ݒ肷��
		SpriteClippingDrawerMaker& blendRate(const tktkMath::Color& value);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		SpriteClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		SpriteClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteClippingDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
		SpriteClippingParam	m_clippingParam				{  };
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_MAKER_H_
