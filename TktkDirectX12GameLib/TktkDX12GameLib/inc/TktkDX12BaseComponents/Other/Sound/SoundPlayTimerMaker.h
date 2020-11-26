#ifndef SOUND_PLAY_TIMER_MAKER_H_
#define SOUND_PLAY_TIMER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SoundPlayTimer.h"

namespace tktk
{
	class SoundPlayTimerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SoundPlayTimerMaker() = default;
		SoundPlayTimerMaker(const SoundPlayTimerMaker& other) = default;
		SoundPlayTimerMaker& operator = (const SoundPlayTimerMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static SoundPlayTimerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SoundPlayTimer> create();

	public:

		// �T�E���h�n���h���̐ݒ�
		SoundPlayTimerMaker& soundHandle(size_t value);

		// �T�E���hID�̐ݒ�i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SoundPlayTimerMaker& soundId(ResourceIdCarrier value);

		// �ŏ��̍Đ����s���܂ł̎���
		SoundPlayTimerMaker& firstPlayStartTimeSec(float value);

		// ���b�Ԃ̊Ԋu���󂯂čĐ����邩�H
		SoundPlayTimerMaker& playIntervalSec(float value);

		// ��x�̃^�C�}�[�ŉ���Đ����邩��ݒ肷��
		SoundPlayTimerMaker& playCount(int value);

		// ��������ɃT�E���h���Đ����邩��ݒ肷��
		SoundPlayTimerMaker& startToPlay(bool value);

	private:

		// ���g�̃|�C���^
		static SoundPlayTimerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user{ };
		size_t				m_soundHandle{ 0U };
		float				m_firstPlayStartTimeSec{ 0.0f };
		float				m_playIntervalSec{ 3.0f };
		int					m_playCount{ 10 };
		bool				m_startToPlay{ false };
	};
}
#endif // !SOUND_PLAY_TIMER_MAKER_H_