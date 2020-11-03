#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	class ReceiveMessageToSelfDestroyerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		ReceiveMessageToSelfDestroyerMaker() = default;
		ReceiveMessageToSelfDestroyerMaker(const ReceiveMessageToSelfDestroyerMaker& other) = default;
		ReceiveMessageToSelfDestroyerMaker& operator = (const ReceiveMessageToSelfDestroyerMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static ReceiveMessageToSelfDestroyerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static ReceiveMessageToSelfDestroyerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<ReceiveMessageToSelfDestroyer> create();

	public:

		// ���g���E�����b�Z�[�W�̎�ނ�ݒ�
		template<class MessageType, is_idType<MessageType> = nullptr>
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageType value) { return destroyMessegeTypeImpl(static_cast<unsigned int>(value)); }

	private: /* �e��id�w��n�̊֐��̎��� */

		ReceiveMessageToSelfDestroyerMaker& destroyMessegeTypeImpl(unsigned int value);

	private:

		// ���g�̃|�C���^
		static ReceiveMessageToSelfDestroyerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user				{ };
		StateTypeHierarchy		m_targetState		{ };
		unsigned int		m_destroyMessegeType{ 0 };

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class MessageType, is_not_idType<MessageType> = nullptr>
		ReceiveMessageToSelfDestroyerMaker& destroyMessegeType(MessageType value) { static_assert(false, "MessageType Fraud Type"); }
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_MAKER_H_