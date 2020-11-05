#ifndef SOUND_PLAYER_MAKER_H_
#define SOUND_PLAYER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "SoundPlayer.h"

namespace tktk
{
	class SoundPlayerMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SoundPlayerMaker() = default;
		SoundPlayerMaker(const SoundPlayerMaker& other) = default;
		SoundPlayerMaker& operator = (const SoundPlayerMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static SoundPlayerMaker& makeStart(GameObjectPtr user);

		// �X�e�[�g���w�肵�A�쐬���J�n����
		static SoundPlayerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SoundPlayer> create();

	public:

		// �T�E���h�n���h���̐ݒ�
		SoundPlayerMaker& soundHandle(size_t soundHandle);

		// �T�E���hID�̐ݒ�i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SoundPlayerMaker& soundId(ResourceIdCarrier value);

		// �T�E���h�̃��[�v�t���O��ݒ肷��
		SoundPlayerMaker& isLoop(bool value);

		// ��������ɃT�E���h���Đ����邩��ݒ肷��
		SoundPlayerMaker& startToPlay(bool value);

	private:

		// ���g�̃|�C���^
		static SoundPlayerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr		m_user			{ };
		StateTypeHierarchy	m_targetState	{ };
		size_t				m_soundHandle	{ 0U };
		bool				m_isLoop		{ false };
		bool				m_startToPlay	{ false };
	};
}
#endif // !SOUND_PLAYER_MAKER_H_