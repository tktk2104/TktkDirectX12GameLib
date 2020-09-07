#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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
		SpriteDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteDrawerMaker& spriteMaterialHandle(unsigned int value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value) { return spriteMaterialIdImpl(static_cast<int>(value)); }

		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		SpriteDrawerMaker& centerRate(const tktkMath::Vector2& value);

	private: /* �e��id�w��n�̊֐��̎��� */

		SpriteDrawerMaker& spriteMaterialIdImpl(int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteDrawerMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		unsigned int		m_useRtvDescriptorHeapHandle{  };
		unsigned int		m_spriteMaterialHandle		{ 0U };
		tktkMath::Vector2	m_centerRate				{ 0.5f, 0.5f };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SpriteDrawerMaker& spriteMaterialId(IdType value) { static_assert(false, "SpriteMaterialId Fraud Type"); }
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_