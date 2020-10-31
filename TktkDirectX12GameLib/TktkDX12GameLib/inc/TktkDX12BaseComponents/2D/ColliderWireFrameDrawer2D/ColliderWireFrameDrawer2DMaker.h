#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_

#include "ColliderWireFrameDrawer2D.h"

namespace tktk
{
	// 「ColliderWireFrameDrawer2D」のインスタンスを作成するクラス
	class ColliderWireFrameDrawer2DMaker
	{
	private:  /* プライベートコンストラクタ達 */

		ColliderWireFrameDrawer2DMaker() = default;
		ColliderWireFrameDrawer2DMaker(const ColliderWireFrameDrawer2DMaker & other) = default;
		ColliderWireFrameDrawer2DMaker& operator = (const ColliderWireFrameDrawer2DMaker & other) = default;

	public:

		// 作成開始
		static ColliderWireFrameDrawer2DMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static ColliderWireFrameDrawer2DMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ColliderWireFrameDrawer2D> create();

		// 描画優先度を設定する
		ColliderWireFrameDrawer2DMaker& drawPriority(float value);

		// 線の色を設定する
		ColliderWireFrameDrawer2DMaker& lineColor(const tktkMath::Color& value);

	private:

		static ColliderWireFrameDrawer2DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr				m_user			{ };
		std::vector<int>			m_targetState	{ };
		float						m_drawPriority	{ 0.0f };
		tktkMath::Color				m_lineColor		{ tktkMath::Color_v::white };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline ColliderWireFrameDrawer2DMaker& ColliderWireFrameDrawer2DMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// 作成開始処理を行う
		auto& result = makeStart(user);

		// 初期化子リストを配列に変換
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// 対象のステートの階層数分のメモリを確保
		result.m_targetState.reserve(targetStateArray.size());

		// 対象のステートの階層を設定する
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// 自身の参照を返す
		return result;
	}
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
