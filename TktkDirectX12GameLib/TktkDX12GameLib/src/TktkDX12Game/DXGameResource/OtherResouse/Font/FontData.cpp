#include "TktkDX12Game/DXGameResource/OtherResouse/Font/FontData.h"

#include <stdexcept>

/* font */
#include <wingdi.h>

/* MultiByteToWideChar() */
#include <stringapiset.h>

/* GetDC() */
#include <WinUser.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

namespace tktk
{
	FontData::FontData(const std::string& systemFontName, int fontSize, float fontThicknessRate)
		: m_fontSize(fontSize)
		, m_fontThicknessRate(fontThicknessRate)
	{
		// �t�H���g�̑���
		int fontWeight = static_cast<int>(1000 * fontThicknessRate);

		// �t�H���g���쐬����
		m_fontHandle = CreateFont(
			fontSize, 0, 0, 0, fontWeight, FALSE, FALSE, FALSE,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,
			systemFontName.c_str()
		);

		if (m_fontHandle == nullptr)
		{
			throw std::runtime_error("create fontHandle error");
		}
	}

	FontData::FontData(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate)
		: m_fontSize(fontSize)
		, m_fontThicknessRate(fontThicknessRate)
	{
		// �t�H���g�t�@�C������t�H���g�����
		int result = AddFontResourceEx(fontFilePath.c_str(), FR_PRIVATE, NULL);

		if (result == 0)
		{
			throw std::runtime_error("load font error");
		}

		//// ���C�h������ϊ���̃t�H���g��
		//wchar_t afterCastFontName[32];
		//
		//// �t�H���g�������C�h������ɕϊ�����
		//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fontName.c_str(), -1, afterCastFontName, 32);

		// �t�H���g�̑���
		int fontWeight = static_cast<int>(1000 * fontThicknessRate);

		// �t�H���g���쐬����
		m_fontHandle = CreateFont(
			fontSize, 0, 0, 0, fontWeight, FALSE, FALSE, FALSE,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,
			fontName.c_str()
		);

		//// �t�H���g���쐬���邽�߂̃f�[�^
		//LOGFONTW lf =
		//{
		//	fontSize, 0, 0, 0, fontWeight, 0, 0, 0,
		//	SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		//	PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
		//	*afterCastFontName
		//};
		//
		//// �t�H���g���쐬����
		//m_fontHandle = CreateFontIndirectW(&lf);

		if (m_fontHandle == nullptr)
		{
			throw std::runtime_error("create fontHandle error");
		}
	}

	FontData::~FontData()
	{
		// �t�H���g�n���h�����폜����
		DeleteObject(m_fontHandle);
	}

	size_t FontData::updateTextTextureUploadBuffData(size_t uploadBufferHandle, const std::string& text, const tktkMath::Vector2& textTextureSize)
	{
		// �e�N�X�`���o�b�t�@�̏��
		std::vector<unsigned char>	textureData = std::vector<unsigned char>(static_cast<unsigned int>(textTextureSize.x * textTextureSize.y) * 4U, 0U);

		// �������ɂ�邘�����̃I�t�Z�b�g
		size_t xOffset = 0U;

		// �f�o�C�X�R���e�L�X�g���擾
		HDC hdc = GetDC(NULL);

		// �t�H���g��K������i�߂�l�F�Â��t�H���g�j
		HFONT oldFont = (HFONT)SelectObject(hdc, m_fontHandle);

		if (setlocale(LC_CTYPE, "") == NULL) return 0U;

		for (size_t i = 0U; i < text.size(); ++i)
		{
			int len = mblen(&text.at(i), 1);

			if (len == 1)
			{
				char c[1];
				memcpy(c, &text.at(i), 1U);

				// ���������������ɍ��W�����炵�ăe�N�X�`���o�b�t�@���X�V����
				auto charSize = getCharSizeAndWriteFontData(hdc, c, xOffset, textTextureSize, &textureData);
				xOffset += static_cast<size_t>(charSize.x);
			}
			else
			{
				len = mblen(&text.at(i), 2);

				if (len < 0) continue;

				char c[2];
				memcpy(c, &text.at(i), 2U);

				// ���������������ɍ��W�����炵�ăe�N�X�`���o�b�t�@���X�V����
				auto charSize = getCharSizeAndWriteFontData(hdc, c, xOffset, textTextureSize, &textureData);
				xOffset += static_cast<size_t>(charSize.x);

				++i;
			}
		}

		DX12GameManager::updateUploadBuffer(uploadBufferHandle, CopySourceDataCarrier(textureData.size(), textureData.data()));

		return xOffset;
	}

