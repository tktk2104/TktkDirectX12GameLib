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

		SoundPlayer(size_t soundHandle, bool isLoop, bool startToPlay);

	public:

		void playSound();

		void stopSound();

		void pauseSound();

		// �V���ȃT�E���h�n���h����ݒ肵�A�Đ�����
		void changeSoundHandle(size_t soundHandle);

		// �V���ȃT�E���hID��ݒ肵�A�Đ�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		void changeSoundId(ResourceIdCarrier soundId);

	public:

		void start();

		void onEnable();

		void onDisable();

		void onDestroy();

	private:

		size_t	m_soundHandle;
		bool	m_isLoop;
		bool	m_startToPlay;
	};
}
#endif // !SOUND_PLAYER_H_