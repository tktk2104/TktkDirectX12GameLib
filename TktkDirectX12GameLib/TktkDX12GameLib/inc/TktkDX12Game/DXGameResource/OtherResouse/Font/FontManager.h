#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

/* std::string */
#include <string>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* �Q�������W�A�x�N�g���\���� */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class FontData;

	struct FontManagerInitParam;

	// �t�H���g�Ǘ��N���X
	class FontManager
	{
	public:

		explicit FontManager(const FontManagerInitParam& initParam);
		~FontManager();

	public:

		// �e�L�X�g��`�悷�邽�߂ɕK�v�Ȋ�{���\�[�X�����
		void createFontBaseResource();

		// �V�X�e���t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const std::string& systemFontName, float fontThicknessRate);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// �e�L�X�g�e�N�X�`���̃A�b�v���[�h�o�b�t�@�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		size_t updateTextTextureUploadBuffData(size_t handle, const std::string& text);

		// �e�L�X�g�e�N�X�`���̃A�b�v���[�h�o�b�t�@�����ۂ̃e�N�X�`���o�b�t�@�ɃR�s�[����
		void copyTextTextureUploadBuffer();

	private:

		unsigned int	m_fontHeight;

		unsigned int	m_textTextureWidth;

		size_t			m_textSpriteMaxInstanceCount;

		tktkContainer::ResourceContainer<FontData> m_fontDataContainer;
	};
}
#endif // !FONT_MANAGER_H_
