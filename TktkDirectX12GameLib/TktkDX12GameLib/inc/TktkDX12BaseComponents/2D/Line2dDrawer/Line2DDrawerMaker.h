#ifndef LINE_2D_DRAWER_MAKER_H_
#define LINE_2D_DRAWER_MAKER_H_
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "Line2DDrawer.h"

namespace tktk
{
	// 「Line2DDrawerMaker」を作るヘルパークラス
	class Line2DDrawerMaker
	{
	private: /* プライベートコンストラクタ達 */

		Line2DDrawerMaker() = default;
		Line2DDrawerMaker(const Line2DDrawerMaker & other) = default;
		Line2DDrawerMaker& operator = (const Line2DDrawerMaker & other) = default;

	public:

		// インスタンス作成開始
		static Line2DDrawerMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static Line2DDrawerMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<Line2DDrawer> create();
	

	public: /* パラメータ設定関数 */

		// 描画優先度を設定する
		Line2DDrawerMaker& drawPriority(float value);

		// 線分を構成する頂点座標の配列を設定する
		Line2DDrawerMaker& lineVertexArray(const std::vector<tktkMath::Vector2>& value);

		// 線の色を設定する
		Line2DDrawerMaker& lineColor(const tktkMath::Color& value);

		// 描画先画像に描画結果をどれぐらいの比率でブレンドするかを設定する
		Line2DDrawerMaker& blendRate(const tktkMath::Color& value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		Line2DDrawerMaker& useRtvDescriptorHeapHandle(unsigned int value);

	private:

		// 自身のポインタ
		static Line2DDrawerMaker m_self;
	
	private:

		// 作成用変数達
		GameObjectPtr					m_user						{ };
		std::vector<int>				m_targetState				{ };
		float							m_drawPriority				{ 0.0f };
		unsigned int					m_useRtvDescriptorHeapHandle{  }; // ※初期パラメータはバックバッファー
		std::vector<tktkMath::Vector2>	m_lineVertexArray			{ };
		tktkMath::Color					m_lineColor					{ tktkMath::Color_v::white };
		tktkMath::Color					m_blendRate					{ 1.0f, 1.0f, 1.0f, 1.0f };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline Line2DDrawerMaker& Line2DDrawerMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
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
#endif // !LINE_2D_DRAWER_MAKER_H_