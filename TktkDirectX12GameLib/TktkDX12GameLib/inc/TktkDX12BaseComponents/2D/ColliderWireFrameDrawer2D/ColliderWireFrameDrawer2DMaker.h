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
		GameObjectPtr		m_user			{ };
		float				m_drawPriority	{ 0.0f };
		tktkMath::Color		m_lineColor		{ tktkMath::Color_v::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_MAKER_H_
