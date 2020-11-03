#ifndef TRANSFORM_3D_MAKER_H_
#define TRANSFORM_3D_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Transform3D.h"

namespace tktk
{
	// 「Transform3D」を作るヘルパークラス
	class Transform3DMaker
	{
	private: /* プライベートコンストラクタ達 */

		Transform3DMaker() = default;
		Transform3DMaker(const Transform3DMaker& other) = default;
		Transform3DMaker& operator = (const Transform3DMaker& other) = default;

	public:

		// 作成開始
		static Transform3DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		static Transform3DMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Transform3D> create();

	public:  /* パラメータ設定関数 */

		// 初期座標を設定する
		Transform3DMaker& initPosition(const tktkMath::Vector3& value);

		// 初期スケールを設定する
		Transform3DMaker& initScaleRate(const tktkMath::Vector3& value);

		// 初期回転を設定する
		Transform3DMaker& initRotation(const tktkMath::Quaternion& value);

		// 初期回転を設定する（オイラー角）
		Transform3DMaker& initRotation(const tktkMath::Vector3& value);

		// 行列から初期パラメータを設定する（座標変換情報のみ）
		Transform3DMaker& setInitTransformFromMatrix(const tktkMath::Matrix4& value);

		// 親のTransform3Dとの関係性の種類を設定する
		Transform3DMaker& traceType(TraceParentType value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static Transform3DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user			{  };
		StateTypeHierarchy			m_targetState	{  };
		tktkMath::Vector3		m_initPosition	{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_initScaleRate	{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_initRotation	{ tktkMath::Quaternion_v::identity };
		TraceParentType			m_traceType		{ TraceParentType::trace_All };
	};
}
#endif // !TRANSFORM_3D_MAKER_H_