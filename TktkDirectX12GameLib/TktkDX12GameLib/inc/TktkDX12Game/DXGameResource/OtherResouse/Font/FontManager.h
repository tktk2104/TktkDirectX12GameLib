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

	// フォント管理クラス
	class FontManager
	{
	public:

		FontManager(const tktkContainer::ResourceContainerInitParam& initParam, const tktkMath::Vector2& textTextureSize);
		~FontManager();

	public:

		// テキストを描画するために必要な基本リソースを作る
		void createFontBaseResource();

		// システムフォントを使う準備をして、そのリソースのハンドルを返す
		size_t create(const std::string& systemFontName, int fontSize, float fontThicknessRate);

		// フォントファイルを読み込み、そのフォントを使う準備をして、そのリソースのハンドルを返す
		size_t create(const std::string& fontFilePath, const std::string& fontName, int fontSize, float fontThicknessRate);

		// 指定のアップロードバッファに引数の文字列のテクスチャデータを書き込み、書き込んだバッファの最大ｘ座標を返す
		size_t updateTextTextureUploadBuffData(size_t handle, size_t uploadBufferHandle, const std::string& text);

		// テキスト書き込み用のアップロードバッファを作り、そのハンドルを返す
		size_t createUploadBuffer();

	private:

		tktkMath::Vector2 m_textTextureSize;

		tktkContainer::ResourceContainer<FontData> m_fontDataContainer;
	};
}
#endif // !FONT_MANAGER_H_