	tktkMath::Vector2 FontData::getCharSizeAndWriteFontData(HDC hdc, const char c[], size_t xOffset, const tktkMath::Vector2& textTextureSize, std::vector<unsigned char>* data)
	{
		// ���C�h������ϊ���̕���
		wchar_t afterCastStr[1];

		// ����������C�h������ɕϊ�����
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, c, -1, afterCastStr, 1);

		// �\�������镶���R�[�h���擾����
		UINT code = ((UINT)*afterCastStr);

		// �O���[�X�P�[���̌`��
		const int gradFlag = GGO_GRAY4_BITMAP;

		// �O���[�X�P�[���K�w�̍ő�l
		int gard = 16;

		// �t�H���g�f�[�^�Ɋւ�����̍\���̂��`���A�擾����
		TEXTMETRIC textMetric;
		GetTextMetrics(hdc, &textMetric);

		// �O���t�i���̃f�[�^�j�Ɋւ�����̍\����
		GLYPHMETRICS glyphMetrics;

		// 2x4�̍s��i�P�ʍs��H�j
		CONST MAT2 mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };

		// �������ݐ��ݒ肹���ɁA�O���t�i���̃f�[�^�j�̃T�C�Y�݂̂��擾���鏈��
		DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &glyphMetrics, 0, NULL, &mat);

		if (size == 0U) return tktkMath::Vector2_v::zero;

		// �������ݐ�̃��������O���t�i���̃f�[�^�j�̃T�C�Y���m�ۂ���
		std::vector<BYTE> mono = std::vector<BYTE>(size);

		// �O���t�i���̃f�[�^�j����������
		GetGlyphOutlineW(hdc, code, gradFlag, &glyphMetrics, size, mono.data(), &mat);

		// �t�H���g�f�[�^�̏c���̑傫��
		int fontSizeX = glyphMetrics.gmCellIncX;
		int fontSizeY = textMetric.tmHeight;

		// �e�L�X�g�`��p�e�L�X�g�o�b�t�@�̃T�C�Y�𒴉߂��Ă����珑�����݂����Ȃ�
		if (fontSizeY > textTextureSize.y || fontSizeX + xOffset > textTextureSize.x) return tktkMath::Vector2_v::zero;

		// �t�H���g�f�[�^���̃O���t�i���̃f�[�^�j�̃I�t�Z�b�g�l
		size_t glyphOffsetX = glyphMetrics.gmptGlyphOrigin.x;
		size_t glyphOffsetY = textMetric.tmAscent - glyphMetrics.gmptGlyphOrigin.y;

		// �O���t�i���̃f�[�^�j�̏c���̑傫��
		size_t glyphWidth = glyphMetrics.gmBlackBoxX + (4 - (glyphMetrics.gmBlackBoxX % 4)) % 4;
		size_t glyphHeight = glyphMetrics.gmBlackBoxY;

		for (size_t y = glyphOffsetY; y < (glyphOffsetY + glyphHeight); y++)
		{
			for (size_t x = glyphOffsetX; x < (glyphOffsetX + glyphWidth); x++)
			{
				unsigned int alpha = (255 * mono.at(x - glyphOffsetX + glyphWidth * (y - glyphOffsetY))) / 16;

				data->at((xOffset * 4) + (y * static_cast<size_t>(textTextureSize.x) * 4U) + (x * 4U) + 0U) = 255U;
				data->at((xOffset * 4) + (y * static_cast<size_t>(textTextureSize.x) * 4U) + (x * 4U) + 1U) = 255U;
				data->at((xOffset * 4) + (y * static_cast<size_t>(textTextureSize.x) * 4U) + (x * 4U) + 2U) = 255U;
				data->at((xOffset * 4) + (y * static_cast<size_t>(textTextureSize.x) * 4U) + (x * 4U) + 3U) = alpha;
			}
		}

		// �t�H���g�f�[�^�̏c���̑傫����Ԃ�
		return { static_cast<float>(fontSizeX),  static_cast<float>(fontSizeY) };
	}
}