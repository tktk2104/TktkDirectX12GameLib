#ifndef FONT_DATA_H_
#define FONT_DATA_H_

/* std::string */
#include <string>

/* std::vector */
#include <vector>

/* HFONT */
#include <Windows.h>
#undef min
#undef max

/* �Q�������W�A�x�N�g���\���� */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class FontData
	{
	public:

		// �V�X�e���t�H���g��
		FontData(const std::string& systemFontName, int fontSize, float fontThicknessRate);

		// �O���t�H���g��
		FontData(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate);

		~FontData();

	public:

		// �e�L�X�g�e�N�X�`���̃A�b�v���[�h�o�b�t�@�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		size_t updateTextTextureUploadBuffData(const std::string& text, unsigned int fontHeight, unsigned int textTextureWidth);

	private:

		// �w��̕����̃t�H���g�����e�N�X�`���f�[�^�̎w�肵���ʒu�ɏ�������
		tktkMath::Vector2 getCharSizeAndWriteFontData(HDC hdc, const char c[], size_t xOffset, const tktkMath::Vector2& textTextureSize, std::vector<unsigned char>* data);

	private:

		HFONT m_fontHandle;

		int m_fontSize;

		float m_fontThicknessRate;
	};
}
#endif // !FONT_DATA_H_