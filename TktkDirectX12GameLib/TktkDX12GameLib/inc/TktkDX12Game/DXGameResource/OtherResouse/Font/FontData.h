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

/* ２次元座標、ベクトル構造体 */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class FontData
	{
	public:

		// システムフォント版
		FontData(const std::string& systemFontName, int fontSize, float fontThicknessRate);

		// 外部フォント版
		FontData(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate);

		~FontData();

	public:

		// テキストテクスチャのアップロードバッファに引数の文字列のテクスチャデータを書き込み、書き込んだバッファの最大ｘ座標を返す
		size_t updateTextTextureUploadBuffData(const std::string& text, unsigned int fontHeight, unsigned int textTextureWidth);

	private:

		// 指定の文字のフォント情報をテクスチャデータの指定した位置に書き込む
		tktkMath::Vector2 getCharSizeAndWriteFontData(HDC hdc, const char c[], size_t xOffset, const tktkMath::Vector2& textTextureSize, std::vector<unsigned char>* data);

	private:

		HFONT m_fontHandle;

		int m_fontSize;

		float m_fontThicknessRate;
	};
}
#endif // !FONT_DATA_H_