#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

/* std::string */
#include <string>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* ２次元座標、ベクトル構造体 */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	class FontData;

	struct FontManagerInitParam;

	// フォント管理クラス
	class FontManager
	{
	public:

		explicit FontManager(const FontManagerInitParam& initParam);
		~FontManager();

	public:

		// テキストを描画するために必要な基本リソースを作る
		void createFontBaseResource();

		// システムフォントを使う準備をして、そのリソースのハンドルを返す
		size_t create(const std::string& systemFontName, float fontThicknessRate);

		// フォントファイルを読み込み、そのフォントを使う準備をして、そのリソースのハンドルを返す
		size_t create(const std::string& fontFilePath, const std::string& fontName, float fontThicknessRate);

		// テキストテクスチャのアップロードバッファに引数の文字列のテクスチャデータを書き込み、書き込んだバッファの最大ｘ座標を返す
		size_t updateTextTextureUploadBuffData(size_t handle, const std::string& text);

		// テキストテクスチャのアップロードバッファを実際のテクスチャバッファにコピーする
		void copyTextTextureUploadBuffer();

	private:

		unsigned int	m_fontHeight;

		unsigned int	m_textTextureWidth;

		size_t			m_textSpriteMaxInstanceCount;

		tktkContainer::ResourceContainer<FontData> m_fontDataContainer;
	};
}
#endif // !FONT_MANAGER_H_
