#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// �T�E���h�Đ��R���|�[�l���g
	class SoundPlayer
		: public ComponentBase
	{
	public:

		SoundPlayer(unsigned int soundHandle, bool isLoop, bool startToPlay);

	public:

		void playSound();

		void stopSound();

		void pauseSound();

		// �V���ȃT�E���h�n���h����ݒ肵�A�Đ�����
		void changeSoundHandle(unsigned int soundHandle);

		// �V���ȃT�E���hID��ݒ肵�A�Đ�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		template<class IdType, is_idType<IdType> = nullptr>
		void changeSoundId(IdType soundId) { return changeSoundIdImpl(static_cast<int>(soundId)); }

	public:

		void start();

		void onEnable();

		void onDisable();

		void onDestroy();

	private:

		void changeSoundIdImpl(int soundId);

	private:

		unsigned int	m_soundHandle;
		bool			m_isLoop;
		bool			m_startToPlay;

	public: /* �s���Ȍ^�̈������n���ꂻ���ɂȂ������ɃR���p�C���G���[�ɂ���ׂ̎d�g�� */

		template<class IdType, is_not_idType<IdType> = nullptr>
		void changeSoundId(IdType soundId) { static_assert(false, "SoundId Fraud Type"); }
	};
}
#endif // !SOUND_PLAYER_H_