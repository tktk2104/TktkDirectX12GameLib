#ifndef COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_
#define COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_

#include "ColliderWireFrameDrawer3D.h"

namespace tktk
{
	// 「ColliderWireFrameDrawer3D」のインスタンスを作成するクラス
	class ColliderWireFrameDrawer3DMaker
	{
	private:  /* プライベートコンストラクタ達 */

		ColliderWireFrameDrawer3DMaker() = default;
		ColliderWireFrameDrawer3DMaker(const ColliderWireFrameDrawer3DMaker& other) = default;
		ColliderWireFrameDrawer3DMaker& operator = (const ColliderWireFrameDrawer3DMaker& other) = default;

	public:

		// 作成開始
		static ColliderWireFrameDrawer3DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<ColliderWireFrameDrawer3D> create();

		// 線の色を設定する
		ColliderWireFrameDrawer3DMaker& lineColor(const tktkMath::Color & value);

	private:

		static ColliderWireFrameDrawer3DMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr						m_user				{ };
		tktkMath::Color						m_lineColor			{ tktkMath::Color_v::white };
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_3D_MAKER_H_