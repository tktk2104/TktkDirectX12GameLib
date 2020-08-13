#ifndef TRANSFORM_2D_MAKER_H_
#define TRANSFORM_2D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform2D.h"

namespace tktk
{
	// 「Transform2D」を作るヘルパークラス
	class Transform2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		Transform2DMaker() = default;
		Transform2DMaker(const Transform2DMaker& other) = default;
		Transform2DMaker& operator = (const Transform2DMaker& other) = default;

	public:

		// 作成開始
		static Transform2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Transform2D> create();

	public:  /* パラメータ設定関数 */

		// 初期座標を設定する
		Transform2DMaker& initPosition(const tktkMath::Vector2& value);

		// 初期スケールを設定する
		Transform2DMaker& initScaleRate(const tktkMath::Vector2& value);

		// 初期回転を設定する
		Transform2DMaker& initRotationDeg(float value);

		// 親のTransform2Dとの関係性の種類を設定する
		Transform2DMaker& traceType(TraceParentType value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static Transform2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		tktkMath::Vector2	m_initPosition		{ tktkMath::vec2Zero };
		tktkMath::Vector2	m_initScaleRate		{ tktkMath::vec2One };
		float				m_initRotationDeg	{ 0.0f };
		TraceParentType		m_traceType			{ TraceParentType::trace_All };
	};
}
#endif // !TRANSFORM_2D_MAKER_H_