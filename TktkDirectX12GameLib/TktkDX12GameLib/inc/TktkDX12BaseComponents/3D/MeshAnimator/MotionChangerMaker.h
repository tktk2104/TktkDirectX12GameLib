#ifndef MOTION_CHANGER_MAKER_H_
#define MOTION_CHANGER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "MotionChanger.h"

namespace tktk
{
	// 「MotionChanger」を作るヘルパークラス
	class MotionChangerMaker
	{
	private: /* プライベートコンストラクタ達 */

		MotionChangerMaker() = default;
		MotionChangerMaker(const MotionChangerMaker& other) = default;
		MotionChangerMaker& operator = (const MotionChangerMaker& other) = default;

	public:

		// 作成開始
		static MotionChangerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		static MotionChangerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MotionChanger> create();

	public:  /* パラメータ設定関数 */

		// モーションをループさせるかを設定する
		MotionChangerMaker& isLoop(bool value);

		// 使用するモーションハンドルを設定する
		MotionChangerMaker& initMotionHandle(size_t value);

		// 使用するモーションIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可）
		// ※内部で対応するリソースハンドルに変換される
		MotionChangerMaker& initMotionId(ResourceIdCarrier value);

		// 何秒間かけてモーションの遷移を行うか？
		MotionChangerMaker& lerpTimeSec(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MotionChangerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user				{  };
		StateTypeHierarchy	m_targetState	{  };
		bool				m_isLoop			{ true };
		size_t				m_initMotionHandle	{ 0U };
		float				m_lerpTimeSec		{ 1.0f };
	};
}
#endif // !MOTION_CHANGER_MAKER_H_