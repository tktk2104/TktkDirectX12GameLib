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
		// フォントの太さ
		int fontWeight = static_cast<int>(1000 * fontThicknessRate);

		// フォントを作成する
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
		// フォントファイルからフォントを作る
		int result = AddFontResourceEx(fontFilePath.c_str(), FR_PRIVATE, NULL);

		if (result == 0)
		{
			throw std::runtime_error("load font error");
		}

		//// ワイド文字列変換後のフォント名
		//wchar_t afterCastFontName[32];
		//
		//// フォント名をワイド文字列に変換する
		//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, fontName.c_str(), -1, afterCastFontName, 32);

		// フォントの太さ
		int fontWeight = static_cast<int>(1000 * fontThicknessRate);

		// フォントを作成する
		m_fontHandle = CreateFont(
			fontSize, 0, 0, 0, fontWeight, FALSE, FALSE, FALSE,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,
			fontName.c_str()
		);

		//// フォントを作成するためのデータ
		//LOGFONTW lf =
		//{
		//	fontSize, 0, 0, 0, fontWeight, 0, 0, 0,
		//	SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS,
		//	PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN,
		//	*afterCastFontName
		//};
		//
		//// フォントを作成する
		//m_fontHandle = CreateFontIndirectW(&lf);

		if (m_fontHandle == nullptr)
		{
			throw std::runtime_error("create fontHandle error");
		}
	}

	FontData::~FontData()
	{
		// フォントハンドルを削除する
		DeleteObject(m_fontHandle);
	}

	size_t FontData::updateTextTextureUploadBuffData(size_t uploadBufferHandle, const std::string& text, const tktkMath::Vector2& textTextureSize)
	{
		// テクスチャバッファの情報
		std::vector<unsigned char>	textureData = std::vector<unsigned char>(static_cast<unsigned int>(textTextureSize.x * textTextureSize.y) * 4U, 0U);

		// 文字数によるｘ方向のオフセット
		size_t xOffset = 0U;

		// デバイスコンテキストを取得
		HDC hdc = GetDC(NULL);

		// フォントを適応する（戻り値：古いフォント）
		HFONT oldFont = (HFONT)SelectObject(hdc, m_fontHandle);

		if (setlocale(LC_CTYPE, "") == NULL) return 0U;

		for (size_t i = 0U; i < text.size(); ++i)
		{
			int len = mblen(&text.at(i), 1);

			if (len == 1)
			{
				char c[1];
				memcpy(c, &text.at(i), 1U);

				// 文字数分ｘ方向に座標をずらしてテクスチャバッファを更新する
				auto charSize = getCharSizeAndWriteFontData(hdc, c, xOffset, textTextureSize, &textureData);
				xOffset += static_cast<size_t>(charSize.x);
			}
			else
			{
				len = mblen(&text.at(i), 2);

				if (len < 0) continue;

				char c[2];
				memcpy(c, &text.at(i), 2U);

				// 文字数分ｘ方向に座標をずらしてテクスチャバッファを更新する
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
		// ワイド文字列変換後の文字
		wchar_t afterCastStr[1];

		// 文字列をワイド文字列に変換する
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, c, -1, afterCastStr, 1);

		// 表示させる文字コードを取得する
		UINT code = ((UINT)*afterCastStr);

		// グレースケールの形式
		const int gradFlag = GGO_GRAY4_BITMAP;

		// グレースケール階層の最大値
		int gard = 16;

		// フォントデータに関する情報の構造体を定義し、取得する
		TEXTMETRIC textMetric;
		GetTextMetrics(hdc, &textMetric);

		// グリフ（字体データ）に関する情報の構造体
		GLYPHMETRICS glyphMetrics;

		// 2x4の行列（単位行列？）
		CONST MAT2 mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };

		// 書き込み先を設定せずに、グリフ（字体データ）のサイズのみを取得する処理
		DWORD size = GetGlyphOutlineW(hdc, code, gradFlag, &glyphMetrics, 0, NULL, &mat);

		if (size == 0U) return tktkMath::Vector2_v::zero;

		// 書き込み先のメモリをグリフ（字体データ）のサイズ分確保する
		std::vector<BYTE> mono = std::vector<BYTE>(size);

		// グリフ（字体データ）を書き込む
		GetGlyphOutlineW(hdc, code, gradFlag, &glyphMetrics, size, mono.data(), &mat);

		// フォントデータの縦横の大きさ
		int fontSizeX = glyphMetrics.gmCellIncX;
		int fontSizeY = textMetric.tmHeight;

		// テキスト描画用テキストバッファのサイズを超過していたら書き込みをしない
		if (fontSizeY > textTextureSize.y || fontSizeX + xOffset > textTextureSize.x) return tktkMath::Vector2_v::zero;

		// フォントデータ内のグリフ（字体データ）のオフセット値
		size_t glyphOffsetX = glyphMetrics.gmptGlyphOrigin.x;
		size_t glyphOffsetY = textMetric.tmAscent - glyphMetrics.gmptGlyphOrigin.y;

		// グリフ（字体データ）の縦横の大きさ
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

		// フォントデータの縦横の大きさを返す
		return { static_cast<float>(fontSizeX),  static_cast<float>(fontSizeY) };
	}
}