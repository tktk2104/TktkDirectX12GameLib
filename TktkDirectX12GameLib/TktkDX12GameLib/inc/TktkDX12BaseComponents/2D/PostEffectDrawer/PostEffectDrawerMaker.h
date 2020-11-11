#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
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
		
		// 使用するポストエフェクトマテリアルハンドルを設定する
		PostEffectDrawerMaker& postEffectMaterialHandle(unsigned int value);

		// 使用するポストエフェクトマテリアルIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		PostEffectDrawerMaker& postEffectMaterialId(ResourceIdCarrier value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static PostEffectDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user							{  };
		float				m_drawPriority					{ 0.0f };
		size_t				m_useRtvDescriptorHeapHandle	{  }; // ※初期パラメータはバックバッファー
		size_t				m_postEffectMaterialHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_