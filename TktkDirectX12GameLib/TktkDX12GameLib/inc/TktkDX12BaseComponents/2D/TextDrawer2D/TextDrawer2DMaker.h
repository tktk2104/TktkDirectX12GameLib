#ifndef TEXT_DRAWER_2D_MAKER_H_
#define TEXT_DRAWER_2D_MAKER_H_

#include "TextDrawer2D.h"

namespace tktk
{
	// �uTextDrawer2D�v�����w���p�[�N���X
	class TextDrawer2DMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		TextDrawer2DMaker() = default;
		TextDrawer2DMaker(const TextDrawer2DMaker& other) = default;
		TextDrawer2DMaker& operator = (const TextDrawer2DMaker& other) = default;

	public:

		// �쐬�J�n
		static TextDrawer2DMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<TextDrawer2D> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �`��D��x��ݒ肷��
		TextDrawer2DMaker& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓|�X�g�G�t�F�N�g�K���Ώ�
		TextDrawer2DMaker& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����t�H���g�n���h����ݒ肷��
		TextDrawer2DMaker& fontHandle(size_t value);

		// �g�p����t�H���gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		TextDrawer2DMaker& fontId(ResourceIdCarrier value);

		// �����e�L�X�g��ݒ肷��
		TextDrawer2DMaker& initText(const std::string& value);

		// �e�L�X�g�̒��S�ʒu�̊�����ݒ肷��
		TextDrawer2DMaker& centerRate(const tktkMath::Vector2 & value);

		// �u�����h���[�g��ݒ肷��
		TextDrawer2DMaker& blendRate(const tktkMath::Color & value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static TextDrawer2DMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr		m_user						{  };
		float				m_drawPriority				{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle{  };
		size_t				m_fontHandle				{ 0U };
		std::string			m_initText					{  };
		tktkMath::Vector2	m_centerRate				{ tktkMath::Vector2_v::zero };
		tktkMath::Color		m_blendRate					{ tktkMath::Color_v::white };
	};
}
#endif // !TEXT_DRAWER_2D_MAKER_H_