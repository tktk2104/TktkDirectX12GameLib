#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "PostEffectDrawer.h"

namespace tktk
{
	// 「PostEffectDrawer」を作るヘルパークラス
	class PostEffectDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		PostEffectDrawerMaker() = default;
		PostEffectDrawerMaker(const PostEffectDrawerMaker& other) = default;
		PostEffectDrawerMaker& operator = (const PostEffectDrawerMaker& other) = default;

	public:

		// 作成開始
		static PostEffectDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<PostEffectDrawer> create();

	public:  /* パラメータ設定関数 */

		// 描画優先度を設定する
		PostEffectDrawerMaker& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		PostEffectDrawerMaker& useRtvDescriptorHeapId(unsigned int value);
		
		// 使用するポストエフェクトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		template<class IdType, is_idType<IdType> = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		PostEffectDrawerMaker& postEffectMaterialIdImpl(unsigned int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static PostEffectDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user							{  };
		float			m_drawPriority					{ 0.0f };
		unsigned int	m_useRtvDescriptorHeapHandle	{  }; // ※初期パラメータはバックバッファー
		unsigned int	m_postEffectMaterialId			{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		PostEffectDrawerMaker& postEffectMaterialId(IdType value) { static_assert(false, "PostEffectMaterialId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用するポストエフェクトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialId(IdType value)
	{
		return postEffectMaterialIdImpl(static_cast<unsigned int>(value));
	}
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_