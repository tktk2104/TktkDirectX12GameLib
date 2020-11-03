#ifndef SPRITE_CLIPPING_DRAWER_MAKER_H_
#define SPRITE_CLIPPING_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static SpriteClippingDrawerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteClippingDrawer> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		SpriteClippingDrawerMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		SpriteClippingDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteClippingDrawerMaker& spriteMaterialHandle(unsigned int value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		SpriteClippingDrawerMaker& spriteMaterialId(IdType value) { return spriteMaterialIdImpl(static_cast<int>(value)); }

		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		SpriteClippingDrawerMaker& centerRate(const tktkMath::Vector2& value);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		SpriteClippingDrawerMaker& clippingLeftTopPos(const tktkMath::Vector2& value);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		SpriteClippingDrawerMaker& clippingSize(const tktkMath::Vector2& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		SpriteClippingDrawerMaker& spriteMaterialIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteClippingDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		StateTypeHierarchy		m_targetState				{  };
		float				m_drawPriority				{ 0.0f };
		unsigned int		m_useRtvDescriptorHeapHandle{  };
		unsigned int		m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };
		SpriteClippingParam	m_clippingParam				{  };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		SpriteClippingDrawerMaker& spriteMaterialId(IdType value) { static_assert(false, "SpriteMaterialId Fraud Type"); }
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_MAKER_H_
