#ifndef MESH_ANIMATOR_MAKER_H_
#define MESH_ANIMATOR_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MeshAnimator.h"

namespace tktk
{
	// 「MeshAnimator」を作るヘルパークラス
	class MeshAnimatorMaker
	{
	private: /* プライベートコンストラクタ達 */

		MeshAnimatorMaker() = default;
		MeshAnimatorMaker(const MeshAnimatorMaker& other) = default;
		MeshAnimatorMaker& operator = (const MeshAnimatorMaker& other) = default;

	public:

		// 作成開始
		static MeshAnimatorMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MeshAnimator> create();

	public:  /* パラメータ設定関数 */

		// モーションをループさせるかを設定する
		MeshAnimatorMaker& isLoop(bool value);

		// 使用する初期モーションハンドルを設定する
		MeshAnimatorMaker& initMotionHandle(unsigned int value);

		// 使用する初期モーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		template<class IdType, is_idType<IdType> = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value);

	private: /* 各種id指定系の関数の実装 */

		MeshAnimatorMaker& initMotionIdImpl(int value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MeshAnimatorMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user				{  };
		unsigned int	m_isLoop			{ true };
		unsigned int	m_initMotionHandle	{ 0U };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		MeshAnimatorMaker& initMotionId(IdType value) { static_assert(false, "MotionId Fraud Type"); }
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 使用する初期モーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
	template<class IdType, is_idType<IdType>>
	inline MeshAnimatorMaker& MeshAnimatorMaker::initMotionId(IdType value)
	{
		return initMotionIdImpl(static_cast<int>(value));
	}
}
#endif // !MESH_ANIMATOR_MAKER_H_
