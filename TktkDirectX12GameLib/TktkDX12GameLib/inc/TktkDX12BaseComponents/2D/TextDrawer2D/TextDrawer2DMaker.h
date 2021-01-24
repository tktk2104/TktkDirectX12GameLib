#ifndef TEXT_DRAWER_2D_MAKER_H_
#define TEXT_DRAWER_2D_MAKER_H_

#include "TextDrawer2D.h"

namespace tktk
{
	// 「TextDrawer2D」を作るヘルパークラス
	class TextDrawer2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		TextDrawer2DMaker() = default;
		TextDrawer2DMaker(const TextDrawer2DMaker& other) = default;
		TextDrawer2DMaker& operator = (const TextDrawer2DMaker& other) = default;

	public:

		// 作成開始
		static TextDrawer2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<TextDrawer2D> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		TextDrawer2DMaker& drawPriority(float value);

		// 使用するフォントハンドルを設定する
		TextDrawer2DMaker& fontHandle(size_t value);

		// 使用するフォントIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		TextDrawer2DMaker& fontId(ResourceIdCarrier value);

		// 初期テキストを設定する
		TextDrawer2DMaker& initText(const std::string& value);

		// テキストのローカル座標を設定する
		TextDrawer2DMaker& localPosition(const tktkMath::Vector2& value);

		// テキストのローカルスケールを設定する
		TextDrawer2DMaker& localScale(const tktkMath::Vector2& value);

		// テキストの中心位置の割合を設定する
		TextDrawer2DMaker& centerRate(const tktkMath::Vector2 & value);

		// ブレンドレートを設定する
		TextDrawer2DMaker& blendRate(const tktkMath::Color & value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static TextDrawer2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user			{  };
		float				m_drawPriority	{ 0.0f };
		size_t				m_fontHandle	{ 0U };
		std::string			m_initText		{  };
		tktkMath::Vector2	m_localPosition	{ tktkMath::Vector2_v::zero };
		tktkMath::Vector2	m_localScale	{ tktkMath::Vector2_v::one };
		tktkMath::Vector2	m_centerRate	{ tktkMath::Vector2_v::zero };
		tktkMath::Color		m_blendRate		{ tktkMath::Color_v::white };
	};
}
#endif // !TEXT_DRAWER_2D_MAKER_H_