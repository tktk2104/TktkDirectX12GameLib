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

	// �t�H���g�Ǘ��N���X
	class FontManager
	{
	public:

		FontManager(const tktkContainer::ResourceContainerInitParam& initParam, const tktkMath::Vector2& textTextureSize);
		~FontManager();

	public:

		// �e�L�X�g��`�悷�邽�߂ɕK�v�Ȋ�{���\�[�X�����
		void createFontBaseResource();

		// �V�X�e���t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const std::string& systemFontName, int fontSize, float fontThicknessRate);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g�����������āA���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate);

		// �w��̃A�b�v���[�h�o�b�t�@�Ɉ����̕�����̃e�N�X�`���f�[�^���������݁A�������񂾃o�b�t�@�̍ő傘���W��Ԃ�
		size_t updateTextTextureUploadBuffData(size_t handle, size_t uploadBufferHandle, const std::string& text);

		// �e�L�X�g�������ݗp�̃A�b�v���[�h�o�b�t�@�����A���̃n���h����Ԃ�
		size_t createUploadBuffer();

	private:

		tktkMath::Vector2 m_textTextureSize;

		tktkContainer::ResourceContainer<FontData> m_fontDataContainer;
	};
}
#endif // !FONT_MANAGER_H_
